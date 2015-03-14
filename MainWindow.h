#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ImageButton.h"

#include "Defines.h"
#include "AnimateButton.h"
#include "ActivationWidget.h"
#include "GeneralWidget.h"
#include "InformationWidget.h"
#include "IpAddressWidget.h"
#include "LockWidget.h"
#include "NetworkWidget.h"
#include "WebSectionWidget.h"

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QSystemTrayIcon>
#include <QByteArray>
#include <QBuffer>
#include <QHttp>
#include <QtWebKit>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

    void setVisible(bool visible);

    signals:
    void modemPlugged(bool status);

public slots:
    bool openWebPage(QUrl url = QUrl(DEFAULT_WEB_PAGE));
    bool onReceiveMessage(const QString& message);

    bool onVersionRequestFinished (int index, bool failed);
    bool onSetupRequestFinished (int index, bool failed);

    bool onDefaultMin();
    bool onFlashMessage(const QString& value);

    bool onMinimizeButtonClicked();
    bool onCloseButtonClicked();

    bool onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason);

    bool onSafelyRemove();
    bool onUpgradeTriggered();
    bool onQuit();

    bool onHelpButtonClicked();
    bool onOptionsButtonClicked();

    bool onUpgradeButtonClicked();
    bool onAccountButtonClicked();
    bool onSettingsButtonClicked();
    bool onToggleSettings();

    bool onGeneralTabClicked();
    bool onLockTabClicked();
    bool onNetworkTabClicked();
    bool onIpAddressTabClicked();
    bool onInformationTabClicked();
    bool onWebSectionTabClicked();
    bool onActivationTabClicked();

    bool onConnectButtonClicked();
    bool onDisconnectButtonClicked();

    bool onConnected ();
    bool onDisconnected ();
    bool onModemPlugged();
    bool onModemUnplugged();

    bool onRasError(long errorNumber, const QString& errorString);


    bool onSignalStrengthUpdated(int level);
    bool onSystemModeUpdated(int value);

    bool onSearchClicked ();

    // Help Menu
    bool onHelpTopics();
    bool onCheckUpdates();
    bool onDeviceSupport();
    bool onConnectToForums();
    bool onAbout();
    bool onSystemInformation();
    bool onDiagnosticParameter();

    // Options Menu
    bool onTestDevice();
    bool onResetSettings();

    bool onActivationInProgress();
    bool onActivationComplete();

    bool onHttpLoadImage( int searchIndex, bool failed );

protected:
    void paintEvent(QPaintEvent* event);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);

private:
    bool checkVersion ();
    bool HttpLoadImage();
    bool createSystemTray();

    bool drawMenus();
    bool drawLeftPanel();
    bool drawRightPanel();
    bool drawTopBanner ();
    bool drawBottomBanner ();
    bool drawTabBar ();
    bool drawMainDisplay ();

    bool checkLock(bool internet);

    GeneralWidget      * general;
    LockWidget         * lock;
    NetworkWidget      * network;
    IpAddressWidget    * ipAddress;
    InformationWidget  * information;
    WebSectionWidget   * webSection;
    ActivationWidget   * activation;

    ImageButton * minimizeButton;
    ImageButton * closeButton;

    ImageButton * yahoo;
    ImageButton * search;
    QLineEdit * searchText;

    ImageButton * helpButton;
    QMenu * helpMenu;
    QAction * helpTopics;
    QAction * checkUpdates;
    QAction * DeviceSupport;
    QAction * connectToForums;
    QAction * about;
    QAction * systemInformation;
    QAction * diagnosticParameter;

    ImageButton * optionsButton;
    QMenu * optionsMenu;
    QAction * testDevice;
    QAction * resetSettings;

    ImageButton * searchButton;
    QLineEdit * searchBar;

    ImageButton * generalTabButton;
    ImageButton * lockTabButton;
    ImageButton * networkTabButton;
    ImageButton * ipAddressTabButton;
    ImageButton * informationTabButton;
    ImageButton * webSectionTabButton;
    ImageButton * activationTabButton;

    ImageButton * upgradeButton;
    ImageButton * accountButton;
    ImageButton * settingsButton;

    ImageButton * connectButton;
    AnimateButton * connectingButton;

    ImageButton * disconnectButton;
    AnimateButton * disconnectingButton;

    QLabel * signalStrengthLabel;
    QLabel * signalTextLabel;
    QLabel * helpLabel;
    QLabel * operatorLabel;

    QList<QPixmap> signalStrengthImage;
    QList<QPixmap> signalTextImage;

    QImage * background;

    ImageButton * leftLogoLabel;
    ImageButton * rightLogoLabel;

    QPoint offset;
    bool moving;

    Tabs activeTab;
    bool connected;

    QAction * minimizeAction;
    QAction * restoreAction;
    QAction * safelyRemoveAction;
    QAction * upgradeAction;
    QAction * quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QTimer * signalStrengthTimer;
    QTimer * systemInformationTimer;
    QTimer * toolTipTimer;

    QHttp * httpRequest;

    QBuffer * leftImageBuffer;
    QBuffer * rightImageBuffer;

    QByteArray * leftImageData;
    QByteArray * rightImageData;

    QUrl * leftImageUrl;
    QUrl * rightImageUrl;

    int leftImageRequestindex;
    int rightImageRequestindex;

    QWebView * leftLogoView;
    QWebView * rightLogoView;

    QString * leftLogoFilePath;
    QString * rightLogoFilePath;

    bool activationInProgress;

    QHttp * versionRequest;
    QHttp * setupRequest;

    QBuffer * versionBuffer;
    QBuffer * setupBuffer;

    QByteArray * versionData;
    QByteArray * setupData;
};

#endif // MAINWINDOW_H
