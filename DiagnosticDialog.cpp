#include "DiagnosticDialog.h"

#include "DeamonInterface.h"
#include "Defines.h"

#include <QDebug>
#include <QIcon>
#include <QTimer>

DiagnosticDialog::DiagnosticDialog(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));
	this->setWindowTitle (DIAGNOSTIC_LABEL);

	this->settings = new QSettings(REGISTRY_DIAGNOSTIC, QSettings::NativeFormat);

	this->layout = new QFormLayout;
	this->layout->setLabelAlignment (Qt::AlignRight);

	this->sid = new QLineEdit(settings->value(SID_NID_KEY, "0").toString(), this);
	this->sid->setReadOnly (true);
	this->layout->addRow (SID_LABEL, this->sid);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(sidUpdate(QString)), SLOT(onSidNidUpdate(QString)));

	this->sectorId = new QLineEdit(settings->value(SECTOR_ID_KEY, "0").toString(), this);
	this->sectorId->setReadOnly (true);
	this->layout->addRow (SECTOR_ID_LABEL, this->sectorId);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(sectorIdUpdate(QString)), SLOT(onSectorIdUpdate(QString)));

	this->drc = new QLineEdit(settings->value(DRC_KEY, "0").toString(), this);
	this->drc->setReadOnly (true);
	this->layout->addRow (DRC_LABEL, this->drc);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(hdrcUpdate(QString)), SLOT(onHdrcUpdate(QString)));

	this->cdmaEcio = new QLineEdit(settings->value(CDMA_ECIO_KEY, "0").toString(), this);
	this->cdmaEcio->setReadOnly (true);
	this->layout->addRow (CDMA_ECIO_LABEL, this->cdmaEcio);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(cdmaEcioUpdate(QString)), SLOT(onCdmaEcioUpdate(QString)));

	this->hdrEcio = new QLineEdit(settings->value(HDR_ECIO_KEY, "0").toString(), this);
	this->hdrEcio->setReadOnly (true);
	this->layout->addRow (HDR_ECIO_LABEL, this->hdrEcio);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(hdrEcioUpdate(QString)), SLOT(onHdrEcioUpdate(QString)));

	this->cdmaRssi = new QLineEdit(settings->value(CDMA_RSSI_KEY, "0").toString(), this);
	this->cdmaRssi->setReadOnly (true);
	this->layout->addRow (CDMA_RSSI_LABEL, this->cdmaRssi);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(cdmaRssiUpdate(QString)), SLOT(onCdmaRssiUpdate(QString)));

	this->cdmaPnOffset = new QLineEdit(settings->value(CDMA_PN_OFFSET_KEY, "0").toString(), this);
	this->cdmaPnOffset->setReadOnly (true);
	this->layout->addRow (CDMA_PN_OFFSET_LABEL, this->cdmaPnOffset);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(pnOffsetUpdate(QString)), SLOT(onPnOffsetUpdate(QString)));

	this->walshCode = new QLineEdit(settings->value(WALSH_CODE_KEY, "0").toString(), this);
	this->walshCode->setReadOnly (true);
	this->layout->addRow (WALSH_CODE_LABEL, this->walshCode);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(walshCodeUpdate(QString)), SLOT(onWalshCodeUpdate(QString)));

	this->channelNumber = new QLineEdit(settings->value(CHANNEL_NUMBER_KEY, "0").toString(), this);
	this->channelNumber->setReadOnly (true);
	this->layout->addRow (CHANNEL_NUMBER_LABEL, this->channelNumber);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(channelNumberUpdate(QString)), SLOT(onChannelNumberUpdate(QString)));

	this->bandClass = new QLineEdit(settings->value(BAND_CLASS_KEY, "0").toString(), this);
	this->bandClass->setReadOnly (true);
	this->layout->addRow (BAND_CLASS_LABEL, this->bandClass);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(bandClassUpdate(QString)), SLOT(onBandClassUpdate(QString)));

	this->txPower = new QLineEdit(settings->value(TX_POWER_KEY, "0").toString(), this);
	this->txPower->setReadOnly (true);
	this->layout->addRow (TX_POWER_LABEL, this->txPower);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(txPowerUpdate(QString)), SLOT(onTxPowerUpdate(QString)));

	this->rxPower = new QLineEdit(settings->value(RX_POWER_KEY, "0").toString(), this);
	this->rxPower->setReadOnly (true);
	this->layout->addRow (RX_POWER_LABEL, this->rxPower);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(rxPowerUpdate(QString)), SLOT(onRxPowerUpdate(QString)));

	this->bsPrevious = new QLineEdit(settings->value(BS_PREVIOUS_KEY, "0").toString(), this);
	this->bsPrevious->setReadOnly (true);
	this->layout->addRow (BS_PREVIOUS_LABEL, this->bsPrevious);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(bsPreviousUpdate(QString)), SLOT(onBsPreviousUpdate(QString)));

	this->msPrevious = new QLineEdit(settings->value(MS_PREVIOUS_KEY, "0").toString(), this);
	this->msPrevious->setReadOnly (true);
	this->layout->addRow (MS_PREVIOUS_LABEL, this->msPrevious);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(msPreviousUpdate(QString)), SLOT(onMsPreviousUpdate(QString)));

	this->previousInUse = new QLineEdit(settings->value(PREVIOUS_IN_USE_KEY, "0").toString(), this);
	this->previousInUse->setReadOnly (true);
	this->layout->addRow (PREVIOUS_IN_USE_LABEL, this->previousInUse);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(previousInUseUpdate(QString)), SLOT(onPreviousInUseUpdate(QString)));

	this->packetZoneId = new QLineEdit(settings->value(PACKET_ZONE_ID_KEY, "0").toString(), this);
	this->packetZoneId->setReadOnly (true);
	this->layout->addRow (PACKET_ZONE_ID_LABEL, this->packetZoneId);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(packetZoneIdUpdate(QString)), SLOT(onPacketZoneIdUpdate(QString)));

	this->lastActiveCallState = new QLineEdit(settings->value(LAST_ACTIVE_CALL_STATE_KEY, "0").toString(), this);
	this->lastActiveCallState->setReadOnly (true);
	this->layout->addRow (LAST_ACTIVE_CALL_STATE_LABEL, this->lastActiveCallState);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(lastActiveCallStateUpdate(QString)), SLOT(onLastActiveCallStateUpdate(QString)));


	this->hdrRssi = new QLineEdit(settings->value(HDR_RSSI_KEY, "0").toString(), this);
	this->hdrRssi->setReadOnly (true);
	this->layout->addRow (HDR_RSSI_LABEL, this->hdrRssi);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(hdrRssiUpdate(QString)), SLOT(onHdrRssiUpdate(QString)));

	this->per = new QLineEdit(settings->value(PER_KEY, "0").toString(), this);
	this->per->setReadOnly (true);
	this->layout->addRow (PER_LABEL, this->per);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(perUpdate(QString)), SLOT(onPerUpdate(QString)));

	this->atState = new QLineEdit(settings->value(AT_STATE_KEY, "0").toString(), this);
	this->atState->setReadOnly (true);
	this->layout->addRow (AT_STATE_LABEL, this->atState);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(atStateUpdate(QString)), SLOT(onAtStateUpdate(QString)));

	this->dormantState = new QLineEdit(settings->value(DORMANT_STATE_KEY, "0").toString(), this);
	this->dormantState->setReadOnly (true);
	this->layout->addRow (DORMANT_STATE_LABEL, this->dormantState);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(dormantStateUpdate(QString)), SLOT(onDormantStateUpdate(QString)));

	this->activeStatePnOffset = new QLineEdit(settings->value(ACTIVE_STATE_PN_OFFSET_KEY, "0").toString(), this);
	this->activeStatePnOffset->setReadOnly (true);
	this->layout->addRow (ACTIVE_STATE_PN_OFFSET_LABEL, this->activeStatePnOffset);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(activeStatePnOffsetUpdate(QString)), SLOT(onActiveStatePnOffsetUpdate(QString)));

	this->neighborSetPnOffset = new QLineEdit(settings->value(NEIGHBOR_SET_ECIO_LABEL, "0").toString(), this);
	this->neighborSetPnOffset->setReadOnly (true);
	this->layout->addRow (NEIGHBOR_SET_PN_OFFSET_LABEL, this->neighborSetPnOffset);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(neighborSetPnOffsetUpdate(QString)), SLOT(onNeighborSetPnOffsetUpdate(QString)));

	this->neighborSetEcio = new QLineEdit(settings->value(NEIGHBOR_SET_ECIO_KEY, "0").toString(), this);
	this->neighborSetEcio->setReadOnly (true);
	this->layout->addRow (NEIGHBOR_SET_ECIO_LABEL, this->neighborSetEcio);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(neighborSetEcioUpdate(QString)), SLOT(onNeighborSetEcioUpdate(QString)));

	this->setLayout (this->layout);

	this->updateTimer = new QTimer();
	QObject::connect (this->updateTimer, SIGNAL(timeout()), SLOT(onUpdateTimeout()));
}

