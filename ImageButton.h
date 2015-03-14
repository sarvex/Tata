#ifndef IMAGE_BUTTON
#define IMAGE_BUTTON

#include <QPushButton>

class ImageButton : public QPushButton {
	Q_OBJECT
public:
	ImageButton(const QString& normalImage, const QString& hoverImage, const QString& text, QWidget *parent = 0);
	ImageButton(const QString& normalImage, const QString& hoverImage, const QString& pressImage, const QString& text, QWidget* parent = 0);

	ImageButton(const QString& normalImage, const QString& hoverImage, QWidget *parent = 0);
	ImageButton(const QString& normalImage, QWidget *parent = 0);

	~ImageButton ();

	bool setImages(const QString& normalImage, const QString& hoverImage);
	bool setImages(const QString& normalImage, const QString& hoverImage, const QString& pressImage);

	bool setImages(const QByteArray& data);

	bool setNormalImage (const QString& normalImage);
	QImage getNormalImage ();

	bool setHoverImage (const QString& hoverImage);
	QImage getHoverImage ();

	bool setPressImage (const QString& pressImage);
	QImage getPressImage ();

	bool select (bool status);
	signals:

public slots:

protected:
	void paintEvent(QPaintEvent * event);
	void enterEvent(QEvent * event);
	void leaveEvent(QEvent * event);

private:
	QImage normalImage;
	QImage hoverImage;
	QImage pressImage;

	QString text;

	bool hover;
	bool press;
};

#endif // IMAGE_BUTTON
