#include "IpAddressWidget.h"

#include "DeamonConnection.h"
#include "Defines.h"
#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QAction>
#include <QDebug>
#include <QPainter>

IpAddressWidget::IpAddressWidget(QWidget *parent) : QWidget(parent) {
	this->background = new QImage(":/display.png");
	QObject::connect(DeamonSetting::getInstance(), SIGNAL(reloadIpAddress()), SLOT(onReloadIpAddress()));

	this->ipTypeStrings.append(DYNAMIC_STRING);
	this->ipTypeStrings.append(STATIC_STRING);

	// this->ipValidator = new QRegExpValidator(QRegExp("^(([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.){3}([01]?\\d\\d?|25[0-5]|2[0-4]\\d)$"), this);
	this->ipValidator = new IpValidator;

	this->ipTypeLabel = new QLabel ( IP_TYPE, this );
	this->ipTypeLabel->setGeometry(UserInterface::tabIpAddressIpTypeLabel);
	this->ipTypeLabel->setAlignment(Qt::AlignRight);

	this->ipLabel = new QLabel ( IP_LABEL, this );
	this->ipLabel->setGeometry(UserInterface::tabIpAddressIpLabel);
	this->ipLabel->setAlignment(Qt::AlignRight);

	this->dnsLabel = new QLabel ( DNS_LABEL, this );
	this->dnsLabel->setGeometry(UserInterface::tabIpAddressDnsLabel);
	this->dnsLabel->setAlignment(Qt::AlignRight);

	this->alternateDnsLabel = new QLabel ( ALTERNATE_DNS_LABEL, this );
	this->alternateDnsLabel->setGeometry(UserInterface::tabIpAddressAlternateDnsLabel);
	this->alternateDnsLabel->setAlignment(Qt::AlignRight);

	this->winsLabel = new QLabel ( WINS_LABEL, this );
	this->winsLabel->setGeometry(UserInterface::tabIpAddressWinsLabel);
	this->winsLabel->setAlignment(Qt::AlignRight);

	this->alternateWinsLabel = new QLabel ( ALTERNATE_WINS_LABEL, this );
	this->alternateWinsLabel->setGeometry(UserInterface::tabIpAddressAlternateWinsLabel);
	this->alternateWinsLabel->setAlignment(Qt::AlignRight);

	this->ipType = new QComboBox (this);
	this->ipType->addItems(this->ipTypeStrings);
	this->ipType->setGeometry(UserInterface::tabIpAddressIpType);
	QObject::connect(this->ipType, SIGNAL(currentIndexChanged(const QString&)), SLOT(onIpTypeChanged(const QString&)));

	this->ip = new QLineEdit(this);
//    this->ip->setInputMask(IP_INPUT_MASK);
	this->ip->setValidator(this->ipValidator);
	this->ip->setGeometry(UserInterface::tabIpAddressIp);

	this->dns = new QLineEdit(this);
//    this->dns->setInputMask(IP_INPUT_MASK);
	this->dns->setValidator(this->ipValidator);
	this->dns->setGeometry(UserInterface::tabIpAddressDns);

	this->alternateDns = new QLineEdit(this);
//    this->alternateDns->setInputMask(IP_INPUT_MASK);
	this->alternateDns->setValidator(this->ipValidator);
	this->alternateDns->setGeometry(UserInterface::tabIpAddressAlternateDns);

	this->wins = new QLineEdit(this);
//    this->wins->setInputMask(IP_INPUT_MASK);
	this->wins->setValidator(this->ipValidator);
	this->wins->setGeometry(UserInterface::tabIpAddressWins);

	this->alternateWins = new QLineEdit(this);
//    this->alternateWins->setInputMask(IP_INPUT_MASK);
	this->alternateWins->setValidator(this->ipValidator);
	this->alternateWins->setGeometry(UserInterface::tabIpAddressAlternateWins);

	this->ok = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", OK_STRING, this);
	this->ok->setGeometry(UserInterface::displayDialogOk);
	QObject::connect (this->ok, SIGNAL(clicked()), SLOT(onOkClicked()));

	this->cancel = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", CANCEL_STRING, this);
	this->cancel->setGeometry(UserInterface::displayDialogCancel);
	QObject::connect (this->cancel, SIGNAL(clicked()), SLOT(onCancelClicked()));

	QObject::connect(DeamonConnection::getInstance(), SIGNAL(updateIpAddress(bool, const QString&, const QString&, const QString&, const QString&, const QString&)), SLOT(onUpdateIpAddress(bool, const QString&, const QString&, const QString&, const QString&, const QString&)));
}

