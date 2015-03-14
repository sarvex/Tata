#include "DeamonInterface.h"

#include "SerialEnumerator.h"

#include <QDebug>
#include <QTime>

DeamonInterface* DeamonInterface::singleton = NULL;

DeamonInterface* DeamonInterface::getInstance () {
	if (NULL == singleton) {
		singleton = new DeamonInterface();
	}
	return (singleton);
}

DeamonInterface::DeamonInterface(QObject *parent) : QThread(parent), running (true) {
	this->mutex = new QMutex();
	this->atPort = NULL;

	this->writeToAtPort (DeamonInterface::echoOff);
	this->writeToAtPort (DeamonInterface::enableFlashMessage);
	this->writeToAtPort (DeamonInterface::signalStrength);

	this->systemInformationTimer = new QTimer(this);
	connect(systemInformationTimer, SIGNAL(timeout()), SLOT(onSystemUpdateTimer()));
	this->systemInformationTimer->start(SIGNAL_STRENGTH_TIMEOUT);
}

DeamonInterface::~DeamonInterface () {
	this->stop ();

	if (NULL != this->mutex) delete this->mutex;
	if (NULL != this->atPort) delete this->atPort;
	if (NULL != this->modemPort) delete this->modemPort;
	if (NULL != this->systemInformationTimer) delete this->systemInformationTimer;
}

bool DeamonInterface::onSystemUpdateTimer () {
	DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::signalStrength);
	DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::systemInformation);
	return true;
}

void DeamonInterface::run (){
	qDebug () << "Starting DeamonPortThread";

	forever {
		if ( true == this->running ) {
			// check for modem existence
			if ( true == this->checkModem ()) {

				// initialize the port
				if ( false == this->openAtPort ()) {
					continue;
				}

				this->writeToAtPort ();

				this->msleep (THREAD_SLEEP_TIMEOUT);

				this->readFromAtPort ();

			}
			// sleep
			this->msleep (THREAD_SLEEP_TIMEOUT);
		} else {
			break;
		}
	}

	qDebug () << "Stopping DeamonPortThread";
	// close port
}

bool DeamonInterface::checkModem () {
	bool result = false;
	this->atPortName = "";

	QList<PortInformation> ports = SerialEnumerator::getPorts();
	for (int index = 0; index < ports.size(); index++) {
		if (VENDOR_ID == ports.at(index).vendorID) {
			if (PRODUCT_ID == ports.at(index).productID) {

				if (ports.at(index).friendName.contains(AT_PORT_NAME)) {
					this->atPortName = ports.at (index).portName;
					this->atPortName.remove ("\\\\.\\");

					result = true;
					break;
				}
			}
		}
	}

	if ( true == result ) {
		emit modemPlugged ();
	} else {
		emit modemUnplugged ();
	}

	return result;
}

bool DeamonInterface::openAtPort() {
	bool result = false;

	if (true == this->atPortName.isEmpty ()) {
		if ( NULL != this->atPort) {
			delete this->atPort;
			this->atPort = NULL;
		}
		result = false;
	} else {
		if ( NULL == this->atPort) {
			this->atPort = new SerialPort(atPortName, SerialPort::Polling);

			if ( true == this->atPort->open (QIODevice::ReadWrite|QIODevice::Unbuffered) ) {
				qDebug () << "Successfully opened Serial Port";
				this->atPort->setBaudRate (BAUD115200);
				this->atPort->setDataBits (DATA_8);
				this->atPort->setParity (PAR_NONE);
				this->atPort->setStopBits (STOP_1);
				this->atPort->setFlowControl (FLOW_HARDWARE);
				this->atPort->setTimeout (PORT_TIMEOUT);

				result = true;
			} else {
				result = false;
			}
		} else {
			result = true;
		}
	}

	return result;
}

bool DeamonInterface::writeToAtPort () {
	bool result = false;

	this->mutex->lock();

	if ( false == this->atCommandQueue.isEmpty ()) {
		QString data = this->atCommandQueue.dequeue ().append (DeamonInterface::end);

		int written = this->atPort->write (data.toAscii (), data.length ());
		qDebug() << QTime::currentTime().toString("hh:mm:ss.zzz") << "[" << written << "]"<< "Write to AT port :"<< data;

		this->atPort->flush ();
		result = true;
	}

	this->mutex->unlock();
	return result;
}

