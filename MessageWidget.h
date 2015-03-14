#ifndef MESSAGE_DIALOG
#define MESSAGE_DIALOG

#include <QDialog>

#include <QLabel>
#include "ImageButton.h"

class MessageWidget : public QDialog
{
	Q_OBJECT
public:
	explicit MessageWidget(const QString& information, int timeout, QWidget *parent = 0);
	~MessageWidget ();

signals:

public slots:

protected:
	void paintEvent(QPaintEvent* event);

private:
	QImage * background;

	QLabel * information;
	ImageButton * okButton;
};

#endif // MESSAGE_DIALOG
