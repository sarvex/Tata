#ifndef INFORMATION_WIDGET
#define INFORMATION_WIDGET

#include <QWidget>

#include "ImageButton.h"

#include <QImage>
#include <QLabel>
#include <QSettings>

class InformationWidget : public QWidget {
	Q_OBJECT
public:
	explicit InformationWidget(QWidget *parent = 0);
	~InformationWidget();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool onOkClicked();
	bool onCancelClicked();

	bool onCompileDateUpdated(const QString& value);
	bool onPrlUpdate(const QString& value);
	bool onEsnUpdate(const QString& value);
	bool onPEsnUpdated(const QString& value);
	bool onSoftwareVersionUpdated(const QString& value);
	bool onHardwareVersionUpdate(const QString& value);

	bool onReloadInformation();

protected:
	void paintEvent (QPaintEvent* event);
	void showEvent (QShowEvent* event);

private:
	bool updateInformation();

	QImage * background;

	QLabel * dialerInformationLabel;
	QLabel * driverVersionLabel;
	QLabel * installDateLabel;
	QLabel * compileDateLabel;
	QLabel * prlLabel;
	QLabel * meidLabel;
	QLabel * esnLabel;
	QLabel * softwareVersionLabel;
	QLabel * hardwareVersionLabel;

	QLabel * driverVersion;
	QLabel * installDate;
	QLabel * compileDate;
	QLabel * prl;
	QLabel * meid;
	QLabel * esn;
	QLabel * softwareVersion;
	QLabel * hardwareVersion;

	ImageButton * ok;
	ImageButton * cancel;

	QSettings * settings;
};

#endif // INFORMATION_WIDGET
