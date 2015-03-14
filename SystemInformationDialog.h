#ifndef SYSTEM_INFORMATION_DIALOG
#define SYSTEM_INFORMATION_DIALOG

#include <QDialog>

#include <QLabel>
#include <QFormLayout>

class SystemInformationDialog : public QDialog {
	Q_OBJECT
public:
	explicit SystemInformationDialog(QDialog *parent = 0);
	~SystemInformationDialog ();

	signals:

public slots:

protected:

private:
	QLabel * operatingSystemName;
	QLabel * operatingSystemVersion;
	QLabel * processor;
	QLabel * physicalMemory;
	QLabel * virtualMemory;
	QLabel * manufacturer;

	QFormLayout * layout;
};

#endif // SYSTEM_INFORMATION_DIALOG
