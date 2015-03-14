#ifndef TEST_DIALOG
#define TEST_DIALOG

#include <QDialog>

#include <QFormLayout>
#include <QVBoxLayout>

#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>

class TestDialog : public QDialog {
	Q_OBJECT
public:
	explicit TestDialog(QDialog *parent = 0);
	~TestDialog ();

	signals:

public slots:
	bool onStartTestClicked();

protected:

private:
	bool testDriver();
	bool testRegistry();
	bool testModem();
	bool testPort();
	bool testProfiles();

	QFile * testLog;
	QTextStream * testStream;

	QPushButton * startTest;

	QLabel * driverTest;
	QLabel * registryTest;
	QLabel * modemTest;
	QLabel * portTest;
	QLabel * profilesTest;

	QFormLayout * formLayout;
	QVBoxLayout * layout;
};

#endif // TEST_DIALOG