DiagnosticDialog::~DiagnosticDialog () {

}

void DiagnosticDialog::showEvent(QShowEvent* event) {
	this->updateTimer->start(DIAGNOSTIC_CYCLE_TIMEOUT);

	QWidget::showEvent(event);

}

void DiagnosticDialog::hideEvent (QHideEvent* event) {
	this->updateTimer->stop();

	QWidget::hideEvent (event);

}

bool DiagnosticDialog::onUpdateTimeout(){
	DeamonInterface::getInstance ()->writeAtDiagnostic ();

	return true;
}

bool DiagnosticDialog::onSidNidUpdate(const QString& result){
	this->sid->setText(result);
	this->settings->setValue(SID_NID_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onSectorIdUpdate(const QString& result){
	this->sectorId->setText(result);
	this->settings->setValue(SECTOR_ID_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onHdrcUpdate(const QString& result){
	this->drc->setText(result);
	this->settings->setValue(DRC_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onHdrEcioUpdate(const QString& result){
	this->hdrEcio->setText(result);
	this->settings->setValue(HDR_ECIO_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onCdmaEcioUpdate(const QString& result){
	this->cdmaEcio->setText(result);
	this->settings->setValue(CDMA_ECIO_KEY, QVariant(result));

	return true;
}


bool DiagnosticDialog::onCdmaRssiUpdate(const QString& result){
	this->cdmaRssi->setText(result);
	this->settings->setValue(CDMA_RSSI_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onPnOffsetUpdate(const QString& result){
	this->cdmaPnOffset->setText(result);
	this->settings->setValue(CDMA_PN_OFFSET_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onWalshCodeUpdate(const QString& result){
	this->walshCode->setText(result);
	this->settings->setValue(WALSH_CODE_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onChannelNumberUpdate(const QString& result){
	this->channelNumber->setText(result);
	this->settings->setValue(CHANNEL_NUMBER_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onBandClassUpdate(const QString& result){
	this->bandClass->setText(result);
	this->settings->setValue(BAND_CLASS_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onTxPowerUpdate(const QString& result){
	this->txPower->setText(result);
	this->settings->setValue(TX_POWER_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onRxPowerUpdate(const QString& result){
	this->rxPower->setText(result);
	this->settings->setValue(RX_POWER_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onBsPreviousUpdate(const QString& result){
	this->bsPrevious->setText(result);
	this->settings->setValue(BS_PREVIOUS_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onMsPreviousUpdate(const QString& result){
	this->msPrevious->setText(result);
	this->settings->setValue(MS_PREVIOUS_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onPreviousInUseUpdate(const QString& result){
	this->previousInUse->setText(result);
	this->settings->setValue(PREVIOUS_IN_USE_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onPacketZoneIdUpdate(const QString& result){
	this->packetZoneId->setText(result);
	this->settings->setValue(PACKET_ZONE_ID_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onLastActiveCallStateUpdate(const QString& result){
	this->lastActiveCallState->setText(result);
	this->settings->setValue(LAST_ACTIVE_CALL_STATE_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onHdrRssiUpdate(const QString& result){
	this->hdrRssi->setText(result);
	this->settings->setValue(HDR_RSSI_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onPerUpdate(const QString& result){
	this->per->setText(result);
	this->settings->setValue(PER_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onAtStateUpdate(const QString& result){
	this->atState->setText(result);
	this->settings->setValue(AT_STATE_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onDormantStateUpdate(const QString& result){
	this->dormantState->setText(result);
	this->settings->setValue(DORMANT_STATE_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onActiveStatePnOffsetUpdate(const QString& result){
	this->activeStatePnOffset->setText(result);
	this->settings->setValue(ACTIVE_STATE_PN_OFFSET_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onNeighborSetPnOffsetUpdate(const QString& result){
	this->neighborSetPnOffset->setText(result);
	this->settings->setValue(NEIGHBOR_SET_PN_OFFSET_KEY, QVariant(result));

	return true;
}

bool DiagnosticDialog::onNeighborSetEcioUpdate(const QString& result){
	qDebug () << "received Neighbor Set Ecio" << result;
	this->neighborSetEcio->setText(result);
	this->settings->setValue(NEIGHBOR_SET_ECIO_KEY, QVariant(result));

	return true;
}