bool DeamonInterface::readFromAtPort () {
	char buffer[1024];
	int availableBytes;

	availableBytes = this->atPort->bytesAvailable();
	if(availableBytes > 1024)
		availableBytes = 1024;

	int i = this->atPort->read(buffer, availableBytes);
	if (i != -1)
		buffer[i] = '\0';
	else
		buffer[0] = '\0';
	QString response = buffer;

	return this->parseResponse (response);

}

bool DeamonInterface::parseResponse (QString& value) {
	bool result = false;

	value.remove(ERROR_STRING).remove(DORMANT0).remove(DORMANT1);

	QStringList response = value.split("OK", QString::SkipEmptyParts);

	foreach (QString responseItem, response ) {
		qDebug() << "Parsing Item : " << responseItem;

		if (responseItem.contains(DeamonInterface::systemInformationResponse)){

			responseItem.remove(DeamonInterface::systemInformation).remove(DeamonInterface::systemInformationResponse);
			qDebug() << "System Information" << responseItem.simplified();
			QStringList information = responseItem.simplified().split(COMMA);

			emit serviceStatusUpdate(information.at(0).toInt());
			emit serviceDomainUpdate(information.at(1).toInt());
			emit roamingStatusUpdate(information.at(2).toInt());
			emit systemModeUpdate(information.at(3).toInt());
			emit simStatusUpdate(information.at(4).toInt());

		} else if (responseItem.contains(DeamonInterface::signalStrengthResponse)){

			responseItem.remove(DeamonInterface::signalStrength).remove(DeamonInterface::signalStrengthResponse).remove(OK_STRING).simplified();
			qDebug() << "Signal Strength:" << responseItem.simplified();
			emit signalStrengthUpdate(responseItem.simplified().toInt());

		} else if (responseItem.contains(DeamonInterface::modemVersionResponse)) {

			responseItem.remove(DeamonInterface::modemVersion).remove(DeamonInterface::modemVersionResponse);
			QStringList list = responseItem.split(LINE, QString::SkipEmptyParts);
			foreach (QString information, list){
				qDebug () << "Parsing Modem Version:" << information;

				if (information.contains(DeamonInterface::modemVersionResponseSoftwareVersion)) {
					qDebug () << "Software Version:" << information.remove(DeamonInterface::modemVersionResponseSoftwareVersion).simplified();
					emit softwareVersionUpdate(information.remove(DeamonInterface::modemVersionResponseSoftwareVersion).simplified());

				} else if (information.contains(DeamonInterface::modemVersionResponseCompilationDate)) {
					qDebug () << "Compile Date:" << information.remove(DeamonInterface::modemVersionResponseCompilationDate).simplified();
					emit compileDateUpdate(information.remove(DeamonInterface::modemVersionResponseCompilationDate).simplified());
				}
			}

		} else if (responseItem.contains(DeamonInterface::hdrcResponse)) {

			responseItem.remove(DeamonInterface::hdrc).remove(DeamonInterface::hdrcResponse);
			qDebug() << "DRC: " << responseItem.simplified();
			emit hdrcUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::cdmaEcioResponse)) {

			responseItem.remove(DeamonInterface::cdmaEcio).remove(DeamonInterface::cdmaEcioResponse);
			qDebug() << "CDMA ECIO:" << responseItem.simplified().right(CDMA_ECIO_LENGTH);
			emit cdmaEcioUpdate(responseItem.simplified().right(CDMA_ECIO_LENGTH));

		} else if (responseItem.contains(DeamonInterface::hdrEcioResponse)) {

			responseItem.remove(DeamonInterface::hdrEcio).remove(DeamonInterface::hdrEcioResponse);
			qDebug() << "HDR ECIO:" << responseItem.simplified();
			emit hdrEcioUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::sidResponse)) {

			responseItem.remove(DeamonInterface::sid).remove(DeamonInterface::sidResponse);
			qDebug() << "SID:" << responseItem.simplified();
			emit sidUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::esnResponse)) {

			QStringList list = responseItem.split(LINE);
			foreach (QString information, list){
				if (information.contains(DeamonInterface::esnResponse)) {
					information.remove(DeamonInterface::esnResponse);
					qDebug() << "ESN:" << information.simplified();
					emit esnUpdate(information.simplified());
				}
			}

		} else if (responseItem.contains(DeamonInterface::meidResponse)) {

			responseItem.remove(DeamonInterface::meid).remove(DeamonInterface::meid);
			qDebug() << "MEID:" << responseItem.simplified();
			emit meidUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::hardwareVersionResponse)) {

			responseItem.remove(DeamonInterface::hardwareVersion).remove(DeamonInterface::hardwareVersionResponse);
			qDebug() << "Hardware Version:" << responseItem.simplified();
			emit hardwareVersionUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::nidResponse)) {
			responseItem.remove(DeamonInterface::nid).remove(DeamonInterface::nidResponse);
			qDebug() << "Nid:" << responseItem.simplified();
			emit nidUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::prlResponse)) {

			responseItem.remove(DeamonInterface::prl).remove(DeamonInterface::prlResponse);
			qDebug() << "PRL:" << responseItem.simplified();
			emit prlUpdate(responseItem.simplified());

		} else if (responseItem.contains(DeamonInterface::flashMessageResponse)) {

			responseItem.remove(DeamonInterface::flashMessageResponse);
			qDebug () << "Flash Message:" << responseItem.split(LINE);
			emit flashMessageUpdate(responseItem.split(LINE).at(2).simplified());

		} else if (responseItem.contains(DeamonInterface::messageResponse)) {

			responseItem.remove(DeamonInterface::messageResponse);
			qDebug () << "Message:" << responseItem.split(LINE);
			emit flashMessageUpdate(responseItem.split(LINE).at(2).simplified());

		} else if (responseItem.contains(DeamonInterface::defaultMinResponse)) {

			responseItem.remove(DeamonInterface::defaultMin).remove(DeamonInterface::defaultMinResponse);
			qDebug () << "IMSI:" << responseItem.simplified();
			int min = responseItem.simplified().toInt();
			min /= 10000;
			min %= 1000000;

			if ( 0 == min ) {
				emit defaultMinUpdate();
			}

		} else if (responseItem.contains(DeamonInterface::programmingSuccessful)) {

			emit activation(true);

		} else if (responseItem.contains(DeamonInterface::programmingUnsuccessful)) {

			emit activation(false);

		} else if (responseItem.contains(DeamonInterface::cdmaRssiResponse)) {

			responseItem.remove(DeamonInterface::cdmaRssi).remove (DeamonInterface::cdmaRssiResponse);
			qDebug () << "CDMA RSSI:" << responseItem.simplified ();
			emit cdmaRssiUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::cdmaPnOffsetResponse)) {

			responseItem.remove(DeamonInterface::cdmaPnOffset).remove (DeamonInterface::cdmaPnOffsetResponse);
			qDebug () << "CDMA Pn Offset:" << responseItem.simplified ();
			emit pnOffsetUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::walshCodeResponse)) {

			responseItem.remove(DeamonInterface::walshCode).remove (DeamonInterface::walshCodeResponse);
			qDebug () << "Walsh Code:" << responseItem.simplified ();
			emit walshCodeUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::channelNumberResponse)) {

			responseItem.remove(DeamonInterface::channelNumber).remove (DeamonInterface::channelNumberResponse);
			qDebug () << "Channel Number:" << responseItem.simplified ();
			emit channelNumberUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::bandClassResponse)) {

			responseItem.remove(DeamonInterface::bandClass).remove (DeamonInterface::bandClassResponse);
			qDebug () << "Band Class:" << responseItem.simplified ();
			emit bandClassUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::txPowerResponse)) {

			responseItem.remove(DeamonInterface::txPower).remove (DeamonInterface::txPowerResponse);
			qDebug () << "Tx Power:" << responseItem.simplified ();
			emit txPowerUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::rxPowerResponse)) {

			responseItem.remove(DeamonInterface::rxPowerResponse).remove (DeamonInterface::rxPowerResponse);
			qDebug () << "Rx Power:" << responseItem.simplified ();
			emit rxPowerUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::bsPreviousResponse)) {

			responseItem.remove(DeamonInterface::bsPrevious).remove (DeamonInterface::bsPreviousResponse);
			qDebug () << "BS Previous:" << responseItem.simplified ();
			emit bsPreviousUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::msPreviousResponse)) {

			responseItem.remove(DeamonInterface::msPrevious).remove (DeamonInterface::msPreviousResponse);
			qDebug () << "MS Previous:" << responseItem.simplified ();
			emit msPreviousUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::previousInUseResponse)) {

			responseItem.remove(DeamonInterface::previousInUse).remove (DeamonInterface::previousInUseResponse);
			qDebug () << "Previous In Use:" << responseItem.simplified ();
			emit previousInUseUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::packetZoneIdResponse)) {

			responseItem.remove(DeamonInterface::packetZoneId).remove (DeamonInterface::packetZoneIdResponse);
			qDebug () << "Packet Zone ID:" << responseItem.simplified ();
			emit packetZoneIdUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::lastActiveCallStateResponse)) {

			responseItem.remove(DeamonInterface::lastActiveCallState).remove (DeamonInterface::lastActiveCallStateResponse);
			qDebug () << "Last Active State:" << responseItem.simplified ();
			emit lastActiveCallStateUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::hdrRssiResponse)) {

			responseItem.remove(DeamonInterface::hdrRssi).remove (DeamonInterface::hdrRssiResponse);
			qDebug () << "HDR RSSI:" << responseItem.simplified ();
			emit hdrRssiUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::perResponse)) {

			responseItem.remove(DeamonInterface::per).remove (DeamonInterface::perResponse);
			qDebug () << "PER:" << responseItem.simplified ();
			emit perUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::atStateResponse)) {

			responseItem.remove(DeamonInterface::atState).remove (DeamonInterface::atStateResponse);
			qDebug () << "AT State:" << responseItem.simplified ();
			emit atStateUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::dormantResponse)) {

			responseItem.remove(DeamonInterface::dormantState).remove (DeamonInterface::dormantResponse);
			qDebug () << "Dormant State:" << responseItem.simplified ();
			emit dormantStateUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::activeStatePnOffsetResponse)) {

			responseItem.remove(DeamonInterface::activeStatePnOffset).remove (DeamonInterface::activeStatePnOffsetResponse);
			qDebug () << "Active State Pn Offset:" << responseItem.simplified ();
			emit activeStatePnOffsetUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::neighborSetPnOffsetResponse)) {

			responseItem.remove(DeamonInterface::neighborSetPnOffset).remove (DeamonInterface::neighborSetPnOffsetResponse);
			qDebug () << "Neighbor Set Pn Offset:" << responseItem.simplified ();
			emit neighborSetPnOffsetUpdate(responseItem.simplified ());

		} else if (responseItem.contains(DeamonInterface::neighborSetEcioResponse)) {

			responseItem.remove(DeamonInterface::neighborSetEcio).remove (DeamonInterface::neighborSetEcioResponse);
			qDebug () << "Neighbor Set Ecio:" << responseItem.simplified ();
			emit neighborSetEcioUpdate(responseItem.simplified ());

		}
	}

	return result;
}

