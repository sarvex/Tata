#include "InformationWidget.h"

#include "DeamonInterface.h"
#include "Defines.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QDebug>
#include <QPainter>

InformationWidget::InformationWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadInformation()), SLOT(onReloadInformation()));

	this->settings = new QSettings (REGISTRY_ABOUT, QSettings::NativeFormat);

	this->dialerInformationLabel = new QLabel(DIALER_INFORMATION_LABEL, this);
	this->dialerInformationLabel->setGeometry (UserInterface::tabInformationDialerInformationLabel);
	this->dialerInformationLabel->setAlignment(Qt::AlignCenter);

	this->driverVersionLabel = new QLabel(DRIVER_INFORMATION_LABEL, this);
	this->driverVersionLabel->setGeometry (UserInterface::tabInformationDriverVersionLabel);
	this->driverVersionLabel->setAlignment(Qt::AlignRight);

	this->installDateLabel = new QLabel(INSTALL_DATE_LABEL, this);
	this->installDateLabel->setGeometry (UserInterface::tabInformationInstallDateLabel);
	this->installDateLabel->setAlignment(Qt::AlignRight);

	this->compileDateLabel = new QLabel(COMPILE_DATE_LABEL, this);
	this->compileDateLabel->setGeometry (UserInterface::tabInformationCompileDateLabel);
	this->compileDateLabel->setAlignment(Qt::AlignRight);

	this->prlLabel = new QLabel(PRL_LABEL, this);
	this->prlLabel->setGeometry (UserInterface::tabInformationPrlLabel);
	this->prlLabel->setAlignment(Qt::AlignRight);

	this->meidLabel = new QLabel(MEID_LABEL, this);
	this->meidLabel->setGeometry (UserInterface::tabInformationEsnLabel);
	this->meidLabel->setAlignment(Qt::AlignRight);

	this->esnLabel = new QLabel(ESN_LABEL, this);
	this->esnLabel->setGeometry (UserInterface::tabInformationPEsnLabel);
	this->esnLabel->setAlignment(Qt::AlignRight);

	this->softwareVersionLabel = new QLabel(SOFTWARE_VERSION_LABEL, this);
	this->softwareVersionLabel->setGeometry (UserInterface::tabInformationSoftwareVersionLabel);
	this->softwareVersionLabel->setAlignment(Qt::AlignRight);

	this->hardwareVersionLabel = new QLabel(HARDWARE_VERSION_LABEL, this);
	this->hardwareVersionLabel->setGeometry (UserInterface::tabInformationHarwareVersionLabel);
	this->hardwareVersionLabel->setAlignment(Qt::AlignRight);


	this->driverVersion = new QLabel(this->settings->value(DRIVER_VERSION_KEY, "0").toString(), this);
	this->driverVersion->setGeometry (UserInterface::tabInformationDriverVersion);
	this->driverVersion->setAlignment(Qt::AlignLeft);

	this->installDate = new QLabel(this->settings->value(INSTALL_DATE_KEY, "0").toString(), this);
	this->installDate->setGeometry (UserInterface::tabInformationInstallDate);
	this->installDate->setAlignment(Qt::AlignLeft);

	this->compileDate = new QLabel(this->settings->value(COMPILE_DATE_KEY, "0").toString(), this);
	this->compileDate->setGeometry (UserInterface::tabInformationCompileDate);
	this->compileDate->setAlignment(Qt::AlignLeft);

	this->prl = new QLabel(this->settings->value(PRL_KEY, "0").toString(), this);
	this->prl->setGeometry (UserInterface::tabInformationPrl);
	this->prl->setAlignment(Qt::AlignLeft);

	this->meid = new QLabel(this->settings->value(ESN_KEY, "0").toString(), this);
	this->meid->setGeometry (UserInterface::tabInformationEsn);
	this->meid->setAlignment(Qt::AlignLeft);

	this->esn = new QLabel(this->settings->value(PESN_KEY, "0").toString(), this);
	this->esn->setGeometry (UserInterface::tabInformationPEsn);
	this->esn->setAlignment(Qt::AlignLeft);

	this->softwareVersion = new QLabel(this->settings->value(SOFTWARE_VERSION_KEY, "0").toString(), this);
	this->softwareVersion->setGeometry (UserInterface::tabInformationSoftwareVersion);
	this->softwareVersion->setAlignment(Qt::AlignLeft);

	this->hardwareVersion = new QLabel(this->settings->value(HARDWARE_VERSION_KEY, "0").toString(), this);
	this->hardwareVersion->setGeometry (UserInterface::tabInformationHarwareVersion);
	this->hardwareVersion->setAlignment(Qt::AlignLeft);

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));

	QObject::connect (DeamonInterface::getInstance(), SIGNAL(prlUpdate(const QString&)), SLOT(onPrlUpdate(const QString&)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(meidUpdate(const QString&)), SLOT(onEsnUpdate(const QString&)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(hardwareVersionUpdate(const QString&)), SLOT(onHardwareVersionUpdate(const QString&)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(compileDateUpdate(const QString&)), SLOT(onCompileDateUpdated(const QString&)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(esnUpdate(const QString&)), SLOT(onPEsnUpdated(const QString&)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(softwareVersionUpdate(const QString&)), SLOT(onSoftwareVersionUpdated(const QString&)));
}

InformationWidget::~InformationWidget () {

}

bool InformationWidget::updateInformation () {
	this->driverVersion->setText(this->settings->value(DRIVER_VERSION_KEY, "0").toString());
	this->installDate->setText(this->settings->value(INSTALL_DATE_KEY, "0").toString());
	this->compileDate->setText(this->settings->value(COMPILE_DATE_KEY, "0").toString());
	this->prl->setText(this->settings->value(PRL_KEY, "0").toString());
	this->meid->setText(this->settings->value(ESN_KEY, "0").toString());
	this->esn->setText(this->settings->value(PESN_KEY, "0").toString());
	this->softwareVersion->setText(this->settings->value(SOFTWARE_VERSION_KEY, "0").toString());
	this->hardwareVersion->setText(this->settings->value(HARDWARE_VERSION_KEY, "0").toString());

	return DeamonInterface::getInstance()->writeAtInformation();
}

void InformationWidget::showEvent (QShowEvent* event){
	this->updateInformation();

	QWidget::showEvent(event);
}


bool InformationWidget::onCompileDateUpdated(const QString& value){
	this->compileDate->setText(value);
	this->settings->setValue(COMPILE_DATE_KEY, QVariant(value));

	return true;
}

bool InformationWidget::onPrlUpdate(const QString& value){
	this->prl->setText(value);
	this->settings->setValue(PRL_KEY, QVariant(value));

	return (true);
}

bool InformationWidget::onEsnUpdate(const QString& value){
	this->meid->setText(value);
	this->settings->setValue(ESN_KEY, QVariant(value));

	return (true);
}

bool InformationWidget::onPEsnUpdated(const QString& value){
	this->esn->setText(value);
	this->settings->setValue(PESN_KEY, QVariant(value));

	return true;
}

bool InformationWidget::onSoftwareVersionUpdated(const QString& value){
	this->softwareVersion->setText(value);
	this->settings->setValue(SOFTWARE_VERSION_KEY, QVariant(value));

	return true;
}

bool InformationWidget::onHardwareVersionUpdate(const QString& value){
	this->hardwareVersion->setText(value);
	this->settings->setValue(HARDWARE_VERSION_KEY, QVariant(value));

	return (true);
}

bool InformationWidget::onOkClicked() {
	bool result = false;

	emit completed();
	return (result);
}

bool InformationWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}

void InformationWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

bool InformationWidget::onReloadInformation(){
	this->updateInformation();

	return (true);
}
