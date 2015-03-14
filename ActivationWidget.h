#ifndef ACTIVATION_WIDGET
#define ACTIVATION_WIDGET

#include "ImageButton.h"

#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QRadioButton>
#include <QWidget>

class ActivationWidget : public QWidget {
	Q_OBJECT
public:
	explicit ActivationWidget(QWidget *parent = 0);
	~ActivationWidget ();

signals:
	bool cancelled();
	bool completed();
	bool activationInProgress();
	bool activationComplete();

public slots:
	bool onActivateClicked ();
	bool onActivation(bool status);
	bool onOkClicked();
	bool onCancelClicked();

	bool onLanguagePrompt();
	bool onCardTypePrompt();
	bool onPinPrompt();

	bool onReloadActivation();

protected:
	void paintEvent (QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateActivation();

	QImage * background;

	QRadioButton * prepaid;
	QRadioButton * postpaid;
	QLabel * pinLabel;
	QLineEdit * pin;

	QProgressBar * progressBar;
	QLabel * progressLabel;

	QLabel * activationSuccessful;
	QLabel * mobileNumberLabel;
	QLineEdit * mobileNumber;

	QString cardType;

	ImageButton * activate;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // ACTIVATION_WIDGET
