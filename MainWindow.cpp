#include "MainWindow.h"

#include "DeamonConnection.h"
#include "DeamonDatabase.h"
#include "DeamonInterface.h"

#include "AboutDialog.h"
#include "DiagnosticDialog.h"
#include "ExitDialog.h"
#include "PinDialog.h"
#include "SystemInformationDialog.h"
#include "TestDialog.h"

#include "AnimateButton.h"
#include "MessageWidget.h"

#include "DeamonSetting.h"
#include "UserInterface.h"

#include <QAction>
#include <QBuffer>
#include <QDebug>
#include <QDesktopServices>
#include <QEventLoop>
#include <QHttp>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QToolTip>
#include <QUrl>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent), connected(false), activationInProgress(false) {
	this->setMouseTracking(false);
	this->createSystemTray();

	this->leftLogoFilePath = new QString(QDir::tempPath () + SLASH + LEFT_LOGO_FILE_NAME);
	this->rightLogoFilePath = new QString(QDir::tempPath () + SLASH + RIGHT_LOGO_FILE_NAME);

	DeamonSetting::getInstance()->readSettingsFromDatabase();

	QObject::connect(DeamonInterface::getInstance(), SIGNAL(flashMessageUpdate(QString)), SLOT(onFlashMessage(QString)));
	QObject::connect(DeamonInterface::getInstance(), SIGNAL(defaultMinUpdate()), SLOT(onDefaultMin()));

	this->httpRequest = new QHttp( this );
	this->leftImageUrl = new QUrl(LEFT_IMAGE_LINK);
	this->rightImageUrl = new QUrl(RIGHT_IMAGE_LINK);
	QObject::connect (this->httpRequest, SIGNAL(requestFinished(int,bool)), SLOT(onHttpLoadImage(int,bool)));

	this->leftImageData = new QByteArray(20480, 0);
	this->rightImageData = new QByteArray(20480, 0);

	this->leftImageBuffer = new QBuffer(this->leftImageData, this);
	this->rightImageBuffer = new QBuffer(this->rightImageData, this);

	this->background = new QImage(":/background.png");
	this->activeTab = NONE;

	this->minimizeButton = new ImageButton(":/minimizeDefault.png", ":/minimizeHover.png", this);
	this->minimizeButton->setGeometry(UserInterface::minimizeButton );

	this->closeButton = new ImageButton(":/closeDefault.png", ":/closeHover.png", this);
	this->closeButton->setGeometry(UserInterface::closeButton );

	QObject::connect (this->minimizeButton, SIGNAL(clicked()), SLOT(onMinimizeButtonClicked()));
	QObject::connect (this->closeButton, SIGNAL(clicked()), SLOT(onCloseButtonClicked()));

	QObject::connect (DeamonInterface::getInstance(), SIGNAL(modemPlugged()), SLOT(onModemPlugged()));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(modemUnplugged()), SLOT(onModemUnplugged()));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(signalStrengthUpdate(int)), SLOT(onSignalStrengthUpdated(int)));
	QObject::connect (DeamonInterface::getInstance(), SIGNAL(systemModeUpdate(int)), SLOT(onSystemModeUpdated(int)));

	QObject::connect (DeamonConnection::getInstance(), SIGNAL(connected()), SLOT(onConnected()));
	QObject::connect (DeamonConnection::getInstance(), SIGNAL(disconnected()), SLOT(onDisconnected()));
	QObject::connect (DeamonConnection::getInstance(), SIGNAL(rasError(long,QString)), SLOT(onRasError(long, QString)));

	this->drawLeftPanel();
	this->drawRightPanel();
	this->drawTopBanner();
	this->drawTabBar();
	this->drawBottomBanner();
	this->drawMainDisplay();
	this->drawMenus();

	DeamonInterface::getInstance()->start ();

	if (true == DeamonSetting::getInstance()->getAutoDial()) {
		this->connectButton->click();
	}
}

bool MainWindow::createSystemTray () {

	this->minimizeAction = new QAction(tr("Mi&nimize"), this);
	QObject::connect (this->minimizeAction, SIGNAL(triggered()), SLOT(hide()));

	this->restoreAction = new QAction(tr("&Restore"), this);
	QObject::connect (this->restoreAction, SIGNAL(triggered()), SLOT(showNormal()));

	this->safelyRemoveAction = new QAction(tr("&Safely Remove"), this);
	QObject::connect (this->safelyRemoveAction, SIGNAL(triggered()), SLOT(onSafelyRemove()));

	this->upgradeAction = new QAction(tr("&Upgrade"), this);
	QObject::connect (this->upgradeAction,
					  SIGNAL(triggered()),
					  this,
					  SLOT(onUpgradeTriggered()));

	this->quitAction = new QAction(tr("&Quit"), this);
	QObject::connect (this->quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	this->trayIconMenu = new QMenu(this);
	this->trayIconMenu->addAction(this->minimizeAction);
	this->trayIconMenu->addAction(this->restoreAction);
	this->trayIconMenu->addSeparator();
	this->trayIconMenu->addAction(this->safelyRemoveAction);
	this->trayIconMenu->addSeparator ();
	this->trayIconMenu->addAction (this->upgradeAction);
	this->trayIconMenu->addSeparator ();
	this->trayIconMenu->addAction(this->quitAction);

	this->trayIcon = new QSystemTrayIcon(this);
	this->trayIcon->setContextMenu(this->trayIconMenu);
	this->trayIcon->setToolTip(APPLICATION_NAME);
	QObject::connect(this->trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(onSystemTrayActivated(QSystemTrayIcon::ActivationReason)));

	this->trayIcon->setIcon(QIcon(":/ttslMax.png"));
	this->trayIcon->show();

	return (true);
}

bool MainWindow::onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason){
	// qDebug () << "Entering MainWindow::onSystemTrayActivated";

	switch (reason) {
	case QSystemTrayIcon::Trigger: { // do nothing
		}break;
	case QSystemTrayIcon::DoubleClick: {
			this->showNormal();
		}break;
	case QSystemTrayIcon::MiddleClick: {// fall through
		}break;
	case QSystemTrayIcon::Unknown: {
		// qDebug() << "QSystemTrayIcon::Unknown";
		}break;
	case QSystemTrayIcon::Context: {
		// qDebug() << "QSystemTrayIcon::Context";
		}break;
	default:{   // do nothing

		};
	}

	return true;
}


