#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <QPoint>
#include <QRect>
#include <QColor>

class UserInterface {
public:
	// Application
	static const QPoint topLeftPoint;
	static const int windowHeight;
	static const int windowWidth;

	static const QRect closeButton ;
	static const QRect minimizeButton ;
	static const QRect helpMenu ;
	static const QRect optionsMenu ;
	static const QRect yahoo;
	static const QRect search;
	static const QRect searchText;

	static const QRect upgradeButton;
	static const QRect activateButton;
	static const QRect logButton;
	static const QRect speedoMeterButton;
	static const QRect browserButton;
	static const QRect accountButton;
	static const QRect settingsButton;

	static const QRect leftLogoLabel ;
	static const QRect rightLogoLabel ;

	static const QRect bottomBannerItemZero ;
	static const QRect bottomBannerItemOne ;
	static const QRect bottomBannerItemTwo ;
	static const QRect bottomBannerItemThree ;
	static const QRect bottomBannerItemFour ;

	static const QRect displayAreaTabbar ;
	static const QRect displayArea ;

	static const QRect generalTabButton ;
	static const QRect lockTabButton ;
	static const QRect ipAddressTabButton ;
	static const QRect networkTabButton ;
	static const QRect webSectionTabButton ;
	static const QRect informationTabButton ;
	static const QRect activationTabButton ;

	static const QRect photoner;
	static const QRect progress;
	static const QRect progressLabel;

	static const QRect tabActivationPrepaid;
	static const QRect tabActivationPostpaid;
	static const QRect tabActivationPinLabel;
	static const QRect tabActivationPin;
	static const QRect tabActivationActivate;

	static const QRect tabGeneralAutoTerminate;
	static const QRect tabGeneralAutoExecute;
	static const QRect tabGeneralExecuteAccess;
	static const QRect tabGeneralAutoDial;
	static const QRect tabGeneralUserInformation;
	static const QRect tabGeneralUserAccount;

	static const QRect tabLockGeneralLock;
	static const QRect tabLockInternetLock;
	static const QRect tabLockChangeLockCode;

	static const QRect tabNetworkModeLabel;
	static const QRect tabNetworkMode;
	static const QRect tabNetworkProfileNamesLabel;
	static const QRect tabNetworkProfileNames;
	static const QRect tabNetworkAddProfile;
	static const QRect tabNetworkEditProfile;
	static const QRect tabNetworkDeleteProfile;
	static const QRect tabNetworkDefaultProfile;

	static const QRect tabInformationDialerInformationLabel;
	static const QRect tabInformationDriverVersionLabel;
	static const QRect tabInformationDriverVersion;
	static const QRect tabInformationInstallDateLabel;
	static const QRect tabInformationInstallDate;
	static const QRect tabInformationCompileDateLabel;
	static const QRect tabInformationCompileDate;
	static const QRect tabInformationPrlLabel;
	static const QRect tabInformationPrl;
	static const QRect tabInformationEsnLabel;
	static const QRect tabInformationEsn;
	static const QRect tabInformationPEsnLabel;
	static const QRect tabInformationPEsn;
	static const QRect tabInformationSoftwareVersionLabel;
	static const QRect tabInformationSoftwareVersion;
	static const QRect tabInformationHarwareVersionLabel;
	static const QRect tabInformationHarwareVersion;

	static const QRect tabIpAddressIpTypeLabel;
	static const QRect tabIpAddressIpType;
	static const QRect tabIpAddressIpLabel;
	static const QRect tabIpAddressIp;
	static const QRect tabIpAddressDnsLabel;
	static const QRect tabIpAddressDns;
	static const QRect tabIpAddressAlternateDnsLabel;
	static const QRect tabIpAddressAlternateDns;
	static const QRect tabIpAddressWinsLabel;
	static const QRect tabIpAddressWins;
	static const QRect tabIpAddressAlternateWinsLabel;
	static const QRect tabIpAddressAlternateWins;

	static const QRect displayDialogOk;
	static const QRect displayDialogCancel;

	static const QRect tabWebOpenDefault;

	static const QRect dialogPassword;
	static const QRect dialogOk;
	static const QRect dialogCancel;

	static const QRect flashMessageText;

	static const QRect activationSuccessful;
	static const QRect mobileNumberLabel;
	static const QRect mobileNumber;

private:
	// Tab Bar
	static const int tabBarLeft;
	static const int tabBarTop;
	static const int tabBarWidth;
	static const int tabBarHeight;

