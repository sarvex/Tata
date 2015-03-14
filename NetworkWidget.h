#ifndef NETWORK_WIDGET
#define NETWORK_WIDGET

#include <QWidget>

#include "ImageButton.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

class NetworkWidget : public QWidget {
	Q_OBJECT
public:
	explicit NetworkWidget(QWidget *parent = 0);
	~NetworkWidget();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool onAddProfileClicked();
	bool onEditProfileClicked();
	bool onDeleteProfileClicked();
	bool onDefaultProfileClicked();

	bool onOkClicked();
	bool onCancelClicked();

	bool onReloadNetwork();

protected:
	void paintEvent(QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateNetwork();

	bool updateProfileNames();

	QLabel * networkModeLabel;
	QLabel * profileNameLabel;

	QComboBox * networkMode;

	QComboBox * profileName;
	QPushButton * addProfile;
	QPushButton * editProfile;
	QPushButton * deleteProfile;

	QCheckBox * defaultProfile;

	QImage * background;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // NETWORK_WIDGET