bool MainWindow::drawMenus() {

	this->helpButton = new ImageButton(":/helpDefault.png", ":/helpHover.png", this);
	this->helpButton->setGeometry(UserInterface::helpMenu );
	QObject::connect (this->helpButton, SIGNAL(clicked()), SLOT(onHelpButtonClicked()));

	this->optionsButton = new ImageButton(":/optionsDefault.png", ":/optionsHover.png", this);
	this->optionsButton->setGeometry(UserInterface::optionsMenu );
	QObject::connect (this->optionsButton, SIGNAL(clicked()), SLOT(onOptionsButtonClicked()));

	this->helpMenu = new QMenu(this);

	this->helpTopics = new QAction(HELP_TOPICS, this);
	this->helpMenu->addAction(this->helpTopics);

	this->checkUpdates = new QAction(CHECK_UPDATES, this);
	this->helpMenu->addAction(this->checkUpdates);

	this->DeviceSupport= new QAction(DEVICE_SUPPORT, this);
	this->helpMenu->addAction(this->DeviceSupport);

	this->connectToForums = new QAction(CONNECT_TO_FORUMS, this);
	this->helpMenu->addAction(this->connectToForums);

	this->about = new QAction(ABOUT, this);
	this->helpMenu->addAction(this->about);

	this->systemInformation = new QAction (SYSTEM_INFORMATION, this);
	this->helpMenu->addAction(this->systemInformation);

	this->diagnosticParameter = new QAction (DIAGNOSTIC_PARAMETER, this);
	this->helpMenu->addAction(this->diagnosticParameter);

	this->optionsMenu = new QMenu(this);
	this->testDevice = new QAction (TEST_DEVICE, this);
	this->optionsMenu->addAction(this->testDevice);

	this->resetSettings = new QAction (RESET_SETTINGS, this);
	this->optionsMenu->addAction(this->resetSettings);


	QObject::connect (this->helpTopics, SIGNAL(triggered()), SLOT(onHelpTopics()));
	QObject::connect (this->checkUpdates, SIGNAL(triggered()), SLOT(onCheckUpdates()));
	QObject::connect (this->DeviceSupport, SIGNAL(triggered()), SLOT(onDeviceSupport()));
	QObject::connect (this->connectToForums, SIGNAL(triggered()), SLOT(onConnectToForums()));
	QObject::connect (this->about, SIGNAL(triggered()), SLOT(onAbout()));
	QObject::connect (this->systemInformation, SIGNAL(triggered()), SLOT(onSystemInformation()));
	QObject::connect (this->diagnosticParameter, SIGNAL(triggered()), SLOT(onDiagnosticParameter()));

	QObject::connect (this->testDevice, SIGNAL(triggered()), SLOT(onTestDevice()));
	QObject::connect (this->resetSettings, SIGNAL(triggered()), SLOT(onResetSettings()));

	return (true);
}

bool MainWindow::drawLeftPanel() {
	this->leftLogoView = new QWebView(this);
	this->leftLogoView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	this->leftLogoView->setGeometry(UserInterface::leftLogoLabel);
	QObject::connect (this->leftLogoView, SIGNAL(linkClicked(QUrl)), SLOT(openWebPage(QUrl)));

	this->leftLogoLabel = new ImageButton(":/rightOperatorLogo.png", this);
	this->leftLogoLabel->setGeometry(UserInterface::leftLogoLabel );
	QObject::connect (this->leftLogoLabel, SIGNAL(clicked()), SLOT(openWebPage()));

	if ( QFile::exists(*this->leftLogoFilePath)) {

		this->leftLogoView->load(*this->leftLogoFilePath);
		this->leftLogoLabel->hide ();

	} else {

		this->leftLogoView->hide();

	}

	return (true);
}

