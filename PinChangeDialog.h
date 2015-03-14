#ifndef PIN_CHANGE_DIALOG
#define PIN_CHANGE_DIALOG

#include <QDialog>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class PinChangeDialog : public QDialog {
	Q_OBJECT
public:
	explicit PinChangeDialog(QDialog *parent = 0);
	~PinChangeDialog ();

	signals:

public slots:
	bool onOkClicked();
	bool onCancelClicked();

protected:

private:
	QLineEdit * existingLock;
	QLineEdit * newLock;
	QLineEdit * confirmLock;

	QPushButton * ok;
	QPushButton * cancel;

	QFormLayout * formLayout;
	QHBoxLayout * buttonLayout;
	QVBoxLayout * layout;
};

#endif // PIN_CHANGE_DIALOG