bool DeamonInterface::writeToAtPort(const QString& value){

	this->mutex->lock ();

	this->atCommandQueue.enqueue (value);

	this->mutex->unlock ();

	return false;
}

bool DeamonInterface::writeAtInformation(){
	this->mutex->lock ();

	this->atCommandQueue.enqueue (DeamonInterface::modemVersion);
	this->atCommandQueue.enqueue (DeamonInterface::hardwareVersion);
	this->atCommandQueue.enqueue (DeamonInterface::meid);
	this->atCommandQueue.enqueue (DeamonInterface::esn);
	this->atCommandQueue.enqueue (DeamonInterface::prl);

	this->mutex->unlock ();

	return false;
}

bool DeamonInterface::writeAtDiagnostic(){
	this->mutex->lock ();

	this->atCommandQueue.enqueue (DeamonInterface::sid);
	this->atCommandQueue.enqueue (DeamonInterface::nid);
	this->atCommandQueue.enqueue (DeamonInterface::sectorId);
	this->atCommandQueue.enqueue (DeamonInterface::hdrc);
	this->atCommandQueue.enqueue (DeamonInterface::cdmaEcio);
	this->atCommandQueue.enqueue (DeamonInterface::hdrEcio);
	this->atCommandQueue.enqueue (DeamonInterface::cdmaRssi);
	this->atCommandQueue.enqueue (DeamonInterface::cdmaPnOffset);
	this->atCommandQueue.enqueue (DeamonInterface::channelNumber);
	this->atCommandQueue.enqueue (DeamonInterface::bandClass);
	this->atCommandQueue.enqueue (DeamonInterface::txPower);
	this->atCommandQueue.enqueue (DeamonInterface::rxPower);
	this->atCommandQueue.enqueue (DeamonInterface::bsPrevious);
	this->atCommandQueue.enqueue (DeamonInterface::msPrevious);
	this->atCommandQueue.enqueue (DeamonInterface::previousInUse);
	this->atCommandQueue.enqueue (DeamonInterface::packetZoneId);
	this->atCommandQueue.enqueue (DeamonInterface::lastActiveCallState);
	this->atCommandQueue.enqueue (DeamonInterface::hdrRssi);
	this->atCommandQueue.enqueue (DeamonInterface::per);
	this->atCommandQueue.enqueue (DeamonInterface::atState);
	this->atCommandQueue.enqueue (DeamonInterface::dormantState);
	this->atCommandQueue.enqueue (DeamonInterface::activeStatePnOffset);
	this->atCommandQueue.enqueue (DeamonInterface::neighborSetPnOffset);
	this->atCommandQueue.enqueue (DeamonInterface::neighborSetEcio);
	this->mutex->unlock ();
	return false;
}

