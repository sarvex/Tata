#include "ImageButton.h"

#include "UserInterface.h"

#include <QDebug>
#include <QPainter>

ImageButton::ImageButton(const QString& normalImage, const QString& hoverImage, const QString& text, QWidget* parent) :
QPushButton(parent), normalImage(normalImage), hoverImage(hoverImage), pressImage(normalImage),
  text(text), hover (false), press (false) {
}

ImageButton::ImageButton(const QString& normalImage, const QString& hoverImage, const QString& pressImage, const QString& text, QWidget* parent) :
QPushButton(parent), normalImage(normalImage), hoverImage(hoverImage), pressImage(pressImage),
  text(text), hover (false), press (false) {
}

ImageButton::ImageButton(const QString& normalImage, const QString& hoverImage, QWidget* parent) :
QPushButton(parent), normalImage(normalImage), hoverImage(hoverImage), pressImage(normalImage),
  hover (false), press (false) {
}

ImageButton::ImageButton(const QString& normalImage, QWidget* parent) :
QPushButton(parent), normalImage(normalImage), hoverImage(normalImage), pressImage(normalImage),
  hover (false), press (false) {
}

ImageButton::~ImageButton () {

}


void ImageButton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    if (true == this->hover && this->isEnabled()) {
        painter.drawImage(UserInterface::topLeftPoint, this->hoverImage);
    } else if (true == this->press  && this->isEnabled()) {
        painter.drawImage(UserInterface::topLeftPoint, this->pressImage);
    } else {
        painter.drawImage(UserInterface::topLeftPoint, this->normalImage);
    }

    if (false == this->text.isEmpty()) {
        painter.setFont(this->font());
        painter.setPen(Qt::black);
        painter.drawText(0, 0, this->geometry().width(), this->geometry().height(), Qt::AlignCenter, text);
    }

    painter.end ();
}

void ImageButton::enterEvent(QEvent * event) {

    this->hover = true;
//    this->update();

    QPushButton::enterEvent(event);

}

void ImageButton::leaveEvent(QEvent * event) {

    this->hover = false;
//     this->update();

    QPushButton::leaveEvent(event);

}

bool ImageButton::select (bool status) {
    this->press = status;
//    this->update();

    return(true);
}

bool ImageButton::setImages(const QString& normalImage, const QString& hoverImage) {
    this->normalImage = QImage(normalImage);
    this->hoverImage = QImage(hoverImage);
    this->pressImage = QImage(normalImage);

//    this->update();
    return(true);
}


bool ImageButton::setImages(const QString& normalImage, const QString& hoverImage, const QString& pressImage) {
    this->normalImage = QImage(normalImage);
    this->hoverImage = QImage(hoverImage);
    this->pressImage = QImage(pressImage);

//    this->update();

    return(true);
}

bool ImageButton::setImages(const QByteArray& data){
    this->normalImage.fromData(data);
    this->hoverImage.fromData(data);
    this->pressImage.fromData(data);

//    this->update();

    return false;
}

bool ImageButton::setNormalImage (const QString& normalImage) {
    this->normalImage = QImage(normalImage);

//    this->update();
    return(true);
}

QImage ImageButton::getNormalImage () {
    return(this->normalImage);
}

bool ImageButton::setHoverImage (const QString& hoverImage) {
    this->hoverImage = QImage(hoverImage);

//    this->update();
    return(true);
}

QImage ImageButton::getHoverImage () {
    return(this->hoverImage);
}

bool ImageButton::setPressImage (const QString& pressImage) {
    this->pressImage = QImage(pressImage);

//    this->update();
    return(true);
}

QImage ImageButton::getPressImage () {
    return(this->pressImage);
}
