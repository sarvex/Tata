#include "ProfileDialog.h"

#include "DeamonDatabase.h"
#include "Defines.h"
#include "Profile.h"
#include "DeamonSetting.h"

#include <QMessageBox>
#include <QIcon>


ProfileDialog::ProfileDialog(QDialog *parent) : QDialog(parent), editing(false) {
	this->initializeUserInterface();

	this->username->setText(PROFILE_USERNAME_SUFFIX);
	this->number->setText(PROFILE_NUMBER);
}

ProfileDialog::ProfileDialog(const Profile& profile, QDialog *parent) : QDialog(parent), editing(true) {
	this->initializeUserInterface();

	this->name->setText(profile.getName());
	this->username->setText(profile.getUserName());
	this->password->setText(profile.getPassword());
	this->number->setText(profile.getNumber());
	this->defaultConnection->setChecked(profile.getConnectionType());
	this->authentication->setCurrentIndex(static_cast<int>(profile.getAuthenticationType()));
}

ProfileDialog::~ProfileDialog () {

}

bool ProfileDialog::initializeUserInterface() {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));

	this->formLayout = new QFormLayout;

	this->name = new QLineEdit(this);
	this->formLayout->addRow (PROFILE_NAME_LABEL, this->name);

	this->username = new QLineEdit(this);
	this->formLayout->addRow (USER_NAME_LABEL, this->username);

	this->password = new QLineEdit(this);
	this->formLayout->addRow (PASSWORD_LABEL, this->password);

	this->number = new QLineEdit(this);
	this->formLayout->addRow (NUMBER_LABEL, this->number);

	this->authentication = new QComboBox(this);
	this->authentication->addItems(DeamonSetting::getInstance()->getAuthenticationTypes());
	this->formLayout->addRow (AUTHENTICATION_LABEL, this->authentication);

	this->buttonLayout = new QHBoxLayout;

	this->ok = new QPushButton(OK_STRING, this);
	this->buttonLayout->addWidget (this->ok);
	QObject::connect ( this->ok, SIGNAL ( clicked() ), SLOT( onOkClicked() ));

	this->cancel = new QPushButton(CANCEL_STRING, this);
	this->buttonLayout->addWidget (this->cancel);
	QObject::connect ( this->cancel, SIGNAL ( clicked() ), SLOT( onCancelClicked() ));

	this->defaultConnection = new QCheckBox(DEFAULT_CONNECTION, this);

	this->layout = new QVBoxLayout;
	this->layout->addLayout (this->formLayout);
	this->layout->addWidget (this->defaultConnection);
	this->layout->addLayout (this->buttonLayout);
	this->setLayout (this->layout);

	return (true);
}

bool ProfileDialog::onOkClicked() {
	if (this->name->text().isEmpty() || this->username->text().isEmpty() || this->password->text().isEmpty() || this->number->text().isEmpty()) {
		if (QMessageBox::Cancel == QMessageBox::critical (NULL, ERROR_MESSAGE, PROFILE_INVALID, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			this->done(QDialog::Rejected);
			return false;
		} else {
			return false;
		}
	}

	Profile profile (this->name->text(), this->username->text(), this->password->text(), this->number->text(), this->defaultConnection->isChecked(), static_cast<AuthenticationType>(this->authentication->currentIndex()) );

	if (this->editing) { // edit existing profile
		DeamonSetting::getInstance()->editProfile(profile);
	} else { // add new profile
		DeamonSetting::getInstance()->addProfile(profile);
	}

	DeamonSetting::getInstance ()->setCurrentProfile (profile.getName ());

	this->done(QDialog::Accepted);
	return true;
}

bool ProfileDialog::onCancelClicked() {
	this->done(QDialog::Rejected);

	return true;
}
