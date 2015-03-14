#ifndef WEB_SECTION_TAB
#define WEB_SECTION_TAB

#include <QWidget>

#include "ImageButton.h"

#include <QCheckBox>
#include <QImage>
#include <QKeyEvent>

class WebSectionWidget : public QWidget {
	Q_OBJECT
public:
	explicit WebSectionWidget(QWidget *parent = 0);
	~WebSectionWidget ();

	bool showVisibilityOption ();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool onOpenDefaultClicked(bool state);

	bool onOkClicked();
	bool onCancelClicked();

	bool onReloadWebSection ();

protected:
	void paintEvent (QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateWebSection();

	QImage * background;

	QCheckBox * openDefault;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // WEB_SECTION_TAB
