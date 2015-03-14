#ifndef EXIT_DIALOG
#define EXIT_DIALOG

#include <QDialog>

#include <QPushButton>
#include <QHBoxLayout>

class DialogExit : public QDialog {
	Q_OBJECT
public:
	explicit DialogExit(QDialog *parent = 0);
	~DialogExit ();

	signals:

public slots:
	bool onCloseApplicationClicked();
	bool onCloseAndSafelyRemoveClicked();
	bool onCancelClicked();

protected:

private:
	QPushButton * closeApplication;
	QPushButton * closeAndSafelyRemove;
	QPushButton * cancel;

	QHBoxLayout * layout;
};

#endif // EXIT_DIALOG