bool MainWindow::drawRightPanel() {
	this->rightLogoView = new QWebView(this);
	this->rightLogoView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	this->rightLogoView->setGeometry(UserInterface::rightLogoLabel);
	QObject::connect (this->rightLogoView, SIGNAL(linkClicked(QUrl)), SLOT(openWebPage(QUrl)));

	this->rightLogoLabel = new ImageButton(":/leftOperatorLogo.png", this);
	this->rightLogoLabel->setGeometry(UserInterface::rightLogoLabel );
	QObject::connect (this->rightLogoLabel, SIGNAL(clicked()), SLOT(openWebPage()));

	if ( QFile::exists(*this->rightLogoFilePath)) {

		this->rightLogoView->load(*this->rightLogoFilePath);
		this->rightLogoLabel->hide ();

	} else {

		this->rightLogoView->hide();

	}


	return (true);
}

bool MainWindow::drawTopBanner() {
	this->yahoo = new ImageButton(":/yahoo.png", this);
	this->yahoo->setGeometry(UserInterface::yahoo);

	this->search = new ImageButton(":/search.png", this);
	this->search->setGeometry(UserInterface::search);
	QObject::connect (this->search, SIGNAL(clicked()), SLOT (onSearchClicked()));

	this->searchText = new QLineEdit(this);
	this->searchText->setGeometry(UserInterface::searchText);
	QObject::connect (this->searchText, SIGNAL(returnPressed()), SLOT(onSearchClicked()));

	return (true);
}

bool MainWindow::drawBottomBanner() {
	this->signalTextImage.append(QPixmap(":/signalText1.png"));
	this->signalTextImage.append(QPixmap(":/signalText2.png"));
	this->signalTextImage.append(QPixmap(":/signalText3.png"));

	this->signalTextLabel = new QLabel(this);
	this->signalTextLabel->setPixmap(this->signalTextImage.at(2));
	this->signalTextLabel->setGeometry(UserInterface::bottomBannerItemZero );

	this->signalStrengthImage.append(QPixmap(":/signalStrength0.png"));
	this->signalStrengthImage.append(QPixmap(":/signalStrength1.png"));
	this->signalStrengthImage.append(QPixmap(":/signalStrength2.png"));
	this->signalStrengthImage.append(QPixmap(":/signalStrength3.png"));
	this->signalStrengthImage.append(QPixmap(":/signalStrength4.png"));
	this->signalStrengthImage.append(QPixmap(":/signalStrength5.png"));

	this->signalStrengthLabel = new QLabel(this);
	this->signalStrengthLabel->setPixmap(this->signalStrengthImage.at(2));
	this->signalStrengthLabel->setGeometry(UserInterface::bottomBannerItemOne );

	this->helpLabel = new QLabel(this);
	this->helpLabel->setPixmap(QPixmap(":/forHelp.png"));
	this->helpLabel->setGeometry(UserInterface::bottomBannerItemTwo );

	this->connectButton = new ImageButton(":/connectDefault.png", ":/connectHover.png", this);
	this->connectButton->setGeometry(UserInterface::bottomBannerItemThree );
	this->connectButton->setVisible(true);

	this->connectingButton = new AnimateButton(":/connecting0.png", ":/connecting1.png", ":/connecting2.png", ":/connecting3.png", ":/connecting4.png", ":/connecting5.png", this);
	this->connectingButton->setGeometry(UserInterface::bottomBannerItemThree );
	this->connectingButton->setVisible(false);

	this->disconnectButton = new ImageButton(":/disconnectDefault.png", ":/disconnectHover.png", this);
	this->disconnectButton->setGeometry(UserInterface::bottomBannerItemThree );
	this->disconnectButton->setVisible(false);

	this->disconnectingButton = new AnimateButton(":/disconnecting0.png", ":/disconnecting1.png", ":/disconnecting2.png", ":/disconnecting3.png", ":/disconnecting4.png", ":/disconnecting5.png", this);
	this->disconnectingButton->setGeometry(UserInterface::bottomBannerItemThree );
	this->disconnectingButton->setVisible(false);

	this->operatorLabel = new QLabel(this);
	this->operatorLabel->setPixmap(QPixmap(":/operatorLogoBig.png"));
	this->operatorLabel->setGeometry(UserInterface::bottomBannerItemFour );

	QObject::connect (this->connectButton, SIGNAL(clicked()), SLOT(onConnectButtonClicked()));
	QObject::connect (this->disconnectButton, SIGNAL(clicked()), SLOT(onDisconnectButtonClicked()));

	return (true);
}

bool MainWindow::onSignalStrengthUpdated(int level) {
	int bars = 0;

	if (99 != level) {
		bars = (level / 8) + 2;
	} else {
		return false;
	}

	this->signalStrengthLabel->setPixmap(signalStrengthImage.at(bars));
	return (true);
}

bool MainWindow::onSystemModeUpdated(int value){
	switch (value) {
	case 2: this->signalTextLabel->setPixmap(this->signalTextImage.at(0)); break;
	case 4: this->signalTextLabel->setPixmap(this->signalTextImage.at(2)); break;
	case 8: this->signalTextLabel->setPixmap(this->signalTextImage.at(2)); break;
	}

	return true;
}

