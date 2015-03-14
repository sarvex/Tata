#ifndef GENERAL_WIDGET
#define GENERAL_WIDGET

#include <QWidget>

#include "ImageButton.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

class GeneralWidget : public QWidget {
	Q_OBJECT
public:
	explicit GeneralWidget(QWidget *parent = 0);
	~GeneralWidget();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool onOkClicked();
	bool onCancelClicked();

	bool onReloadGeneral();

protected:
	void paintEvent(QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateUserAccount();
	bool updateGeneral();

	QCheckBox * autoTerminate;
	QCheckBox * autoExecute;
	QCheckBox * executeAccess;
	QCheckBox * autoDial;

	QComboBox * userAccount;

	QLabel * userInformation;

	QImage * background;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // GENERAL_WIDGET
