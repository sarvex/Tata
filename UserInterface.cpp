#include "UserInterface.h"

// Application
const QPoint UserInterface::topLeftPoint(0, 0);

const int UserInterface::windowWidth = 800;
const int UserInterface::windowHeight = 500;

// Left Panel
const int UserInterface::leftColumnLeft = 25;
const int UserInterface::leftColumnTop = 29;
const int UserInterface::leftColumnWidth = 126;
const int UserInterface::leftColumnHeight = 443;

const int UserInterface::leftItemLeft = 26;
const int UserInterface::leftItemTop = 28;
const int UserInterface::leftItemWidth = 126;
const int UserInterface::leftItemHeight = 443;
const int UserInterface::leftItemHeightOffset = 50;
const int UserInterface::leftItemWidthOffset = 21;

// Right Panel
const int UserInterface::rightColumnLeft = 643;
const int UserInterface::rightColumnTop = 29;
const int UserInterface::rightColumnWidth = 126;
const int UserInterface::rightColumnHeight = 443;

const int UserInterface::rightItemLeft = 648;
const int UserInterface::rightItemTop = 28;
const int UserInterface::rightItemWidth = 126;
const int UserInterface::rightItemHeight = 443;
const int UserInterface::rightItemHeightOffset = 50;
const int UserInterface::rightItemWidthOffset = 21;

// Display Area
const int UserInterface::displayAreaLeft = 173;
const int UserInterface::displayAreaTop = 142;
const int UserInterface::displayAreaWidth = 450;
const int UserInterface::displayAreaHeight = 150;


// Activation Tab
const int UserInterface::photonerLeft = 183;
const int UserInterface::photonerTop = 180;
const int UserInterface::photonerWidth = 410;
const int UserInterface::photonerHeight = 42;

// General Tab
const int UserInterface::tabGeneralLeft = 50;
const int UserInterface::tabGeneralTop = 10;
const int UserInterface::tabGeneralWidth = 300;
const int UserInterface::tabGeneralHeight = 20;
const int UserInterface::tabGeneralOffset = 20;

// Lock Tab
const int UserInterface::tabLockLeft = 50;
const int UserInterface::tabLockTop = 20;
const int UserInterface::tabLockWidth = 200;
const int UserInterface::tabLockHeight = 20;
const int UserInterface::tabLockOffset = 20;

// Network Tab
const int UserInterface::tabNetworkLeft = 50;
const int UserInterface::tabNetworkTop = 20;
const int UserInterface::tabNetworkWidth = 120;
const int UserInterface::tabNetworkHeight = 20;
const int UserInterface::tabNetworkOffset = 20;
const int UserInterface::tabNetworkGap = 60;
const int UserInterface::tabNetworkGapWidth = 50;

// Information Tab
const int UserInterface::tabInformationLeft = 50;
const int UserInterface::tabInformationTop = 5;
const int UserInterface::tabInformationWidth = 100;
const int UserInterface::tabInformationHeight = 20;
const int UserInterface::tabInformationOffset = 15;
const int UserInterface::tabInformationGap = 120;

// IP Address
const int UserInterface::tabIpAddressLeft = 60;
const int UserInterface::tabIpAddressTop = 10;
const int UserInterface::tabIpAddressWidth = 100;
const int UserInterface::tabIpAddressHeight = 18 ;
const int UserInterface::tabIpAddressOffset = 22;
const int UserInterface::tabIpAddressGap = 110;

// Web Section
const int UserInterface::tabWebSectionLeft = 10;
const int UserInterface::tabWebSectionTop = 10;
const int UserInterface::tabWebSectionWidth = 100;
const int UserInterface::tabWebSectionHeight = 20 ;
const int UserInterface::tabWebSectionOffset = 30;
const int UserInterface::tabWebSectionGap = 110;

const QRect UserInterface::tabActivationPrepaid (30, 10, 60, 20) ;
const QRect UserInterface::tabActivationPostpaid (100, 10, 60, 20);
const QRect UserInterface::tabActivationPinLabel (30, 40, 60, 20 );
const QRect UserInterface::tabActivationPin (100, 40, 100, 20);
const QRect UserInterface::tabActivationActivate (100, 70, 60, 20);

const QRect UserInterface::flashMessageText(10, 10, 400, 100);


// Display Area Tab
const int UserInterface::displayAreaTabbarItemHeight = 20;
const int UserInterface::displayAreaTabbarItemWidth = 60;

