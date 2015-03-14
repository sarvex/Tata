#include "WebSectionWidget.h"

#include "PinDialog.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QDebug>
#include <QInputDialog>
#include <QPainter>

WebSectionWidget::WebSectionWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadWebSection()), SLOT(onReloadWebSection()));

	this->openDefault = new QCheckBox(OPEN_DEFAULT_STRING, this);
	this->openDefault->setGeometry(UserInterface::tabWebOpenDefault);
	this->openDefault->setVisible(false);
	QObject::connect (this->openDefault, SIGNAL(clicked(bool)), SLOT(onOpenDefaultClicked(bool)));

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));
}

WebSectionWidget::~WebSectionWidget () {

}

bool WebSectionWidget::updateWebSection() {
	this->openDefault->setChecked(DeamonSetting::getInstance()->getOpenDefault());
	this->openDefault->hide();

	return true;
}

bool WebSectionWidget::onOkClicked() {
	bool result = false;

	this->openDefault->hide();
	emit completed();
	return (result);
}

bool WebSectionWidget::onCancelClicked() {
	bool result = false;

	this->openDefault->hide();
	emit cancelled();
	return (result);
}


bool WebSectionWidget::onOpenDefaultClicked(bool state) {
	PinDialog password("5298");
	if (QDialog::Accepted == password.exec()) {
		if (true == password.getResult()) {
			DeamonSetting::getInstance()->setOpenDefault(this->openDefault->isChecked());
		} else {
			this->openDefault->setChecked(!state);
		}
	} else {
		this->openDefault->setChecked(!state);
	}

	return (true);
}

bool WebSectionWidget::showVisibilityOption () {
	this->openDefault->setVisible(true);

	return (true);
}


void WebSectionWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void WebSectionWidget::showEvent (QShowEvent * event) {
	this->updateWebSection();

	return QWidget::showEvent(event);
}

bool WebSectionWidget::onReloadWebSection() {
	this->updateWebSection ();

	return (true);
}
