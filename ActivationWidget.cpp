#include "ActivationWidget.h"

#include "DeamonInterface.h"
#include "Defines.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

ActivationWidget::ActivationWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadActivation()), SLOT(onReloadActivation()));

	this->prepaid = new QRadioButton(PREPAID, this);
	this->prepaid->setGeometry(UserInterface::tabActivationPrepaid);

	this->postpaid = new QRadioButton(POSTPAID, this);
	this->postpaid->setGeometry(UserInterface::tabActivationPostpaid);

	this->pinLabel = new QLabel(ENTER_PIN, this);
	this->pinLabel->setGeometry(UserInterface::tabActivationPinLabel);

	this->pin = new QLineEdit (this);
	this->pin->setGeometry(UserInterface::tabActivationPin);
	this->pin->setMaxLength(PIN_LENGTH);

	this->activate = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", ACTIVATE_STRING, this);
	this->activate->setGeometry(UserInterface::tabActivationActivate);

	QObject::connect (this->activate, SIGNAL(clicked()), SLOT(onActivateClicked()));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(activation(bool)), SLOT(onActivation(bool)));

	this->progressBar = new QProgressBar(this);
	this->progressBar->setGeometry(UserInterface::progress);
	this->progressBar->setMinimum(0);
	this->progressBar->setMaximum(0);

	this->progressLabel = new QLabel(ACTIVATION_PROGRESS_STRING, this);
	this->progressLabel->setGeometry(UserInterface::progressLabel);
	this->progressLabel->hide();

	this->activationSuccessful = new QLabel (ACTIVATION_SUCCESSFUL, this);
	this->activationSuccessful->setGeometry(UserInterface::activationSuccessful);
	this->activationSuccessful->hide();

	this->mobileNumberLabel = new QLabel (ENTER_NUMBER, this);
	this->mobileNumberLabel->setGeometry(UserInterface::mobileNumberLabel);
	this->mobileNumberLabel->hide();

	this->mobileNumber = new QLineEdit(this);
	this->mobileNumber->setGeometry(UserInterface::mobileNumber);
	this->mobileNumber->setMaxLength(MOBILE_NUMBER_LENGTH);
	this->mobileNumber->hide();

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

ActivationWidget::~ActivationWidget () {

}

bool ActivationWidget::updateActivation() {
	bool result = false;

	this->prepaid->show();
	this->postpaid->show();
	this->pinLabel->show();
	this->pin->show();
	this->activate->show();

	this->ok->show();
	this->cancel->show();

	this->progressBar->hide();
	this->progressLabel->hide();
	this->activationSuccessful->hide();
	this->mobileNumberLabel->hide();
	this->mobileNumber->hide();

	return result;
}

bool ActivationWidget::onOkClicked() {
	bool result = false;

	if (true == this->mobileNumber->isVisible()) {
		// Activation was successful
		if ( MOBILE_NUMBER_LENGTH != this->mobileNumber->text().length()) {
			QMessageBox::information(0, ERROR_MESSAGE, MOBILE_NUMBER_LENGTH_ERROR_MESSAGE, QMessageBox::Ok);
			return false;
		} else {
			// Create New Profile
			Profile profile = DeamonSetting::getInstance()->getCurrentProfile();
			profile.setUserName(this->mobileNumber->text() + PROFILE_USERNAME_SUFFIX);
			profile.setPassword(this->mobileNumber->text());
			DeamonSetting::getInstance()->editProfile(profile);
			DeamonSetting::getInstance ()->setCurrentProfile (profile.getName ());
		}
	}

	emit completed();
	return (result);
}

bool ActivationWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}

void ActivationWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void ActivationWidget::showEvent (QShowEvent * event) {
	this->updateActivation();

	return QWidget::showEvent(event);
}

bool ActivationWidget::onActivateClicked() {

	if (true == this->prepaid->isChecked()) {
		this->cardType = PREPAID_NUMBER;
	} else if (true == this->postpaid->isChecked()) {
		this->cardType = POSTPAID_NUMBER;
	} else {
		QMessageBox::critical(NULL, ERROR_MESSAGE, SELECT_CARD_TYPE, QMessageBox::Ok, QMessageBox::Ok);
		return (false);
	}

	if (true == this->pin->text().isEmpty()) {
		 if (QMessageBox::Cancel == QMessageBox::information(NULL, INFORMATION_MESSAGE, CONTINUE_WITHOUT_PIN, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			return (false);
		}
	} else if (PIN_LENGTH != this->pin->text().length()) {
		QMessageBox::critical(NULL, ERROR_MESSAGE, INVALID_PIN, QMessageBox::Ok, QMessageBox::Ok);
		return (false);
	}

	this->prepaid->hide();
	this->postpaid->hide();
	this->pinLabel->hide();
	this->pin->hide();
	this->activate->hide();
	this->ok->hide();
	this->cancel->hide();

	this->progressBar->show();
	this->progressLabel->show();

	emit activationInProgress();

	DeamonInterface::getInstance()->writeToAtPort(DeamonInterface::dial + ACTIVATION_NUMBER);
	QTimer::singleShot(30000, this, SLOT(onLanguagePrompt()));

	return (true);
}

bool ActivationWidget::onLanguagePrompt () {

	// dial 1 to select English Language
	DeamonInterface::getInstance()->writeToAtPort( DeamonInterface::toneDial + "1");
	QTimer::singleShot(5000, this, SLOT(onCardTypePrompt()));

	return true;
}

bool ActivationWidget::onCardTypePrompt () {

	DeamonInterface::getInstance()->writeToAtPort (DeamonInterface::toneDial + this->cardType);

	if (false == this->pin->text().isEmpty()) {
		QTimer::singleShot(5000, this, SLOT(onPinPrompt()));
	}

	return true;
}

bool ActivationWidget::onPinPrompt () {
	DeamonInterface::getInstance()->writeToAtPort (DeamonInterface::toneDial + this->pin->text());

	return true;
}


bool ActivationWidget::onActivation (bool status) {
	if ( false == status) {
		this->progressBar->hide();
		this->progressLabel->hide();

		this->prepaid->show();
		this->postpaid->show();
		this->pinLabel->show();
		this->pin->show();
		this->activate->show();
		this->ok->show();
		this->cancel->show();
	} else {
		this->progressBar->hide();
		this->progressLabel->hide();

		this->activationSuccessful->show();
		this->mobileNumberLabel->show();
		this->mobileNumber->show();

		this->ok->show();
	}

	emit activationComplete();

	return true;
}

bool ActivationWidget::onReloadActivation(){
	bool result = false;

	result = this->updateActivation();
	return result;
}
