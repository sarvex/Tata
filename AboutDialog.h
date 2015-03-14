#ifndef ABOUT_DIALOG
#define ABOUT_DIALOG

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QSettings>

class AboutDialog : public QDialog {
	Q_OBJECT
public:
	explicit AboutDialog(QDialog *parent = 0);
	~AboutDialog ();

signals:

public slots:
	bool onCompileDateUpdated(const QString& value);
	bool onEsnDateUpdated(const QString& value);
	bool onPEsnUpdated(const QString& value);
	bool onPrlUpdated(const QString& value);
	bool onSoftwareVersionUpdated(const QString& value);
	bool onHardwareVersionUpdated(const QString& value);

protected:
	void showEvent (QShowEvent* event);

private:

	QLabel * driverVersion;
	QLabel * installDate;
	QLabel * compileDate;
	QLabel * prl;
	QLabel * meid;
	QLabel * esn;
	QLabel * softwareVersion;
	QLabel * hardwareVersion;

	QSettings * settings;
	QFormLayout * layout;
};

#endif // ABOUT_DIALOG