	static const int tabBarItemCount;
	static const int tabBarItemWidth;
	static const int tabBarItemHeight;
	static const int tabBarSpaceWidth;
	static const int tabBarItemOffset;

	static const int tabBarFirstItemLeft;
	static const int tabBarSecondLeft;
	static const int tabBarThirdLeft;
	static const int tabBarFourthLeft;
	static const int tabBarFifthItemLeft;
	static const int tabBarSixthItemLeft;
	static const int tabBarMiddleLeft;

	// Left Panel
	static const int leftColumnLeft;
	static const int leftColumnTop;
	static const int leftColumnWidth;
	static const int leftColumnHeight;

	static const int leftItemLeft;
	static const int leftItemTop;
	static const int leftItemWidth;
	static const int leftItemHeight;
	static const int leftItemWidthOffset;
	static const int leftItemHeightOffset;

	// Right Panel
	static const int rightColumnLeft;
	static const int rightColumnTop;
	static const int rightColumnWidth;
	static const int rightColumnHeight;

	static const int rightItemLeft;
	static const int rightItemTop;
	static const int rightItemWidth;
	static const int rightItemHeight;
	static const int rightItemWidthOffset;
	static const int rightItemHeightOffset;

	// bottom banner
	static const int bottomBannerAnchor;

	static const int bottomBannerItemZeroLeft;
	static const int bottomBannerItemOneLeft;
	static const int bottomBannerItemTwoLeft;
	static const int bottomBannerItemThreeLeft;
	static const int bottomBannerItemFourLeft;

	static const int bottomBannerItemZeroTop;
	static const int bottomBannerItemOneTop;
	static const int bottomBannerItemTwoTop;
	static const int bottomBannerItemThreeTop;
	static const int bottomBannerItemFourTop;

	static const int bottomBannerItemZeroWidth;
	static const int bottomBannerItemOneWidth;
	static const int bottomBannerItemTwoWidth;
	static const int bottomBannerItemThreeWidth;
	static const int bottomBannerItemFourWidth;

	static const int bottomBannerItemZeroHeight;
	static const int bottomBannerItemOneHeight;
	static const int bottomBannerItemTwoHeight;
	static const int bottomBannerItemThreeHeight;
	static const int bottomBannerItemFourHeight;

	// Display Area
	static const int displayAreaLeft;
	static const int displayAreaTop;
	static const int displayAreaWidth;
	static const int displayAreaHeight;

	// Display Area Tabbar
	static const int displayAreaTabbarItemHeight;
	static const int displayAreaTabbarItemWidth;

	// Activation Tab
	static const int photonerLeft;
	static const int photonerTop;
	static const int photonerWidth;
	static const int photonerHeight;

	// General Tab
	static const int tabGeneralLeft;
	static const int tabGeneralTop;
	static const int tabGeneralWidth;
	static const int tabGeneralHeight;
	static const int tabGeneralOffset;

	// Lock Tab
	static const int tabLockLeft;
	static const int tabLockTop;
	static const int tabLockWidth;
	static const int tabLockHeight;
	static const int tabLockOffset;

	// IP ADdress Tab
	static const int tabIpAddressLeft;
	static const int tabIpAddressTop;
	static const int tabIpAddressWidth;
	static const int tabIpAddressHeight;
	static const int tabIpAddressOffset;
	static const int tabIpAddressGap;
	static const int tabIpAddressGapWidth;

	// Network Tab
	static const int tabNetworkLeft;
	static const int tabNetworkTop;
	static const int tabNetworkWidth;
	static const int tabNetworkHeight;
	static const int tabNetworkOffset;
	static const int tabNetworkGap;
	static const int tabNetworkGapWidth;

	// Network Tab
	static const int tabWebSectionLeft;
	static const int tabWebSectionTop;
	static const int tabWebSectionWidth;
	static const int tabWebSectionHeight;
	static const int tabWebSectionOffset;
	static const int tabWebSectionGap;
	static const int tabWebSectionGapWidth;

	// Information Tab
	static const int tabInformationLeft;
	static const int tabInformationTop;
	static const int tabInformationWidth;
	static const int tabInformationHeight;
	static const int tabInformationOffset;
	static const int tabInformationGap;

	// Application
	static const int topBannerTop;


};

#endif // USER_INTERFACE
