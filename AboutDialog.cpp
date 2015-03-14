#include "AboutDialog.h"

#include "DeamonInterface.h"
#include "Defines.h"
#include "DeamonSetting.h"

#include <QIcon>

AboutDialog::AboutDialog(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));
	this->setWindowTitle (DIALER_INFORMATION_LABEL);

	this->settings = new QSettings (REGISTRY_ABOUT, QSettings::NativeFormat);
	this->layout = new QFormLayout;
	this->layout->setLabelAlignment (Qt::AlignRight);

	this->driverVersion = new QLabel(settings->value(DRIVER_VERSION_KEY, "0").toString(), this);
	this->layout->addRow (DRIVER_INFORMATION_LABEL, this->driverVersion);

	this->installDate = new QLabel(settings->value(INSTALL_DATE_KEY, "0").toString(), this);
	this->layout->addRow (INSTALL_DATE_LABEL, this->installDate);

	this->compileDate = new QLabel(settings->value(COMPILE_DATE_KEY, "0").toString(), this);
	this->layout->addRow (COMPILE_DATE_LABEL, this->compileDate);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(compileDateUpdate(QString)), SLOT(onCompileDateUpdated(QString)));

	this->prl = new QLabel(settings->value(settings->value(PRL_KEY, "0").toString(), "0").toString(), this);
	this->layout->addRow (PRL_LABEL, this->prl);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(prlUpdate(QString)), SLOT(onPrlUpdated(QString)));

	this->meid = new QLabel(settings->value(settings->value(ESN_KEY, "0").toString(), "0").toString(), this);
	this->layout->addRow (MEID_LABEL, this->meid);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(meidUpdate(QString)), SLOT(onEsnDateUpdated(QString)));

	this->esn = new QLabel(settings->value(settings->value(PESN_KEY, "0").toString(), "0").toString(), this);
	this->layout->addRow (ESN_LABEL, this->esn);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(esnUpdate(QString)), SLOT(onPEsnUpdated(QString)));

	this->softwareVersion = new QLabel(settings->value(SOFTWARE_VERSION_KEY, "0").toString(), this);
	this->layout->addRow (SOFTWARE_VERSION_LABEL, this->softwareVersion);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(softwareVersionUpdate(QString)), SLOT(onSoftwareVersionUpdated(QString)));

	this->hardwareVersion = new QLabel(settings->value(HARDWARE_VERSION_KEY, "0").toString(), this);
	this->layout->addRow (HARDWARE_VERSION_LABEL, this->hardwareVersion);
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(hardwareVersionUpdate(QString)), SLOT(onHardwareVersionUpdated(QString)));

	this->setLayout (this->layout);
}

AboutDialog::~AboutDialog () {

}

void AboutDialog::showEvent (QShowEvent* event){
	DeamonInterface::getInstance ()->writeAtInformation ();

	QWidget::showEvent(event);
}

bool AboutDialog::onCompileDateUpdated(const QString& value){
	this->compileDate->setText(value);
	this->settings->setValue(COMPILE_DATE_KEY, QVariant(value));

	return true;
}

bool AboutDialog::onEsnDateUpdated(const QString& value){
	this->meid->setText(value);
	this->settings->setValue(ESN_KEY, QVariant(value));

	return true;
}

bool AboutDialog::onPEsnUpdated(const QString& value){
	this->esn->setText(value);
	this->settings->setValue(PESN_KEY, QVariant(value));

	return true;
}

bool AboutDialog::onPrlUpdated(const QString& value){
	this->prl->setText(value);
	this->settings->setValue(PRL_KEY, QVariant(value));

	return true;
}

bool AboutDialog::onSoftwareVersionUpdated(const QString& value){
	this->softwareVersion->setText(value);
	this->settings->setValue(SOFTWARE_VERSION_KEY, QVariant(value));

	return true;
}

bool AboutDialog::onHardwareVersionUpdated(const QString& value){
	this->hardwareVersion->setText(value);
	this->settings->setValue(HARDWARE_VERSION_KEY, QVariant(value));

	return true;
}

