#include "PinChangeDialog.h"

#include "Defines.h"
#include "DeamonSetting.h"

#include <QMessageBox>
#include <QIcon>

PinChangeDialog::PinChangeDialog(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));

	this->existingLock = new QLineEdit(this);
	this->existingLock->setEchoMode(QLineEdit::Password);
	this->existingLock->setMaxLength(PASSWORD_LENGTH);

	this->newLock = new QLineEdit(this);
	this->newLock->setEchoMode(QLineEdit::Password);
	this->newLock->setMaxLength(PASSWORD_LENGTH);

	this->confirmLock = new QLineEdit(this);
	this->confirmLock->setEchoMode(QLineEdit::Password);
	this->confirmLock->setMaxLength(PASSWORD_LENGTH);

	this->ok = new QPushButton(OK_STRING, this);

	this->cancel = new QPushButton(CANCEL_STRING, this);

	this->formLayout = new QFormLayout;
	this->formLayout->setLabelAlignment (Qt::AlignRight);

	this->formLayout->addRow (EXISTING_LOCK, this->existingLock);
	this->formLayout->addRow (NEW_LOCK, this->newLock);
	this->formLayout->addRow (CONFIRM_LOCK, this->confirmLock);

	this->buttonLayout = new QHBoxLayout;
	this->buttonLayout->addWidget (this->ok);
	this->buttonLayout->addWidget (this->cancel);

	this->layout = new QVBoxLayout;
	this->layout->addLayout (this->formLayout);
	this->layout->addStretch ();
	this->layout->addLayout (this->buttonLayout);

	this->setLayout (this->layout);

	QObject::connect (this->ok, SIGNAL (clicked()), SLOT(onOkClicked()));
	QObject::connect (this->cancel, SIGNAL (clicked()), SLOT(onCancelClicked()));
}

PinChangeDialog::~PinChangeDialog () {

}

bool PinChangeDialog::onOkClicked () {
	if (this->newLock->text().isEmpty() || this->existingLock->text().isEmpty() || this->confirmLock->text().isEmpty()) {

		if (QMessageBox::Cancel == QMessageBox::critical (NULL, ERROR_MESSAGE, LOCK_EMPTY, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			this->done(QDialog::Rejected);
		} else {
			return false;
		}
	}

	if (this->newLock->text() != this->confirmLock->text()) {
		if (QMessageBox::Cancel == QMessageBox::critical (NULL, ERROR_MESSAGE, LOCK_MISMATCH, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			this->done(QDialog::Rejected);
		} else {
			return false;
		}
	}

	if (DeamonSetting::getInstance()->checkLock( this->newLock->text())) {
		if (QMessageBox::Cancel == QMessageBox::critical (NULL, ERROR_MESSAGE, LOCK_INVALID, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
			this->done(QDialog::Rejected);
		} else {
			return false;
		}
	}

	DeamonSetting::getInstance()->setLock(this->newLock->text());

	this->done(QDialog::Accepted);

	return true;
}

bool PinChangeDialog::onCancelClicked () {
	this->done(QDialog::Rejected);

	return true;
}