// top banner
const int UserInterface::topBannerTop = 63;

const QRect UserInterface::closeButton (606,UserInterface::topBannerTop,24,24);
const QRect UserInterface::minimizeButton (579,UserInterface::topBannerTop,24,24);
const QRect UserInterface::helpMenu (475, UserInterface::topBannerTop, 20, 10);
const QRect UserInterface::optionsMenu (510, UserInterface::topBannerTop, 33, 10);
const QRect UserInterface::yahoo(170, UserInterface::topBannerTop, 294, 33);
const QRect UserInterface::searchText(200, UserInterface::topBannerTop+6, 200, 20);
const QRect UserInterface::search(405, UserInterface::topBannerTop, 58, 33);

// bottom banner
const int UserInterface::bottomBannerAnchor = 385;


const int UserInterface::bottomBannerItemZeroWidth = 62;
const int UserInterface::bottomBannerItemOneWidth = 62;
const int UserInterface::bottomBannerItemTwoWidth = 110;
const int UserInterface::bottomBannerItemThreeWidth = 67;
const int UserInterface::bottomBannerItemFourWidth = 177;

const int UserInterface::bottomBannerItemZeroHeight = 6;
const int UserInterface::bottomBannerItemOneHeight = 36;
const int UserInterface::bottomBannerItemTwoHeight = 12;
const int UserInterface::bottomBannerItemThreeHeight = 60;
const int UserInterface::bottomBannerItemFourHeight = 62;

const int UserInterface::bottomBannerItemZeroLeft = 175;
const int UserInterface::bottomBannerItemOneLeft = 175;
const int UserInterface::bottomBannerItemTwoLeft = 250;
const int UserInterface::bottomBannerItemThreeLeft = 370;
const int UserInterface::bottomBannerItemFourLeft = 450;

const int UserInterface::bottomBannerItemZeroTop = UserInterface::bottomBannerAnchor - bottomBannerItemZeroHeight;
const int UserInterface::bottomBannerItemOneTop = UserInterface::bottomBannerAnchor - bottomBannerItemOneHeight - bottomBannerItemZeroHeight;
const int UserInterface::bottomBannerItemTwoTop = UserInterface::bottomBannerAnchor - bottomBannerItemTwoHeight;
const int UserInterface::bottomBannerItemThreeTop = UserInterface::bottomBannerAnchor - bottomBannerItemThreeHeight;
const int UserInterface::bottomBannerItemFourTop = UserInterface::bottomBannerAnchor - bottomBannerItemFourHeight;

// Tab Bar
const int UserInterface::tabBarLeft = 170;
const int UserInterface::tabBarTop = 410;
const int UserInterface::tabBarWidth = 500 ;
const int UserInterface::tabBarHeight = 0 ;  // TODO

const int UserInterface::tabBarItemCount = 6;
const int UserInterface::tabBarItemWidth = 57;
const int UserInterface::tabBarItemHeight = 53;


// Calculations
const int UserInterface::tabBarSpaceWidth = (UserInterface::tabBarWidth
                                             - (UserInterface::tabBarItemCount * UserInterface::tabBarItemWidth))
                                            / (UserInterface::tabBarItemCount + 1 );
const int UserInterface::tabBarItemOffset = UserInterface::tabBarItemWidth
                                            + UserInterface::tabBarSpaceWidth;