bool DeamonInterface::stop (){
	this->running = false;

	return true;
}

const QString DeamonInterface::at("AT");
const QString DeamonInterface::end("\x0D\x0A");
const QString DeamonInterface::dial("AT+CDV");
const QString DeamonInterface::toneDial("AT$VTS=");

const QString DeamonInterface::echoOff("ATE0");
const QString DeamonInterface::echoOn("ATE1");

const QString DeamonInterface::enableFlashMessage("AT+CNMI=1,2,0,1,0");
const QString DeamonInterface::enableMessage("AT$QCCNMI=1,2,2,1,1");

const QString DeamonInterface::programmingSuccessful("Programming Successful");
const QString DeamonInterface::programmingUnsuccessful("Programming Unsuccessful");

const QString DeamonInterface::signalStrength("AT+CSQ");
const QString DeamonInterface::signalStrengthResponse(", 99");

const QString DeamonInterface::systemInformation("AT^SYSINFO");
const QString DeamonInterface::systemInformationResponse("^SYSINFO:");

const QString DeamonInterface::modemVersion("AT$VER");
const QString DeamonInterface::modemVersionResponse("$VER:");
const QString DeamonInterface::modemVersionResponseCompilationDate("rel_time:");
const QString DeamonInterface::modemVersionResponseSoftwareVersion("version:");

