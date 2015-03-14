#include "PinDialog.h"

#include "Defines.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QMessageBox>
#include <QIcon>

PinDialog::PinDialog(const QString& lockCode, QWidget *parent) : QDialog(parent), lockCode(lockCode), result(false){
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));

	this->password = new QLineEdit(this);
	this->password->setEchoMode(QLineEdit::Password);
	this->password->setMaxLength(PASSWORD_LENGTH);
	this->password->setGeometry(UserInterface::dialogPassword);

	this->ok = new QPushButton(OK_STRING, this);
	this->ok->setGeometry(UserInterface::dialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new QPushButton(CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::dialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

PinDialog::~PinDialog () {

}

bool PinDialog::onOkClicked() {
	if (this->lockCode != this->password->text()) {
		if (QMessageBox::Cancel == QMessageBox::critical (NULL, ERROR_MESSAGE, LOCK_INVALID, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			this->done(QDialog::Rejected);
			return false;
		} else {
			return false;
		}
	} else {
		this->result = true;
		this->done(QDialog::Accepted);
	}

	return true;
}

bool PinDialog::onCancelClicked () {
	this->done(QDialog::Rejected);

	return true;
}

bool PinDialog::getResult() {
	return (this->result);
}
