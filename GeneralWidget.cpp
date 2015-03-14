#include "GeneralWidget.h"

#include "Defines.h"
#include "DeamonSetting.h"
#include "UserInterface.h"
#include "DeamonDatabase.h"

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QShowEvent>

GeneralWidget::GeneralWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadGeneral()), this, SLOT(onReloadGeneral()));

	this->autoTerminate = new QCheckBox(AUTO_TERMINATE, this);
	this->autoTerminate->setGeometry (UserInterface::tabGeneralAutoTerminate);

	this->autoExecute = new QCheckBox(AUTO_EXECUTE, this);
	this->autoExecute->setGeometry (UserInterface::tabGeneralAutoExecute);

	this->executeAccess = new QCheckBox(EXECUTE_ACCESS, this);
	this->executeAccess->setGeometry (UserInterface::tabGeneralExecuteAccess);

	this->autoDial = new QCheckBox(AUTO_DIAL, this);
	this->autoDial->setGeometry (UserInterface::tabGeneralAutoDial);

	this->userInformation = new QLabel(USER_INFORMATION, this);
	this->userInformation->setGeometry (UserInterface::tabGeneralUserInformation);

	this->userAccount = new QComboBox(this);
	this->userAccount->addItems( DeamonSetting::getInstance()->getProfileNames() );
	this->userAccount->setGeometry (UserInterface::tabGeneralUserAccount);


	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

GeneralWidget::~GeneralWidget () {

}

bool GeneralWidget::onOkClicked() {
	bool result = false;

	DeamonSetting::getInstance()->setAutoDial(this->autoDial->isChecked());
	DeamonSetting::getInstance()->setAutoExecute(this->autoExecute->isChecked());
	DeamonSetting::getInstance()->setExecuteAccess(this->executeAccess->isChecked());
	DeamonSetting::getInstance()->setAutoTerminate(this->autoTerminate->isChecked());
	DeamonSetting::getInstance()->getInstance()->setCurrentProfile(this->userAccount->currentText());

	emit completed();
	return (result);
}

bool GeneralWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}

void GeneralWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void GeneralWidget::showEvent (QShowEvent * event) {
	this->updateGeneral();

	return QWidget::showEvent(event);
}

bool GeneralWidget::updateUserAccount() {
	bool result = false;

	for (int index = 0; index < this->userAccount->count(); index++) {
		if (DeamonSetting::getInstance()->getCurrentProfile().getName() == this->userAccount->itemText(index)) {
			this->userAccount->setCurrentIndex(index);
			result = true;
			break;
		}
	}

	return result;
}


bool GeneralWidget::updateGeneral() {
	bool result = false;

	this->autoTerminate->setChecked(DeamonSetting::getInstance()->getAutoTerminate());
	this->autoExecute->setChecked(DeamonSetting::getInstance()->getAutoExecute());
	this->executeAccess->setChecked(DeamonSetting::getInstance()->getExecuteAccess());
	this->autoDial->setChecked(DeamonSetting::getInstance()->getAutoDial());

	result = this->updateUserAccount();
	return result;

}

bool GeneralWidget::onReloadGeneral() {
	bool result = false;

	result = this->updateGeneral();
	return result;

}
