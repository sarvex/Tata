#include "MessageWidget.h"

#include "UserInterface.h"
#include "Defines.h"

#include <QPainter>
#include <QTimer>

MessageWidget::MessageWidget(const QString& information, int timeout, QWidget *parent) : QDialog(parent){
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setGeometry(UserInterface::displayArea);
	this->background = new QImage(":/display.png");

	this->information = new QLabel(information, this);
	this->information->setGeometry(UserInterface::flashMessageText);
	this->information->setWordWrap(true);

	this->okButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->okButton->setGeometry(UserInterface::displayDialogCancel);

	QTimer::singleShot(timeout, this, SLOT(accept()));
	QObject::connect(this->okButton, SIGNAL(clicked()), SLOT(accept()));
}

MessageWidget::~MessageWidget () {

}

void MessageWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}