const QRect UserInterface::upgradeButton  (tabBarFirstItemLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::activateButton  (tabBarSecondLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::logButton  (tabBarThirdLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::speedoMeterButton  (tabBarFourthLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::browserButton  (tabBarFifthItemLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::accountButton  (tabBarMiddleLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);
const QRect UserInterface::settingsButton  (tabBarSixthItemLeft, UserInterface::tabBarTop, UserInterface::tabBarItemWidth, UserInterface::tabBarItemHeight);

const int UserInterface::tabBarFirstItemLeft = UserInterface::tabBarLeft
                                               + 0 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarSecondLeft = UserInterface::tabBarLeft
                                            + 1 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarThirdLeft = UserInterface::tabBarLeft
                                           + 2 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarFourthLeft = UserInterface::tabBarLeft
                                            + 3 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarFifthItemLeft = UserInterface::tabBarLeft
                                               + 4 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarSixthItemLeft = UserInterface::tabBarLeft
                                               + 5 * UserInterface::tabBarItemOffset;
const int UserInterface::tabBarMiddleLeft = UserInterface::tabBarLeft
                                            + 2.5 * UserInterface::tabBarItemOffset;

const QRect UserInterface::leftLogoLabel (UserInterface::leftItemLeft, UserInterface::leftItemTop, UserInterface::leftItemWidth, UserInterface::leftItemHeight);
const QRect UserInterface::rightLogoLabel (UserInterface::rightItemLeft, UserInterface::rightItemTop, UserInterface::rightItemWidth, UserInterface::rightItemHeight);

const QRect UserInterface::bottomBannerItemZero (bottomBannerItemZeroLeft, bottomBannerItemZeroTop, bottomBannerItemZeroWidth, bottomBannerItemZeroHeight);
const QRect UserInterface::bottomBannerItemOne (bottomBannerItemOneLeft, bottomBannerItemOneTop, bottomBannerItemOneWidth, bottomBannerItemOneHeight);
const QRect UserInterface::bottomBannerItemTwo (bottomBannerItemTwoLeft, bottomBannerItemTwoTop, bottomBannerItemTwoWidth, bottomBannerItemTwoHeight);
const QRect UserInterface::bottomBannerItemThree (bottomBannerItemThreeLeft, bottomBannerItemThreeTop, bottomBannerItemThreeWidth, bottomBannerItemThreeHeight);
const QRect UserInterface::bottomBannerItemFour (bottomBannerItemFourLeft, bottomBannerItemFourTop, bottomBannerItemFourWidth, bottomBannerItemFourHeight);

const QRect UserInterface::displayAreaTabbar (displayAreaLeft, displayAreaTop, displayAreaWidth, displayAreaTabbarItemHeight);
const QRect UserInterface::displayArea (displayAreaLeft, displayAreaTop + displayAreaTabbarItemHeight, displayAreaWidth, displayAreaHeight);

const QRect UserInterface::generalTabButton  (UserInterface::displayAreaLeft + ( 0 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::lockTabButton  (UserInterface::displayAreaLeft + ( 1 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::ipAddressTabButton  (UserInterface::displayAreaLeft + ( 2 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::networkTabButton  (UserInterface::displayAreaLeft + ( 3 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::webSectionTabButton  (UserInterface::displayAreaLeft + ( 4 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::informationTabButton  (UserInterface::displayAreaLeft + ( 5 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);
const QRect UserInterface::activationTabButton  (UserInterface::displayAreaLeft + ( 6 * UserInterface::displayAreaTabbarItemWidth) , UserInterface::displayAreaTop, UserInterface::displayAreaTabbarItemWidth, UserInterface::displayAreaTabbarItemHeight);

const QRect UserInterface::photoner (UserInterface::photonerLeft, UserInterface::photonerTop, UserInterface::photonerWidth, UserInterface::photonerHeight);

const QRect UserInterface::tabGeneralAutoTerminate(UserInterface::tabGeneralLeft, UserInterface::tabGeneralTop + (0 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth, UserInterface::tabGeneralHeight );
const QRect UserInterface::tabGeneralAutoExecute(UserInterface::tabGeneralLeft, UserInterface::tabGeneralTop + (1 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth, UserInterface::tabGeneralHeight );
const QRect UserInterface::tabGeneralExecuteAccess(UserInterface::tabGeneralLeft, UserInterface::tabGeneralTop + (2 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth, UserInterface::tabGeneralHeight );
const QRect UserInterface::tabGeneralAutoDial(UserInterface::tabGeneralLeft, UserInterface::tabGeneralTop + (3 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth, UserInterface::tabGeneralHeight );
const QRect UserInterface::tabGeneralUserInformation(UserInterface::tabGeneralLeft, UserInterface::tabGeneralTop + (4 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth/2, UserInterface::tabGeneralHeight );
const QRect UserInterface::tabGeneralUserAccount(UserInterface::tabGeneralLeft + UserInterface::tabGeneralWidth/2, UserInterface::tabGeneralTop + (4 * UserInterface::tabGeneralOffset), UserInterface::tabGeneralWidth/2, UserInterface::tabGeneralHeight );

const QRect UserInterface::tabLockGeneralLock(UserInterface::tabLockLeft, UserInterface::tabLockTop + (0 * UserInterface::tabLockOffset), UserInterface::tabLockWidth, UserInterface::tabLockHeight );
const QRect UserInterface::tabLockInternetLock(UserInterface::tabLockLeft, UserInterface::tabLockTop + (1 * UserInterface::tabLockOffset), UserInterface::tabLockWidth, UserInterface::tabLockHeight );
const QRect UserInterface::tabLockChangeLockCode(UserInterface::tabLockLeft, UserInterface::tabLockTop + (3 * UserInterface::tabLockOffset), UserInterface::tabLockWidth, UserInterface::tabLockHeight );

const QRect UserInterface::tabIpAddressIpTypeLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (0 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressIpType( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (0 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressIpLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (1 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressIp( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (1 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressDnsLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (2 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressDns( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (2 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressAlternateDnsLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (3 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressAlternateDns( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (3 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressWinsLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (4 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressWins( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (4 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressAlternateWinsLabel( UserInterface::tabIpAddressLeft + (0 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (5 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );
const QRect UserInterface::tabIpAddressAlternateWins( UserInterface::tabIpAddressLeft + (1 * UserInterface::tabIpAddressGap), UserInterface::tabIpAddressTop + (5 * UserInterface::tabIpAddressOffset), UserInterface::tabIpAddressWidth, UserInterface::tabIpAddressHeight );

const QRect UserInterface::tabNetworkModeLabel(UserInterface::tabNetworkLeft, UserInterface::tabNetworkTop + (0 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkMode(UserInterface::tabNetworkLeft + 1.2*UserInterface::tabNetworkGap, UserInterface::tabNetworkTop + (0 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkProfileNamesLabel(UserInterface::tabNetworkLeft , UserInterface::tabNetworkTop + (2 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkProfileNames(UserInterface::tabNetworkLeft + 1.2*UserInterface::tabNetworkGap, UserInterface::tabNetworkTop + (2 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkAddProfile(UserInterface::tabNetworkLeft + (1.5 * UserInterface::tabNetworkGap) + tabNetworkWidth, UserInterface::tabNetworkTop + (2 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkGapWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkEditProfile(UserInterface::tabNetworkLeft + (2.5 * UserInterface::tabNetworkGap) + tabNetworkWidth, UserInterface::tabNetworkTop + (2 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkGapWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkDeleteProfile(UserInterface::tabNetworkLeft + (3.5 * UserInterface::tabNetworkGap)+ tabNetworkWidth, UserInterface::tabNetworkTop + (2 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkGapWidth, UserInterface::tabNetworkHeight );
const QRect UserInterface::tabNetworkDefaultProfile(UserInterface::tabNetworkLeft + 1.2*UserInterface::tabNetworkGap, UserInterface::tabNetworkTop + (3 * UserInterface::tabNetworkOffset), UserInterface::tabNetworkWidth, UserInterface::tabNetworkHeight );

const QRect UserInterface::tabInformationDialerInformationLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (0 * UserInterface::tabInformationOffset), 3*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationDriverVersionLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (1 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationDriverVersion( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (1 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationInstallDateLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (2 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationInstallDate( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (2 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationCompileDateLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (3 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationCompileDate( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (3 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationPrlLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (4 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationPrl( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (4 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationEsnLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (5 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationEsn( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (5 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationPEsnLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (6 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationPEsn( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (6 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationSoftwareVersionLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (7 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationSoftwareVersion( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (7 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationHarwareVersionLabel( UserInterface::tabInformationLeft + (0 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (8 * UserInterface::tabInformationOffset), UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );
const QRect UserInterface::tabInformationHarwareVersion( UserInterface::tabInformationLeft + (1 * UserInterface::tabInformationGap), UserInterface::tabInformationTop + (8 * UserInterface::tabInformationOffset), 2*UserInterface::tabInformationWidth, UserInterface::tabInformationHeight );

const QRect UserInterface::tabWebOpenDefault(30, 30, 200, 20);

const QRect UserInterface::dialogPassword(10, 10, 100, 20);
const QRect UserInterface::dialogOk(10, 40, 40, 20);
const QRect UserInterface::dialogCancel(60, 40, 40, 20);

const QRect UserInterface::progress(30, 30, 425, 30) ;
const QRect UserInterface::progressLabel(35, 70, 430, 30) ;

const QRect UserInterface::displayDialogOk(330, 130, 60, 20);
const QRect UserInterface::displayDialogCancel(390, 130, 60, 20);

const QRect UserInterface::activationSuccessful(170, 20, 425, 20);
const QRect UserInterface::mobileNumberLabel(20, 60, 320, 20);
const QRect UserInterface::mobileNumber(350, 60, 80, 20);