const QString DeamonInterface::hardwareVersion("AT^HWVER");
const QString DeamonInterface::hardwareVersionResponse("Part=1280  version=");

const QString DeamonInterface::meid("AT^GSN");
const QString DeamonInterface::meidResponse("0x");

const QString DeamonInterface::sid("AT+CSS");
const QString DeamonInterface::sidResponse("?,");

const QString DeamonInterface::nid("AT$NID?");
const QString DeamonInterface::nidResponse("$NID:");

const QString DeamonInterface::prl("AT$PRL?");
const QString DeamonInterface::prlResponse("$PRL:");

const QString DeamonInterface::sectorId("AT$SECTORID?");
const QString DeamonInterface::sectorIdResponse("$SECTORID:");

const QString DeamonInterface::hdrc("AT$QCHDRC?");
const QString DeamonInterface::hdrcResponse("$QCHDRC:");

const QString DeamonInterface::cdmaEcio("AT$CECIO?");
const QString DeamonInterface::cdmaEcioResponse("$CECIO:");

const QString DeamonInterface::hdrEcio("AT$HAECIO?");
const QString DeamonInterface::hdrEcioResponse("$HAECIO:");


const QString DeamonInterface::cdmaRssi("AT$CRSSI?");
const QString DeamonInterface::cdmaRssiResponse("$CRSSI:");