IpAddressWidget::~IpAddressWidget () {

}

bool IpAddressWidget::onOkClicked() {
	qDebug () << "Entering TabIpAddress::onOkClicked";
	bool result = false;

	qDebug () << "ipAddress : " << this->ip->text ();

	Profile profile = DeamonSetting::getInstance()->getCurrentProfile();
	if ( STATIC_STRING == this->ipType->currentText()) {
		profile.setDynamic(false);
		profile.setIpAddress(this->ip->text());
		profile.setDnsAddress(this->dns->text());
		profile.setDnsAlternateAddress(this->alternateDns->text());
		profile.setWinsAddress(this->wins->text());
		profile.setWinsAlternateAddress(this->alternateWins->text());

	} else {
		profile.setDynamic(true);
	}

	DeamonSetting::getInstance()->editProfile(profile);

	emit completed();

	qDebug () << "Exiting TabIpAddress::onOkClicked";
	return (result);
}

bool IpAddressWidget::onCancelClicked() {
	bool result = false;

	emit cancelled();
	return (result);
}

bool IpAddressWidget::updateIpAddress() {
	if (false == DeamonSetting::getInstance()->getCurrentProfile().getDynamic() ){
		this->ipType->setCurrentIndex(1);

		Profile profile = DeamonSetting::getInstance()->getCurrentProfile();
		profile.setDynamic(false);

		this->ip->setText(profile.getIpAddress());
		this->dns->setText(profile.getDnsAddress());
		this->alternateDns->setText(profile.getDnsAlternateAddress());
		this->wins->setText(profile.getWinsAddress());
		this->alternateWins->setText(profile.getWinsAlternateAddress());

	} else {

		Profile profile = DeamonSetting::getInstance()->getCurrentProfile();
		profile.setDynamic(true);

		this->ipType->setCurrentIndex(0);
		this->ip->setEnabled(false);
		this->dns->setEnabled(false);
		this->alternateDns->setEnabled(false);
		this->wins->setEnabled(false);
		this->alternateWins->setEnabled(false);

	}

	return true;
}

bool IpAddressWidget::onUpdateIpAddress(bool isDynamic, const QString& ipAddress, const QString& dnsAddress, const QString& dnsAlternateAddress, const QString& winsAddress, const QString& winsAlternateAddress) {

	qDebug () << "TabIpAddress::onUpdateIpAddress " << isDynamic << ipAddress<< dnsAddress << dnsAlternateAddress << winsAddress << winsAlternateAddress;
	if ( false == isDynamic ){
		this->ipType->setCurrentIndex(1);

		DeamonSetting::getInstance()->getCurrentProfile().setDynamic(false);
		DeamonSetting::getInstance()->getCurrentProfile().setIpAddress(ipAddress);
		DeamonSetting::getInstance()->getCurrentProfile().setDnsAddress(dnsAddress);
		DeamonSetting::getInstance()->getCurrentProfile().setDnsAlternateAddress(dnsAlternateAddress);
		DeamonSetting::getInstance()->getCurrentProfile().setWinsAddress(winsAddress);
		DeamonSetting::getInstance()->getCurrentProfile().setWinsAlternateAddress(winsAlternateAddress);

		this->ip->setText(ipAddress);
		this->dns->setText(dnsAddress);
		this->alternateDns->setText(dnsAlternateAddress);
		this->wins->setText(winsAddress);
		this->alternateWins->setText(winsAlternateAddress);
	 }

	return true;
}

void IpAddressWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void IpAddressWidget::showEvent (QShowEvent * event) {
	this->updateIpAddress();
	DeamonConnection::getInstance()->readRasPhonebookConnectionEntry(DeamonSetting::getInstance()->getCurrentProfile().getName());

	return QWidget::showEvent(event);
}

bool IpAddressWidget::onIpTypeChanged(const QString& currentText) {

	if (STATIC_STRING == currentText) {
		this->ip->setEnabled(true);
		this->dns->setEnabled(true);
		this->alternateDns->setEnabled(true);
		this->wins->setEnabled(true);
		this->alternateWins->setEnabled(true);

	} else {
		this->ip->setEnabled(false);
		this->dns->setEnabled(false);
		this->alternateDns->setEnabled(false);
		this->wins->setEnabled(false);
		this->alternateWins->setEnabled(false);

	}

	return true;
}

bool IpAddressWidget::onReloadIpAddress(){
	bool result = false;

	result = this->updateIpAddress();
	return result;
}
