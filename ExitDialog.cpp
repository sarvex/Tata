#include "ExitDialog.h"

#include "Defines.h"

#include <QIcon>

DialogExit::DialogExit(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));

	this->closeApplication = new QPushButton(CLOSE_APPLICATION, this);
	this->closeAndSafelyRemove = new QPushButton(CLOSE_AND_SAFELY_REMOVE, this);
	this->cancel = new QPushButton(CANCEL_STRING, this);

	this->layout = new QHBoxLayout;
	this->layout->addWidget (this->closeApplication);
	this->layout->addWidget (this->closeAndSafelyRemove);
	this->layout->addWidget (this->cancel);
	this->setLayout (layout);

	QObject::connect (this->closeApplication, SIGNAL(clicked()), SLOT(onCloseApplicationClicked()));
	QObject::connect (this->closeAndSafelyRemove, SIGNAL(clicked()), SLOT(onCloseAndSafelyRemoveClicked()));
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

DialogExit::~DialogExit () {

}

bool DialogExit::onCloseApplicationClicked() {
	this->done(QDialog::Accepted);
	return true;
}

bool DialogExit::onCloseAndSafelyRemoveClicked() {
	// safely remove device
	this->done(QDialog::Accepted);
	return true;
}

bool DialogExit::onCancelClicked() {
	this->done(QDialog::Rejected);
	return true;
}