const QString DeamonInterface::cdmaPnOffset("AT$CPNOFFSET?");
const QString DeamonInterface::cdmaPnOffsetResponse("$CPNOFFSET:");

const QString DeamonInterface::walshCode("AT$WALSH?");
const QString DeamonInterface::walshCodeResponse("$CWALSH:");

const QString DeamonInterface::channelNumber("AT$CCHANNEL?");
const QString DeamonInterface::channelNumberResponse("$CCHANNEL:");

const QString DeamonInterface::bandClass("AT$CBAND?");
const QString DeamonInterface::bandClassResponse("$CBAND:");

const QString DeamonInterface::txPower("AT$HTXPOWER?");
const QString DeamonInterface::txPowerResponse("$HTXPOWER:");

const QString DeamonInterface::rxPower("AT$HRXPOWER?");
const QString DeamonInterface::rxPowerResponse("$HRXPOWER:");

const QString DeamonInterface::bsPrevious("AT$CBSPREV?");
const QString DeamonInterface::bsPreviousResponse("$CBSPREV:");

const QString DeamonInterface::msPrevious("AT$CMSPREV?");
const QString DeamonInterface::msPreviousResponse("$CMSPREV:");

const QString DeamonInterface::previousInUse("AT$CPREVINUSE?");
const QString DeamonInterface::previousInUseResponse("$CPREVINUSE:");

const QString DeamonInterface::packetZoneId("AT$CPZONEID?");
const QString DeamonInterface::packetZoneIdResponse("$CPZONEID:");

const QString DeamonInterface::lastActiveCallState("AT$CALLSTATE?");
const QString DeamonInterface::lastActiveCallStateResponse("$CALLSTATE:");

const QString DeamonInterface::hdrRssi("AT$HRSSI?");
const QString DeamonInterface::hdrRssiResponse("$HRSSI:");

const QString DeamonInterface::per("AT$HPER?");
const QString DeamonInterface::perResponse("$HPER:");

const QString DeamonInterface::atState("AT$HATSTATE?");
const QString DeamonInterface::atStateResponse("$HATSTATE:");

const QString DeamonInterface::dormantState("AT$HDORMSTATE?");
const QString DeamonInterface::dormantResponse("$HDORMSTATE:");

const QString DeamonInterface::activeStatePnOffset("AT$HAPNOFFSET?");
const QString DeamonInterface::activeStatePnOffsetResponse("$HAPNOFFSET:");

const QString DeamonInterface::neighborSetPnOffset("AT$HNPNOFFSET?");
const QString DeamonInterface::neighborSetPnOffsetResponse("$HNPNOFFSET:");

const QString DeamonInterface::neighborSetEcio("AT$HNECIO?");
const QString DeamonInterface::neighborSetEcioResponse("$HNPNECIO:");

const QString DeamonInterface::esn("ATI");
const QString DeamonInterface::esnResponse("ESN:");

const QString DeamonInterface::defaultMin("AT+CIMI");
const QString DeamonInterface::defaultMinResponse("404");

const QString DeamonInterface::flashMessageResponse("$CFT: \"REC UNREAD\",");
const QString DeamonInterface::messageResponse("$QCMT: \"REC UNREAD\",");

const QString DeamonInterface::setModeZero("AT^PREFMODE=8");
const QString DeamonInterface::setModeOne("AT^PREFMODE=2");
const QString DeamonInterface::setModeTwo("AT^PREFMODE=4");
const QString DeamonInterface::setModeThree("AT^PREFMODE=4");
