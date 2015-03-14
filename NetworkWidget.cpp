#include "NetworkWidget.h"

#include "DeamonInterface.h"
#include "DeamonDatabase.h"
#include "Defines.h"
#include "ProfileDialog.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadNetwork()), SLOT(onReloadNetwork()));

	this->networkModeLabel = new QLabel (NETWORK_MODE_LABEL, this);
	this->networkModeLabel->setGeometry(UserInterface::tabNetworkModeLabel);

	this->networkMode = new QComboBox(this);
	this->networkMode->addItem(NETWORK_MODE_ZERO);
	this->networkMode->addItem(NETWORK_MODE_ONE);
	this->networkMode->addItem(NETWORK_MODE_TWO);
	this->networkMode->addItem(NETWORK_MODE_THREE);
	this->networkMode->setGeometry (UserInterface::tabNetworkMode);

	this->profileNameLabel = new QLabel (PROFILE_NAME_LABEL, this);
	this->profileNameLabel->setGeometry(UserInterface::tabNetworkProfileNamesLabel);

	this->profileName = new QComboBox(this);
	this->profileName->setGeometry (UserInterface::tabNetworkProfileNames);

	this->addProfile = new QPushButton(ADD_PROFILE_STRING, this);
	this->addProfile->setGeometry (UserInterface::tabNetworkAddProfile);

	this->editProfile = new QPushButton(EDIT_PROFILE_STRING, this);
	this->editProfile->setGeometry (UserInterface::tabNetworkEditProfile);

	this->deleteProfile = new QPushButton(DELETE_PROFILE_STRING, this);
	this->deleteProfile->setGeometry (UserInterface::tabNetworkDeleteProfile);

	this->defaultProfile = new QCheckBox(SET_DEFAULT_STRING, this);
	this->defaultProfile->setGeometry (UserInterface::tabNetworkDefaultProfile);

	QObject::connect (this->addProfile, SIGNAL(clicked()), SLOT(onAddProfileClicked()));
	QObject::connect (this->editProfile, SIGNAL(clicked()), SLOT(onEditProfileClicked()));
	QObject::connect (this->deleteProfile, SIGNAL(clicked()), SLOT(onDeleteProfileClicked()));
	QObject::connect (this->defaultProfile, SIGNAL(clicked()), SLOT(onDefaultProfileClicked()));

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));

	this->updateProfileNames();
}

NetworkWidget::~NetworkWidget () {

}

bool NetworkWidget::updateNetwork() {
	bool result = false;

	this->updateProfileNames();
	this->defaultProfile->setChecked(DeamonSetting::getInstance()->getCurrentProfile().getConnectionType());

	return result;
}

bool NetworkWidget::onOkClicked() {
	bool result = false;

	if ( NETWORK_MODE_ZERO == this->networkMode->currentText() ){
		DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::setModeZero);
	} else if ( NETWORK_MODE_ONE == this->networkMode->currentText()) {
	   DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::setModeOne);
	} else if ( NETWORK_MODE_TWO == this->networkMode->currentText()) {
		DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::setModeTwo);
	} else if ( NETWORK_MODE_THREE == this->networkMode->currentText()) {
		DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::setModeThree);
	}

	emit completed();
	return (result);
}

bool NetworkWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}

bool NetworkWidget::updateProfileNames() {
	for (int index = this->profileName->count(); index >= 0; index--) {
		this->profileName->removeItem(index);
	}

	this->profileName->addItems (DeamonSetting::getInstance()->getProfileNames());

	for (int index = 0; index < this->profileName->count(); index++) {
		if (DeamonSetting::getInstance()->getCurrentProfile().getName() == this->profileName->itemText(index)) {
			this->profileName->setCurrentIndex(index);
			this->defaultProfile->setChecked(DeamonSetting::getInstance()->getCurrentProfile().getConnectionType());
			break;
		}
	}

	return (true);
}

void NetworkWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void NetworkWidget::showEvent (QShowEvent * event) {
	this->updateNetwork();

	return QWidget::showEvent(event);
}

bool NetworkWidget::onAddProfileClicked() {
	ProfileDialog dialogProfile;
	dialogProfile.exec();

	return (this->updateProfileNames());
}

bool NetworkWidget::onEditProfileClicked() {
	QString profileName = this->profileName->currentText();

	qDebug () << "TabNetwork::onEditProfileClicked" << profileName;
	Profile profile = DeamonDatabase::getInstance()->readProfile(profileName);

	ProfileDialog dialogProfile(profile);
	dialogProfile.exec();

	return (this->updateProfileNames());
}

bool NetworkWidget::onDeleteProfileClicked() {
	QString currentProfileName = this->profileName->currentText();
	if (PROFILE_NAME == currentProfileName) {
		QMessageBox::critical(NULL, ERROR_MESSAGE, CANNOT_DELETE_DEFAULT, QMessageBox::Ok, QMessageBox::Ok);
		return false;
	} else {
		DeamonDatabase::getInstance()->deleteProfile(currentProfileName);
		DeamonSetting::getInstance()->deleteProfile(this->profileName->currentText());
		this->updateProfileNames();
	}
	return (true);
}

bool NetworkWidget::onDefaultProfileClicked() {
	DeamonSetting::getInstance()->setCurrentProfile(this->profileName->currentText());

	return true;
}

bool NetworkWidget::onReloadNetwork(){
	bool result = false;

	result = this->updateNetwork();
	return result;
}
