#ifndef LOCK_WIDGET
#define LOCK_WIDGET

#include <QWidget>

#include <QCheckBox>
#include <QPushButton>

#include "ImageButton.h"

class LockWidget : public QWidget {
	Q_OBJECT
public:
	explicit LockWidget(QWidget *parent = 0);
	~LockWidget ();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool generalLockClicked (bool);
	bool internetLockClicked (bool);
	bool changeLockCodeClicked ();

	bool onOkClicked();
	bool onCancelClicked();

	bool onReloadLock();

protected:
	void paintEvent(QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateLock();

	QCheckBox * generalLock;
	QCheckBox * internetLock;

	QPushButton * changeLockCode;

	QImage * background;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // LOCK_WIDGET