bool MainWindow::onConnectButtonClicked () {
//    qDebug () << "MainWindow::onConnectButtonClicked checkLock";
	if (false == this->checkLock(true)) return (false);

	this->connectButton->hide();
	this->connectingButton->show();

	this->generalTabButton->setVisible(false);
	this->lockTabButton->setVisible(false);
	this->ipAddressTabButton->setVisible(false);
	this->networkTabButton->setVisible(false);
	this->webSectionTabButton->setVisible(false);
	this->informationTabButton->setVisible(false);
	this->activationTabButton->setVisible(false);

	this->general->setVisible(false);
	this->lock->setVisible(false);
	this->network->setVisible(false);
	this->ipAddress->setVisible(false);
	this->information->setVisible(false);
	this->webSection->setVisible(false);
	this->activation->setVisible(false);

	DeamonConnection::getInstance()->connectDataCall();

	return (true);
}

bool MainWindow::onDisconnectButtonClicked(){
	this->disconnectButton->hide();

	this->disconnectingButton->show();

	DeamonConnection::getInstance()->disconnectDataCall();

	return false;
}

bool MainWindow::drawTabBar() {
	this->upgradeButton = new ImageButton(":/upgradeDefault.png", ":/upgradeHover.png", this);
	this->upgradeButton->setGeometry(UserInterface::upgradeButton );

	this->accountButton = new ImageButton(":/myAccountDefault.png", ":/myAccountHover.png", this);
	this->accountButton->setGeometry(UserInterface::accountButton);

	this->settingsButton = new ImageButton(":/settingsDefault.png", ":/settingsHover.png", this);
	this->settingsButton->setGeometry(UserInterface::settingsButton );

	QObject::connect (this->upgradeButton,    SIGNAL(clicked()), SLOT(onUpgradeButtonClicked()));
	QObject::connect (this->accountButton, SIGNAL(clicked()), SLOT(onAccountButtonClicked()));
	QObject::connect (this->settingsButton,   SIGNAL(clicked()), SLOT(onSettingsButtonClicked()));

	return (true);
}

