#include "LockWidget.h"

#include "Defines.h"
#include "PinChangeDialog.h"
#include "PinDialog.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QDebug>
#include <QInputDialog>
#include <QPainter>

LockWidget::LockWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadLock()), SLOT(onReloadLock()));

	this->generalLock = new QCheckBox(GENERAL_LOCK, this);
	this->generalLock->setGeometry (UserInterface::tabLockGeneralLock);

	this->internetLock = new QCheckBox(INTERNET_LOCK, this);
	this->internetLock->setGeometry (UserInterface::tabLockInternetLock);

	this->changeLockCode = new QPushButton(CHANGE_LOCK_CODE, this);
	this->changeLockCode->setGeometry (UserInterface::tabLockChangeLockCode);

	QObject::connect ( this->generalLock, SIGNAL(clicked(bool)), SLOT(generalLockClicked(bool)));
	QObject::connect ( this->internetLock, SIGNAL(clicked(bool)), SLOT(internetLockClicked(bool)));
	QObject::connect ( this->changeLockCode, SIGNAL (released() ), SLOT(changeLockCodeClicked() ));

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

LockWidget::~LockWidget () {

}

bool LockWidget::updateLock() {
	this->generalLock->setChecked(DeamonSetting::getInstance()->getGeneralLock());
	this->internetLock->setChecked(DeamonSetting::getInstance()->getInternetLock());

	return true;
}

bool LockWidget::onOkClicked() {
	bool result = false;

	DeamonSetting::getInstance()->setGeneralLock(this->generalLock->isChecked());
	DeamonSetting::getInstance()->setInternetLock(this->internetLock->isChecked());

	emit completed();
	return (result);
}

bool LockWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}
void LockWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void LockWidget::showEvent (QShowEvent * event) {
	this->updateLock();

	return QWidget::showEvent(event);
}

bool LockWidget::generalLockClicked (bool state) {
	qDebug () << "TabLock::generalLockClicked";
	PinDialog password(DeamonSetting::getInstance()->getLock());
	password.exec();

	if (false == password.getResult()) {
		this->generalLock->setChecked(!state);
	}

	return true;
}

bool LockWidget::internetLockClicked (bool state) {
	qDebug () << "TabLock::internetLockClicked";
	PinDialog password(DeamonSetting::getInstance()->getLock());
	password.exec();

	if (false == password.getResult()) {
		this->generalLock->setChecked(!state);
	}

	return true;
}

bool LockWidget::changeLockCodeClicked () {
	qDebug () << "TabLock::changeLockCodeClicked";
	PinChangeDialog dialogChangeLock;

	dialogChangeLock.exec();

	return true;
}

bool LockWidget::onReloadLock() {
	bool result = false;

	result = this->updateLock();
	return result;
}
