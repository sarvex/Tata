#ifndef PIN_DIALOG
#define PIN_DIALOG

#include <QDialog>

#include <QLineEdit>
#include <QPushButton>

class PinDialog : public QDialog {
	Q_OBJECT
public:
	explicit PinDialog(const QString& lockCode, QWidget *parent = 0);
	~PinDialog ();

	bool getResult();

signals:

public slots:
	bool onOkClicked();
	bool onCancelClicked();

protected:

private:
	QLineEdit * password;

	QPushButton * ok;
	QPushButton * cancel;

	QString lockCode;
	bool result;

};

#endif // PIN_DIALOG