bool MainWindow::drawMainDisplay() {

	this->generalTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", GENERAL_STRING, this);
	this->generalTabButton->setGeometry(UserInterface::generalTabButton );
	this->generalTabButton->setVisible(false);
	QObject::connect (this->generalTabButton, SIGNAL(clicked()), SLOT (onGeneralTabClicked()));

	this->lockTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", LOCK_STRING, this);
	this->lockTabButton->setGeometry(UserInterface::lockTabButton );
	this->lockTabButton->setVisible(false);
	QObject::connect (this->lockTabButton, SIGNAL(clicked()), SLOT (onLockTabClicked()));

	this->networkTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", NETWORK_STRING, this);
	this->networkTabButton->setGeometry(UserInterface::networkTabButton );
	this->networkTabButton->setVisible(false);
	QObject::connect (this->networkTabButton, SIGNAL(clicked()), SLOT (onNetworkTabClicked()));

	this->ipAddressTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", IP_STRING, this);
	this->ipAddressTabButton->setGeometry(UserInterface::ipAddressTabButton );
	this->ipAddressTabButton->setVisible(false);
	QObject::connect (this->ipAddressTabButton, SIGNAL(clicked()), SLOT (onIpAddressTabClicked()));

	this->informationTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", INFORMATION_STRING, this);
	this->informationTabButton->setGeometry(UserInterface::informationTabButton );
	this->informationTabButton->setVisible(false);
	QObject::connect (this->informationTabButton, SIGNAL(clicked()), SLOT (onInformationTabClicked()));

	this->webSectionTabButton= new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", WEB_SECTION_STRING, this);
	this->webSectionTabButton->setGeometry(UserInterface::webSectionTabButton );
	this->webSectionTabButton->setVisible(false);
	QObject::connect (this->webSectionTabButton, SIGNAL(clicked()), SLOT (onWebSectionTabClicked()));

	this->activationTabButton = new ImageButton(":/buttonDefault.png", ":/buttonHover.png", ":/buttonPress.png", ACTIVATION_STRING, this);
	this->activationTabButton->setGeometry(UserInterface::activationTabButton );
	this->activationTabButton->setVisible(false);
	QObject::connect (this->activationTabButton, SIGNAL(clicked()), SLOT (onActivationTabClicked()));

	this->general = new GeneralWidget (this);
	this->general->setGeometry (UserInterface::displayArea );
	this->general->setVisible(false);
	QObject::connect (this->general, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->general, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->lock = new LockWidget (this);
	this->lock->setGeometry (UserInterface::displayArea );
	this->lock->setVisible(false);
	QObject::connect (this->lock, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->lock, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->network = new NetworkWidget (this);
	this->network->setGeometry (UserInterface::displayArea );
	this->network->setVisible(false);
	QObject::connect (this->network, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->network, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->ipAddress = new IpAddressWidget (this);
	this->ipAddress->setGeometry (UserInterface::displayArea );
	this->ipAddress->setVisible(false);
	QObject::connect (this->ipAddress, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->ipAddress, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->information = new InformationWidget (this);
	this->information->setGeometry (UserInterface::displayArea );
	this->information->setVisible(false);
	QObject::connect (this->information, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->information, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->webSection = new WebSectionWidget(this);
	this->webSection->setGeometry (UserInterface::displayArea );
	this->webSection->setVisible(false);
	QObject::connect (this->webSection, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->webSection, SIGNAL(cancelled()), SLOT(onToggleSettings()));

	this->activation = new ActivationWidget (this);
	this->activation->setGeometry (UserInterface::displayArea );
	this->activation->setVisible(false);
	QObject::connect (this->activation, SIGNAL(completed()), SLOT(onToggleSettings()));
	QObject::connect (this->activation, SIGNAL(cancelled()), SLOT(onToggleSettings()));
	QObject::connect (this->activation, SIGNAL(activationInProgress()), SLOT(onActivationInProgress()));
	QObject::connect (this->activation, SIGNAL(activationComplete()), SLOT(onActivationComplete()));

	return (true);
}

MainWindow::~MainWindow() {

}

void MainWindow::setVisible(bool visible) {
	this->minimizeAction->setEnabled(visible);
	this->restoreAction->setEnabled(isMaximized() || !visible);
	QMainWindow::setVisible(visible);
}

void MainWindow::paintEvent(QPaintEvent* event) {
	Q_UNUSED (event)

	QPainter painter(this);
	painter.drawImage(UserInterface::topLeftPoint, *this->background);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	if (this->moving) {
		this->move(event->globalPos() - this->offset);
	}
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		this->moving = true;
		this->offset = event->pos();
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		this->moving = false;
	}
}

bool MainWindow::onReceiveMessage(const QString& message) {
	qDebug () << "Message Recieved : " << message;
	this->showNormal();

	return (true);
}

bool MainWindow::onMinimizeButtonClicked() {
	if (true == DeamonSetting::getInstance()->getExecuteAccess ()) {
		qDebug () << "MainWindow::onMinimizeButtonClicked Hiding";
		this->hide();
	} else {
		qDebug () << "MainWindow::onMinimizeButtonClicked Minimizing";
		this->showMinimized();
	}

	return (true);
}

bool MainWindow::onCloseButtonClicked() {
	if ( true == this->activationInProgress) {
		QMessageBox::information (NULL, ACTIVATION_TITLE, ACTIVATION_IN_PROGRESS, QMessageBox::Ok, QMessageBox::Ok);
		return false;
	}

	if (true == this->connected) {
		QMessageBox::information (NULL, INFORMATION_MESSAGE, DISCONNECT_INTERNET, QMessageBox::Ok, QMessageBox::Ok);
		return (false);
	}

	DialogExit dialogExit;
	if (QDialog::Accepted == dialogExit.exec()) {
		DeamonInterface::getInstance ()->stop ();
		DeamonInterface::getInstance ()->wait ();
		qApp->quit();
	}


	return (true);
}

bool MainWindow::onUpgradeButtonClicked() {
	if (false == this->checkLock(false)) return (false);

	// check for connection
	if (false == this->connected) {
		if (QMessageBox::Cancel == QMessageBox::information(NULL, INFORMATION_MESSAGE, CONNECT_INTERNET, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok) ) {
			return (false);
		} else {
			this->connectButton->click();
		}
		QEventLoop loop;
		QObject::connect (DeamonConnection::getInstance(), SIGNAL(connected()), &loop, SLOT(quit()));
		loop.exec();
	}

	// download the html page

	// check the latest version of dialer

		// download the latest version if available

		// exit and launch installer

	QMessageBox::information(NULL, UPGRADE_TITLE, NO_UPGRADE_TEXT, QMessageBox::Ok, QMessageBox::Ok);

	return (true);
}

bool MainWindow::onAccountButtonClicked() {
	if (false == this->checkLock(false)) return (false);
	this->openWebPage(QUrl(MY_ACCOUNT_URL));

	return (true);
}


bool MainWindow::onSettingsButtonClicked() {
	if (false == this->checkLock(false)) return false;

	return this->onToggleSettings ();
}

bool MainWindow::onToggleSettings() {
	bool toggle = !this->generalTabButton->isVisible();

	this->generalTabButton->setVisible(toggle);
	this->lockTabButton->setVisible(toggle);
	this->ipAddressTabButton->setVisible(toggle);
	this->networkTabButton->setVisible(toggle);
	this->webSectionTabButton->setVisible(toggle);
	this->informationTabButton->setVisible(toggle);
	this->activationTabButton->setVisible(toggle);

	if (true == DeamonSetting::getInstance ()->getGeneralLock ()) {
		this->general->setVisible(false);
		this->lock->setVisible(toggle);
	} else {
		this->general->setVisible(toggle);
		this->lock->setVisible(false);
	}

	this->network->setVisible(false);
	this->ipAddress->setVisible(false);
	this->information->setVisible(false);
	this->webSection->setVisible(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onGeneralTabClicked() {
//    qDebug () << "MainWindow::onGeneralTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (GENERAL == this->activeTab) {

		this->activeTab = NONE;
		this->generalTabButton->select (false);
		this->general->setVisible (false);

	} else {

		this->activeTab = GENERAL;
		this->generalTabButton->select (true);
		this->general->setVisible (true);

	}

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onLockTabClicked() {
//    qDebug () << "MainWindow::onLockTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (LOCK == this->activeTab) {

		this->activeTab = NONE;
		this->lockTabButton->select (false);
		this->lock->setVisible (false);

	} else {

		this->activeTab = LOCK;
		this->lockTabButton->select (true);
		this->lock->setVisible (true);

	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onNetworkTabClicked() {
//    qDebug () << "MainWindow::onNetworkTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (NETWORK == this->activeTab) {

		this->activeTab = NONE;
		this->networkTabButton->select (false);
		this->network->setVisible (false);

	} else {

		this->activeTab = NETWORK;
		this->networkTabButton->select (true);
		this->network->setVisible (true);

	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onIpAddressTabClicked() {
//    qDebug () << "MainWindow::onIpAddressTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (IP_ADDRESS == this->activeTab) {

		this->activeTab = NONE;
		this->ipAddressTabButton->select (false);
		this->ipAddress->setVisible (false);

	} else {

		this->activeTab = IP_ADDRESS;
		this->ipAddressTabButton->select (true);
		this->ipAddress->setVisible (true);

	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onInformationTabClicked() {
//    qDebug () << "MainWindow::onInformationTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (INFORMATION == this->activeTab) {

		this->activeTab = NONE;
		this->informationTabButton->select (false);
		this->information->setVisible (false);

	} else {

		this->activeTab = INFORMATION;
		this->informationTabButton->select (true);
		this->information->setVisible (true);

	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onWebSectionTabClicked() {
//    qDebug () << "MainWindow::onWebSectionTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (WEB_SECTION == this->activeTab) {
		this->activeTab = NONE;
		this->webSectionTabButton->select(false);
		this->webSection->setVisible(false);
	} else {
		this->activeTab = WEB_SECTION;
		this->webSectionTabButton->select(true);
		this->webSection->setVisible(true);
	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->activationTabButton->select(false);
	this->activation->setVisible(false);

	return (true);
}

bool MainWindow::onActivationTabClicked() {
//    qDebug () << "MainWindow::onActivationTabClicked checkLock";
	if (false == this->checkLock(false)) return (false);

	if (ACTIVATION == this->activeTab) {

		this->activeTab = NONE;
		this->activationTabButton->select (false);
		this->activation->setVisible (false);

	} else {

		this->activeTab = ACTIVATION;
		this->activationTabButton->select (true);
		this->activation->setVisible (true);

	}

	this->generalTabButton->select(false);
	this->general->setVisible(false);

	this->lockTabButton->select(false);
	this->lock->setVisible(false);

	this->networkTabButton->select(false);
	this->network->setVisible(false);

	this->ipAddressTabButton->select(false);
	this->ipAddress->setVisible(false);

	this->informationTabButton->select(false);
	this->information->setVisible(false);

	this->webSectionTabButton->select(false);
	this->webSection->setVisible(false);

	return (true);
}

bool MainWindow::onModemPlugged(){

	this->upgradeButton->setEnabled(true);
	this->accountButton->setEnabled(true);
	this->settingsButton->setEnabled( !this->connected );

	this->signalStrengthLabel->setEnabled(true);
	this->connectButton->setEnabled(true);

	this->searchText->setEnabled(true);
	this->search->setEnabled(true);

	this->optionsButton->setEnabled(true);

	this->leftLogoLabel->setEnabled(true);
	this->rightLogoLabel->setEnabled(true);

	return true;
}

bool MainWindow::onModemUnplugged(){
	this->signalStrengthLabel->setPixmap(this->signalStrengthImage.at(0));
	this->connected = false;

	this->connectingButton->hide ();
	this->disconnectButton->hide ();
	this->disconnectingButton->hide ();
	this->connectButton->show ();


	this->upgradeButton->setEnabled(false);
	this->accountButton->setEnabled(false);
	this->settingsButton->setEnabled(false);

	this->signalStrengthLabel->setEnabled(false);
	this->connectButton->setEnabled(false);

	this->searchText->setEnabled(false);
	this->search->setEnabled(false);

	this->optionsButton->setEnabled(false);

	this->leftLogoLabel->setEnabled(false);
	this->rightLogoLabel->setEnabled(false);

	return true;
}

bool MainWindow::onConnected () {
	this->connected = true;

	this->connectingButton->hide();
	this->disconnectButton->show();

	this->leftLogoView->load(QUrl(LEFT_LOGO_LINK));
	this->rightLogoView->load(QUrl(RIGHT_LOGO_LINK));


	this->settingsButton->setEnabled(false);

	if (true == DeamonSetting::getInstance()->getOpenDefault()) {
		this->openWebPage(QUrl(DEFAULT_WEB_PAGE));
	}

	this->HttpLoadImage ();

	return (true);
}

bool MainWindow::onDisconnected () {
	this->connected = false;

	this->disconnectingButton->hide();
	this->connectingButton->hide ();

	this->connectButton->show();

	this->settingsButton->setEnabled(true);

	return (true);
}

bool MainWindow::onRasError(long errorNumber, const QString& errorString) {
	QMessageBox::critical(NULL, QString::number (errorNumber), errorString, QMessageBox::Ok, QMessageBox::Ok);
	return true;
}

bool MainWindow::onHelpButtonClicked() {
	this->helpMenu->popup(QCursor::pos());

	return (true);
}

bool MainWindow::onHelpTopics() {
	QString filePath = qApp->applicationDirPath() + "/help.chm";
	qDebug () << QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

	return (true);
}

bool MainWindow::onCheckUpdates() {
//    qDebug () << "MainWindow::onCheckUpdates checkLock";
	if (false == this->checkLock(false)) return (false);

	this->upgradeButton->click();

	return (true);
}

bool MainWindow::onDeviceSupport() {
	this->openWebPage(QUrl(DEVICE_SUPPORT_URL));

	return (true);
}

bool MainWindow::onConnectToForums() {
	this->openWebPage(QUrl(CONNECT_TO_FORUMS_URL));

	return (true);
}

bool MainWindow::onAbout() {
	AboutDialog about;
	about.exec();

	return (true);
}

bool MainWindow::onSystemInformation() {
	SystemInformationDialog systemInformation;
	systemInformation.exec();

	return (true);
}

bool MainWindow::onDiagnosticParameter() {
	DiagnosticDialog diagnostic;
	diagnostic.exec();

	return (true);
}


bool MainWindow::onOptionsButtonClicked() {
	this->optionsMenu->popup(QCursor::pos());

	return (true);
}


bool MainWindow::onTestDevice() {
	TestDialog test;
	test.exec();

	return (true);
}

bool MainWindow::onResetSettings() {

	if (QMessageBox::Cancel == QMessageBox::question (NULL, INFORMATION_MESSAGE, RESET_SETTINGS, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
		return (false);
	} else {
		PinDialog password(DeamonSetting::getInstance()->getLock());
		if ( QDialog::Accepted == password.exec()) {
			if (true == password.getResult()) {
				DeamonSetting::getInstance()->resetAllSettings();
			} else {
				return false;
			}
		} else {
			return false;
		}

	}

	return (true);
}

bool MainWindow::openWebPage(QUrl url) {
	if (false == this->connected) {
		if (QMessageBox::Cancel == QMessageBox::information(NULL, INFORMATION_MESSAGE, CONNECT_INTERNET, QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok) ) {
			return (false);
		} else {
			this->connectButton->click();
		}
		QEventLoop loop;
		QObject::connect (DeamonConnection::getInstance(), SIGNAL(connected()), &loop, SLOT(quit()));
		loop.exec();
	}

	QDesktopServices::openUrl(QUrl(url));
	return (true);
}

bool MainWindow::onSearchClicked() {
	this->openWebPage(YAHOO_SEARCH_STRING + this->searchText->text());

	return (true);
}

bool MainWindow::checkLock(bool internet) {
	if ( true == this->activationInProgress ) return (false);

	bool condition = false;
	if (true == internet) {
		condition = (true == DeamonSetting::getInstance()->getInternetLock());
	} else {
		condition = (true == DeamonSetting::getInstance()->getGeneralLock());
	}

	if (true == condition) {
		PinDialog password(DeamonSetting::getInstance()->getLock());
		if ( QDialog::Accepted == password.exec()) {
			return (password.getResult());
		} else {
			return false;
		}
	} else {
		return (true);
	}
}
bool MainWindow::onSafelyRemove() {
	bool result = false;

	if (true == this->connected) {
		QMessageBox::information (NULL, INFORMATION_MESSAGE, DISCONNECT_INTERNET, QMessageBox::Ok, QMessageBox::Ok);
		return (false);
	} else {
		qApp->quit();
	}

	return (result);
}

bool MainWindow::onQuit() {
	bool result = false;

	if (true == this->connected) {
		QMessageBox::information (NULL, INFORMATION_MESSAGE, DISCONNECT_INTERNET, QMessageBox::Ok, QMessageBox::Ok);
		return (false);
	} else {
		qApp->quit();
	}

	return (result);
}

bool MainWindow::HttpLoadImage() {

	this->leftImageData->clear();
	this->rightImageData->clear();

	this->leftImageBuffer->open(QIODevice::ReadWrite|QIODevice::Truncate);
	this->leftImageBuffer->open(QIODevice::ReadWrite|QIODevice::Truncate);

	this->httpRequest->setHost(this->leftImageUrl->host());
	this->leftImageRequestindex = this->httpRequest->get(this->leftImageUrl->toEncoded(), this->leftImageBuffer);
	this->rightImageRequestindex = this->httpRequest->get(this->rightImageUrl->toEncoded(), this->rightImageBuffer);

	return (true);
}

bool MainWindow::onHttpLoadImage( int searchIndex, bool failed ) {
	if ( failed ) {
		qDebug () << "Failed to Load Image : " << searchIndex << " Error : " << this->httpRequest->errorString();
		return false;
	} else {
		QDir::temp ().mkdir ("images");
	}

	if (searchIndex == this->leftImageRequestindex) {
		this->leftLogoLabel->setImages(*this->leftImageData);

		QPixmap leftImage;
		leftImage.loadFromData (*this->leftImageData);
		leftImage.save (QDir::tempPath () + "/images/photon-left.jpg");


	} else if (searchIndex == this->rightImageRequestindex) {
		this->rightLogoLabel->setImages(*this->rightImageData);

		QPixmap rightImage;
		rightImage.loadFromData (*this->rightImageData);
		rightImage.save (QDir::tempPath () + "/images/photon-right.jpg");
	}

	QFile leftLogoFile(*this->leftLogoFilePath);
	leftLogoFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream leftLogoTextStream(&leftLogoFile);
	leftLogoTextStream << this->leftLogoView->page()->mainFrame()->toHtml ();
	leftLogoFile.close();

	QFile rightLogoFile(*this->rightLogoFilePath);
	rightLogoFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream rightLogoTextStream(&rightLogoFile);
	rightLogoTextStream << this->rightLogoView->page()->mainFrame()->toHtml();
	rightLogoFile.close();

	this->leftLogoLabel->setVisible(false);
	this->rightLogoLabel->setVisible(false);

	this->leftLogoView->setVisible(true);
	this->rightLogoView->setVisible(true);


	return true;
}

void MainWindow::closeEvent(QCloseEvent *event){
	DeamonSetting::getInstance()->writeSettingsToDatabase();
	DeamonDatabase::getInstance()->closeDatabase();

	event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if ((Qt::Key_W == event->key()) && ( (Qt::ShiftModifier|Qt::AltModifier) == event->modifiers())) {
		this->webSection->showVisibilityOption();
	}
}

bool MainWindow::onDefaultMin () {
	this->helpButton->setEnabled (true);
	this->optionsButton->setEnabled (false);
	this->connectButton->setEnabled (false);
	this->upgradeButton->setEnabled (false);
	this->accountButton->setEnabled (false);
	this->settingsButton->setEnabled (false);

	this->settingsButton->click();
	this->activationTabButton->click();

	return (true);
}

bool MainWindow::onFlashMessage (const QString& value) {
	bool result = false;

	MessageWidget flashMessage(value, FLASH_MESSAGE_TIMEOUT);
	flashMessage.exec();

	return result;
}

bool MainWindow::onActivationInProgress(){
	this->activationInProgress = true;

	return true;
}

bool MainWindow::onActivationComplete(){
	this->activationInProgress = false;

	return false;
}

bool MainWindow::checkVersion () {

	this->versionRequest = new QHttp (this);
	QObject::connect (this->versionRequest,
					  SIGNAL(requestFinished(int, bool)),
					  this,
					  SLOT(onVersionRequestFinished(int, bool)));

	this->versionData = new QByteArray(128, 0);
	this->versionBuffer = new QBuffer (this->versionData, 0);
	this->versionBuffer->open (QIODevice::ReadWrite|QIODevice::Truncate);

	this->versionRequest->setHost (QUrl(VERSION_URL).host ());
	this->versionRequest->get (QUrl(VERSION_URL).toEncoded (), this->versionBuffer);

	return true;
}

bool
MainWindow::onUpgradeTriggered () {
	this->setupRequest = new QHttp (this);
	QObject::connect (this->setupRequest,
					  SIGNAL(requestFinished(int, bool)),
					  this,
					  SLOT(onSetupRequestFinished(int, bool)));

	this->setupData = new QByteArray(128000, 0);
	this->setupBuffer = new QBuffer (this->setupData, 0);
	this->setupBuffer->open (QIODevice::ReadWrite|QIODevice::Truncate);

	this->setupRequest->setHost (QUrl(SETUP_URL).host ());
	this->setupRequest->get (QUrl(SETUP_URL).toEncoded (), this->setupBuffer);

	return true;
}

bool
MainWindow::onVersionRequestFinished (
		int index, bool failed) {

	Q_UNUSED (index);
	bool result = false;

	if ( true == failed ) {
		QMessageBox::critical (NULL,
							   NETWORK_ERROR,
							   VERSION_ERROR,
							   QMessageBox::Ok,
							   QMessageBox::Ok);

		result = false;

	} else {
		QString version(*this->versionData);
		if (version.toInt () > VERSION) {
			this->trayIcon->showMessage (NEW_VERSION,
										 VERSION_SUCCESS);
		} else {
			QMessageBox::information (NULL,
									  NETWORK_SUCCESS,
									  VERSION_LATEST,
									  QMessageBox::Ok,
									  QMessageBox::Ok);
			result = true;
		}
	}

	this->versionBuffer->close ();
	delete this->versionBuffer;
	delete this->versionData;

	return result;
}

bool
MainWindow::onSetupRequestFinished (
		int index, bool failed) {

	Q_UNUSED (index);
	bool result = false;

	if ( true == failed ) {
		QMessageBox::critical (NULL,
							   NETWORK_ERROR,
							   SETUP_ERROR,
							   QMessageBox::Ok,
							   QMessageBox::Ok);

		result = false;

	} else {
		QFile setupFile (QDir::tempPath () + "/setup.exe");
		setupFile.open (QIODevice::WriteOnly | QIODevice::Truncate);
		setupFile.write (*this->setupData);
		setupFile.close ();

		if (QMessageBox::Ok == QMessageBox::question (NULL,
													  NETWORK_SUCCESS,
													  SETUP_SUCCESS,
													  QMessageBox::Ok
													  |QMessageBox::Cancel,
													  QMessageBox::Ok)) {
			QProcess::startDetached (QDir::tempPath ()+"/setup.exe",
									 QStringList (), QDir::tempPath ());

			this->closeButton->click ();
		}

		result = true;
	}

	this->setupBuffer->close ();
	delete this->setupBuffer;
	delete this->setupData;

	return result;
}
