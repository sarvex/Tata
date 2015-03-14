#include "AnimateButton.h"

#include "UserInterface.h"

#include <QDebug>
#include <QPainter>
#include <QTimer>

AnimateButton::AnimateButton(const QString& first, const QString& second, const QString& third, const QString& fourth,  const QString& fifth, const QString& sixth, QWidget *parent) : QPushButton(parent) {
    this->startTime.start();
    this->timer = new QTimer ();
    QObject::connect ( this->timer, SIGNAL(timeout()), SLOT(update()));

    this->imageList.append(QImage(first));
    this->imageList.append(QImage(second));
    this->imageList.append(QImage(third));
    this->imageList.append(QImage(fourth));
    this->imageList.append(QImage(fifth));
    this->imageList.append(QImage(sixth));
}

AnimateButton::~AnimateButton () {
    this->timer->stop ();
    delete this->timer;
}

bool AnimateButton::onDelayedStart() {
    this->timer->start(500);

    return true;
}

void AnimateButton::paintEvent (QPaintEvent *event) {
    Q_UNUSED (event);

    // qDebug () << "Is Hidden" << this->isHidden();
    QPainter painter(this);
    painter.drawImage(UserInterface::topLeftPoint, this->imageList.at((this->startTime.elapsed()/100)%6));
    painter.end ();
}

void AnimateButton::hideEvent (QHideEvent * event){
    // qDebug () << "Entering AnimateButton::hideEvent";
    this->timer->stop();

    // qDebug () << "Exiting AnimateButton::hideEvent";
    return QPushButton::hideEvent(event);
}

void AnimateButton::showEvent (QShowEvent * event){
    // qDebug () << "Entering AnimateButton::showEvent";
    this->timer->start(100);

    // qDebug () << "Exiting AnimateButton::showEvent";
    return QPushButton::showEvent(event);
}
