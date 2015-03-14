#include "TestDialog.h"

#include "DeamonInterface.h"
#include "Defines.h"
#include "Profile.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <windows.h>
#include <ras.h>
#include <raserror.h>

#include <QDebug>
#include <QDir>
#include <QIcon>
#include <QProcess>
#include <QSettings>
#include <QTextStream>

#include "SerialEnumerator.h"
#include "SerialPort.h"

TestDialog::TestDialog(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));

	this->startTest = new QPushButton(START_TEST_STRING, this);
	QObject::connect (this->startTest, SIGNAL(clicked()), SLOT(onStartTestClicked()));

	this->formLayout = new QFormLayout;
	this->formLayout->setLabelAlignment (Qt::AlignRight);

	this->driverTest = new QLabel(UNKNOWN, this);
	this->formLayout->addRow (DRIVER_TEST_LABEL, this->driverTest);

	this->registryTest = new QLabel(UNKNOWN, this);
	this->formLayout->addRow (REGISTRY_TEST_LABEL, this->registryTest);

	this->modemTest = new QLabel(UNKNOWN, this);
	this->formLayout->addRow (MODEM_TEST_LABEL, this->modemTest);

	this->portTest = new QLabel(UNKNOWN, this);
	this->formLayout->addRow (PORT_TEST_LABEL, this->portTest);

	this->profilesTest = new QLabel(UNKNOWN, this);
	this->formLayout->addRow (PROFILES_TEST_LABEL, this->profilesTest);

	this->layout = new QVBoxLayout;
	this->layout->addWidget (this->startTest);
	this->layout->addLayout (this->formLayout);
	this->setLayout (this->layout);
}

TestDialog::~TestDialog () {

}

bool TestDialog::onStartTestClicked () {

	this->testLog = new QFile(DEVICE_TEST_FILE_NAME);
	this->testLog->open(QIODevice::WriteOnly|QIODevice::Truncate);

	this->testStream = new QTextStream(this->testLog);

	this->driverTest->setText(this->testDriver()?PASS_STRING:FAIL_STRING);
	this->registryTest->setText(this->testRegistry()?PASS_STRING:FAIL_STRING);
	this->modemTest->setText(this->testModem()?PASS_STRING:FAIL_STRING);
	this->portTest->setText(this->testPort()?PASS_STRING:FAIL_STRING);
	this->profilesTest->setText(this->testProfiles()?PASS_STRING:FAIL_STRING);

	delete this->testLog;
	this->testLog = NULL;

	delete this->testStream;
	this->testLog = NULL;
	return (true);
}

bool TestDialog::testDriver() {
	QStringList environment = QProcess::systemEnvironment();

	qDebug () << "System Environment :" << environment;
	QString driverFilePath;
	foreach ( QString variable, environment) {
		if (variable.contains ("WINDIR")) {
			driverFilePath = variable.remove ("WINDIR=").simplified ();
		}
	}

	driverFilePath = QDir::fromNativeSeparators(driverFilePath);
	driverFilePath += DRIVER_FILE_PATH;

	qDebug () << "driverFilePath :" << driverFilePath;

	QFileInfo driverfileInformation (driverFilePath);

	if ( true == driverfileInformation.exists()) {
		*this->testStream << "Found Driver at " << driverFilePath << endl << endl;
		return (true);
	} else {
		*this->testStream << "No Driver found at " << driverFilePath << endl << endl;
		return (false);
	}

}

bool TestDialog::testRegistry() {
	QSettings settings(REGISTRY_ROOT, QSettings::NativeFormat);

	*this->testStream << REGISTRY_ROOT << "\\" << REGISTRY_KEY_ONE << " : " << settings.value(REGISTRY_KEY_ONE, "0" ).toInt() << endl;
	*this->testStream << REGISTRY_ROOT << "\\" << REGISTRY_KEY_TWO << " : " << settings.value(REGISTRY_KEY_TWO, "0" ).toInt() << endl;
	*this->testStream << REGISTRY_ROOT << "\\" << REGISTRY_KEY_THREE << " : " << settings.value(REGISTRY_KEY_THREE, "0" ).toInt() << endl;
	*this->testStream << REGISTRY_ROOT << "\\" << REGISTRY_KEY_FOUR << " : " << settings.value(REGISTRY_KEY_FOUR, "0" ).toInt() << endl << endl;

	if (REGISTRY_KEY_ONE_VALUE != settings.value(REGISTRY_KEY_ONE, "0" ).toInt()) return (false);
	if (REGISTRY_KEY_TWO_VALUE != settings.value(REGISTRY_KEY_TWO, "0" ).toInt()) return (false);
	if (REGISTRY_KEY_THREE_VALUE != settings.value(REGISTRY_KEY_THREE, "0" ).toInt()) return (false);
	if (REGISTRY_KEY_FOUR_VALUE != settings.value(REGISTRY_KEY_FOUR, "0" ).toInt()) return (false);

	return (true);
}

bool TestDialog::testModem() {
	bool result = false;

	DWORD bufferSize = 0;
	DWORD returnValue = ERROR_SUCCESS;
	DWORD numberOfDevices = 0;
	LPRASDEVINFO rasDeviceInformation = NULL;

	returnValue = RasEnumDevices(rasDeviceInformation, &bufferSize, &numberOfDevices);

	if (ERROR_BUFFER_TOO_SMALL == returnValue ){
		// Allocate the memory needed for the array of RAS structure(s).
		rasDeviceInformation = (LPRASDEVINFO) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufferSize);
		if (rasDeviceInformation == NULL){
			qDebug() << "HeapAlloc failed!";
			return false;
		}
		// The first RASDEVINFO structure in the array must contain the structure size
		rasDeviceInformation[0].dwSize = sizeof(RASDEVINFO);

		// Call RasEnumDevices to enumerate RAS devices
		returnValue = RasEnumDevices(rasDeviceInformation, &bufferSize, &numberOfDevices);

		// If successful, print the names of the RAS devices
		if (ERROR_SUCCESS == returnValue){
			for (unsigned int index = 0; index < numberOfDevices; index++){
				if ( OLIVE_DEVICE_NAME == QString::fromWCharArray(rasDeviceInformation[index].szDeviceName)) {
					*this->testStream << "Found Modem : " << QString::fromWCharArray(rasDeviceInformation[index].szDeviceName) << endl << endl;
					result = true;
					break;
				}
			}
		}

		//Deallocate memory for the connection buffer
		HeapFree(GetProcessHeap(), 0, rasDeviceInformation);
		rasDeviceInformation = NULL;
	}

	return (result);
}

bool TestDialog::testPort() {
	bool result = false;

	QList<PortInformation> ports = SerialEnumerator::getPorts();
	for (int index = 0; index < ports.size(); index++) {
		if (VENDOR_ID == ports.at(index).vendorID) {
			if (PRODUCT_ID == ports.at(index).productID) {
				*this->testStream << "Found Port : " <<  ports.at(index).friendName << endl;
			}
		}
	}

	*this->testStream << endl;
	return (result);
}

bool TestDialog::testProfiles() {
	QList <Profile> profileList = DeamonSetting::getInstance ()->getProfiles ();

	foreach ( Profile profile, profileList) {
		*this->testStream << "Profile Name : " << profile.getName () << endl;
		*this->testStream << "Username : " << profile.getUserName () << endl;
		*this->testStream << "Password : " << profile.getPassword () << endl;
		*this->testStream << "Number : " << profile.getNumber () << endl << endl;
	}
	return (true);
}
