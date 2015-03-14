#ifndef PROFILE_DIALOG
#define PROFILE_DIALOG

#include <QDialog>

#include "Profile.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>


class ProfileDialog : public QDialog {
	Q_OBJECT
public:
	explicit ProfileDialog(QDialog *parent = 0);
	ProfileDialog(const Profile& profile, QDialog *parent=0);
	~ProfileDialog ();

	signals:

public slots:
	bool onOkClicked();
	bool onCancelClicked();

protected:

private:
	bool initializeUserInterface();

	QLineEdit * name;
	QLineEdit * username;
	QLineEdit * password;
	QLineEdit * number;
	QCheckBox * defaultConnection;
	QComboBox * authentication;

	QPushButton * ok;
	QPushButton * cancel;

	QFormLayout * formLayout;
	QHBoxLayout * buttonLayout;
	QVBoxLayout * layout;

	bool editing;
};

#endif // PROFILE_DIALOG
