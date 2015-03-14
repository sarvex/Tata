#ifndef IP_ADDRESS_WIDGET
#define IP_ADDRESS_WIDGET

#include <QWidget>

#include "ImageButton.h"
#include "IpValidator.h"

#include <QComboBox>
#include <QImage>
#include <QLabel>
#include <QLineEdit>

class IpAddressWidget : public QWidget {
	Q_OBJECT
public:
	explicit IpAddressWidget(QWidget *parent = 0);
	~IpAddressWidget();

signals:
	bool cancelled();
	bool completed();

public slots:
	bool onOkClicked();
	bool onCancelClicked();
	bool onIpTypeChanged(const QString&);

	bool onReloadIpAddress();
	bool onUpdateIpAddress(bool isDynamic, const QString& ipAddress, const QString& dnsAddress, const QString& dnsAlternateAddress, const QString& winsAddress, const QString& winsAlternateAddress);
protected:
	void paintEvent(QPaintEvent* event);
	void showEvent (QShowEvent * event);

private:
	bool updateIpAddress();

	QImage * background;

	QComboBox * ipType;

	QLineEdit * ip;
	QLineEdit * dns;
	QLineEdit * alternateDns;
	QLineEdit * wins;
	QLineEdit * alternateWins;

	QLabel * ipTypeLabel;
	QLabel * ipLabel;
	QLabel * dnsLabel;
	QLabel * alternateDnsLabel;
	QLabel * winsLabel;
	QLabel * alternateWinsLabel;

	IpValidator * ipValidator;
	QStringList ipTypeStrings;

	ImageButton * ok;
	ImageButton * cancel;
};

#endif // IP_ADDRESS_WIDGET
