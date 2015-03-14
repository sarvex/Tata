#ifndef ANIMATEBUTTON_H
#define ANIMATEBUTTON_H

#include <QPushButton>

#include <QList>
#include <QImage>
#include <QTime>

class AnimateButton : public QPushButton {
    Q_OBJECT
public:
    AnimateButton(const QString& first, const QString& second, const QString& third, const QString& fourth,  const QString& fifth, const QString& sixth, QWidget *parent = 0);
    ~AnimateButton();

signals:

public slots:
    bool onDelayedStart();

protected:
    void paintEvent (QPaintEvent * event);
    void hideEvent (QHideEvent * event);
    void showEvent (QShowEvent * event);

private:
    QList<QImage> imageList;

    QTime startTime;
    QTimer * timer;

};

#endif // ANIMATEBUTTON_H
