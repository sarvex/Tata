#ifndef DEFINES
#define DEFINES

#define OLIVE_DEVICE_NAME "Olive Modem"
#define OLIVE_DEVICE_TYPE "RASDT_Modem"
#define VENDOR_ID 0x22f4
#define PRODUCT_ID 0x0034
#define AT_PORT_NAME "Olive PCUI"
#define DIAGNOSTIC_PORT_NAME "Olive Diagnostics"

#define PORT_TIMEOUT 100
#define CHECK_PORT_TIMEOUT 3000
#define CDMA_ECIO_LENGTH 2

#define THREAD_SLEEP_TIMEOUT 200

#define DIAGNOSTIC_CYCLE_TIMEOUT 5000
#define FLASH_MESSAGE_TIMEOUT 30000
#define AT_COMMAND_DELAY 100

#define UPGRADE_TITLE "Upgrade Dialer"
#define NO_UPGRADE_TEXT "You are using the latest version of the dialer"

#define SIGNAL_STRENGTH_TIMEOUT 5000
#define SYSTEM_INFORMATION_TIMEOUT 10000
#define DIAL_WAIT_TIMEOUT 5000
#define LANGUAGE_TIMEOUT 1000
#define CARD_TYPE_TIMEOUT 1000
#define RESPONSE_TIMEOUT 5000
#define SID_NID_TIMEOUT 100
#define SECTOR_ID_TIMEOUT 10

#define SPLASH_SCREEN_TIMEOUT 1500

#define APPLICATION_NAME "TATA Photon Max VME500"

#define HELP_MENU "Help"
#define HELP_TOPICS "Help Topics"
#define CHECK_UPDATES "Check for Update"
#define DEVICE_SUPPORT "Device Support Page"
#define CONNECT_TO_FORUMS "Connect to TATA Indicom forums"
#define ABOUT "About"
#define SYSTEM_INFORMATION "System Information"
#define DIAGNOSTIC_PARAMETER "Diagnostic Parameter"
#define OPTIONS_MENU "Options"
#define TEST_DEVICE "Test Photon Max Device"
#define RESET_SETTINGS "Reset All Settings To Default"

#define GENERAL_STRING "General"
#define LOCK_STRING "Lock"
#define NETWORK_STRING "Network"
#define IP_STRING "IP"
#define INFORMATION_STRING "Info"
#define WEB_SECTION_STRING "Web"
#define ACTIVATION_STRING "Activate"
#define EMPTY_STRING ""

#define STATIC_STRING "Static"
#define DYNAMIC_STRING "Dynamic"

#define LINE '\r'
#define COLON ':'
#define COMMA ','
#define EQUAL '='
#define DOT '.'
#define SLASH '/'

#define LEFT_LOGO_FILE_NAME "/dialer-1.html"
#define RIGHT_LOGO_FILE_NAME "/dialer-R1.html"

#define HARDWARE_VERSION_RESPONSE "QualcommVer:"
#define SOFTWARE_VERSION_RESPONSE "version:"
#define COMPILE_DATE_RESPONSE "rel_time:"
#define DORMANT0 "^DSDORMANT:0"
#define DORMANT1 "^DSDORMANT:1"
#define ERROR_STRING "ERROR"

#define DISCONNECT_INTERNET "Please disconnect the Internet first, then close the Dialer!"

#define DRIVER_FILE_PATH "/System32/drivers/Oliveusbser.sys"

#define CONNECT_INTERNET "Do you woant to connect with Internet?"
#define LEFT_LOGO_URL "http://www.tataindicom.com/vme500"
#define RIGHT_LOGO_URL "http://www.tataindicom.com/vme500"
#define DEVICE_SUPPORT_URL "http://www.tataindicom.com/helpvme500"
#define CONNECT_TO_FORUMS_URL "http://www.tatateleservices.com/forums/"
#define YAHOO_SEARCH_STRING "http://in.yhs.search.yahoo.com/search?ei=UTF-8&partnerid=yhs-tata&fr=ond_onnetwork_ti_search&p="
#define MY_ACCOUNT_URL "http://www.tataindicom.com/myaccount.aspx"
#define DEFAULT_WEB_PAGE "http://www.tataindicom.com/vme500"

#define LEFT_LOGO_LINK "http://www.tataindicom.com/dialer-ads/dialer-1.html"
#define RIGHT_LOGO_LINK "http://www.tataindicom.com/dialer-ads/dialer-R1.html"
#define LEFT_IMAGE_LINK "http://www.tataindicom.com/dialer-ads/images/photon-left.jpg"
#define RIGHT_IMAGE_LINK "http://www.tataindicom.com/dialer-ads/images/photon-right.jpg"

#define PHOTONER "Dear Photoner,\n\nTo activate your Tata Photon Plus device please press continue"
#define CONTINUE "Continue"
#define MODEM_ACTIVATION "Modem Actitivation"
#define ACTIVATE_DIALOG "Activate Dialog"
#define ACTIVATION_TITLE "Activation"
#define ACTIVATION_IN_PROGRESS "Activation in progress. Please let the activation complete first"
#define ACTIVATION_SUCCESSFUL "Activation Successful"
#define ACTIVATION_FAILED "Activation Failed"
#define ACTIVATE_STRING "Activate"
#define PREPAID "Prepaid"
#define POSTPAID "Postpaid"
#define ENTER_PIN "Enter PIN"
#define CONTINUE_WITHOUT_PIN "Do you want to continue without PIN"
#define INVALID_PIN "Please input 14 digit PIN"
#define SELECT_CARD_TYPE "Please select a Card Type (Prepaid/Postpaid)"
#define ACTIVATION_NUMBER "*228"
#define PREPAID_NUMBER "1"
#define POSTPAID_NUMBER "2"
#define LANGUAGE "1"
#define ACTIVATION_PROGRESS_STRING "Activation in progress and can take a few minutes. Do not cancel the operation"
#define ENTER_NUMBER "Please enter your Tata Photon Number (Available in the starter Kit)"
#define MOBILE_NUMBER_LENGTH_ERROR_MESSAGE "Please enter 10 digits for Tata Photon Number"
#define MOBILE_NUMBER_LENGTH 10

#define REGISTRY_ABOUT "HKEY_LOCAL_MACHINE\\Software\\TATA Photon MAX\\VME500\\About"
#define REGISTRY_DIAGNOSTIC "HKEY_LOCAL_MACHINE\\Software\\TATA Photon MAX\\VME500\\Diagnostic"
#define SID_NID_KEY "SidNid"
#define SECTOR_ID_KEY "SectorID"
#define DRC_KEY "DRC"
#define CDMA_ECIO_KEY "CDMAECIO"
#define HDR_ECIO_KEY "HDRECIO"

#define CDMA_RSSI_LABEL "CDMA Rssi"
#define CDMA_PN_OFFSET_LABEL "PN Offset"
#define WALSH_CODE_LABEL "Walsh Code"
#define CHANNEL_NUMBER_LABEL "CHANNEL #"
#define BAND_CLASS_LABEL "Band Class"
#define TX_POWER_LABEL "TX Power"
#define RX_POWER_LABEL "RX Power"
#define BS_PREVIOUS_LABEL "BS PREV"
#define MS_PREVIOUS_LABEL "MS PREV"
#define PREVIOUS_IN_USE_LABEL "PREV in use"
#define PACKET_ZONE_ID_LABEL "Packet Zone ID"
#define LAST_ACTIVE_CALL_STATE_LABEL "Last Active Call State"

#define CDMA_RSSI_KEY "CDMARSSI"
#define CDMA_PN_OFFSET_KEY "CDMAPNOffset"
#define WALSH_CODE_KEY "WalshCode"
#define CHANNEL_NUMBER_KEY "CHANNEL"
#define BAND_CLASS_KEY "BandClass"
#define TX_POWER_KEY "TXPower"
#define RX_POWER_KEY "RXPower"
#define BS_PREVIOUS_KEY "BSPREV"
#define MS_PREVIOUS_KEY "MSPREV"
#define PREVIOUS_IN_USE_KEY "PrevInUse"
#define PACKET_ZONE_ID_KEY "PacketZoneID"
#define LAST_ACTIVE_CALL_STATE_KEY "LastActiveCallState"

#define HDR_RSSI_LABEL "HDR Rssi"
#define PER_LABEL "PER"
#define AT_STATE_LABEL "AT State"
#define DORMANT_STATE_LABEL "Dormant State"
#define ACTIVE_STATE_PN_OFFSET_LABEL "Active State PN Offset"
#define NEIGHBOR_SET_PN_OFFSET_LABEL "Neighbor Set PN Label"
#define NEIGHBOR_SET_ECIO_LABEL "Neighbor Set ECIO Label"

#define HDR_RSSI_KEY "HDRRSSI"
#define PER_KEY "PER"
#define AT_STATE_KEY "AtState"
#define DORMANT_STATE_KEY "DormantState"
#define ACTIVE_STATE_PN_OFFSET_KEY "AcitveStatePNOffset"
#define NEIGHBOR_SET_PN_OFFSET_KEY "NeoghborSetPNLable"
#define NEIGHBOR_SET_ECIO_KEY "NeoghborSetECIOLable"

#define DRIVER_VERSION_KEY "DialerVersion"
#define INSTALL_DATE_KEY "InstallDate"
#define COMPILE_DATE_KEY "CompileDate"
#define PRL_KEY "PRL"
#define ESN_KEY "ESN"
#define PESN_KEY "MEID"
#define SOFTWARE_VERSION_KEY "SoftwareVersion"
#define HARDWARE_VERSION_KEY "HardwareVersion"

#define DEVICE_TEST_FILE_NAME "DeviceTest.txt"
#define REGISTRY_ROOT "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
#define REGISTRY_AUTORUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define REGISTRY_KEY_ONE "TCPWindowSize"
#define REGISTRY_KEY_ONE_VALUE 65535
#define REGISTRY_KEY_TWO "SackOpts"
#define REGISTRY_KEY_TWO_VALUE 1
#define REGISTRY_KEY_THREE "TcpMaxDupAcks"
#define REGISTRY_KEY_THREE_VALUE 2
#define REGISTRY_KEY_FOUR "DefaultTTL"
#define REGISTRY_KEY_FOUR_VALUE 64
#define HARDWARE_VERSION_VALUE "USB\\VID_22F4&PID_0034&REV_0000&MI_04 USB\\VID_22F4&PID_0034&MI_04"
#define HARDWARE_ID_KEY "HardwareID"
#define HARWARE_VERSION_ROOT "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_22F4&PID_0042&MI_04\\6&13200d2d&0&0004"

#define PASSWORD_PROMPT "Please enter you password"
#define PASSWORD_TITLE "Password"
#define PASSWORD_LENGTH 4
#define EXISTING_LOCK "Existing Lock"
#define NEW_LOCK "New Lock"
#define CONFIRM_LOCK "Confirm Lock"
#define ERROR_MESSAGE "Error"
#define INFORMATION_MESSAGE "Information"
#define LOCK_MISMATCH "New Lock Mismatch"
#define LOCK_INVALID "Invalid Lock Entered"
#define LOCK_EMPTY "Empty Lock"
#define PROFILE_INVALID "Empty Profile"
#define CANNOT_DELETE_DEFAULT "Cannot Delete Default Profile"
#define PROFILE_NULL "No Profile Selected. Please select a profile"

#define AUTO_TERMINATE "Auto termination when system go to power saving mode"
#define AUTO_EXECUTE "Auto execution when system startup"
#define EXECUTE_ACCESS "Execute access manager on background"
#define AUTO_DIAL "Auto connect data call at startup"
#define USER_INFORMATION "User Account Information"

#define GENERAL_LOCK "General Lock"
#define INTERNET_LOCK "Internet Lock"
#define CHANGE_LOCK_CODE "Change Lock Code"

#define SET_DEFAULT_STRING "Set Default Profile"
#define ADD_PROFILE_STRING "Add"
#define EDIT_PROFILE_STRING "Edit"
#define DELETE_PROFILE_STRING "Delete"

#define NETWORK_MODE_ZERO "Hybrid"
#define NETWORK_MODE_ONE "TATA Photon Whiz"
#define NETWORK_MODE_TWO "TATA Photon Plus"
#define NETWORK_MODE_THREE "TATA Photon Max"

#define IP_TYPE "Set IP"
#define IP_LABEL "IP"
#define DNS_LABEL "DNS"
#define ALTERNATE_DNS_LABEL "Alternate DNS"
#define WINS_LABEL "WINS"
#define ALTERNATE_WINS_LABEL "Alternate WINS"

#define DIALER_INFORMATION_LABEL "TATA Photon Max Dialer"
#define DRIVER_INFORMATION_LABEL "Dialer Version"
#define INSTALL_DATE_LABEL "Installation Date"
#define COMPILE_DATE_LABEL "Compilation Date"
#define PRL_LABEL "PRL"
#define MEID_LABEL "MEID"
#define ESN_LABEL "pESN"
#define SOFTWARE_VERSION_LABEL "Software Version"
#define HARDWARE_VERSION_LABEL "Hardware Version"

#define SYSTEM_INFORMATION_LABEL "System Information"
#define OPERATING_SYSTEM_NAME_LABEL "OS Name"
#define OPERATING_SYSTEM_VERSION_LABEL "OS Version"
#define PROCESSOR_LABEL "Processor"
#define PHYSICAL_MEMORY_LABEL "Memory"
#define VIRTUAL_MEMORY_LABEL "Virtual Memory"
#define MANUFACTURER_LABEL "Manufacturer"

#define DIAGNOSTIC_LABEL "Diagnostics"
#define SID_LABEL "SID NID"
#define SECTOR_ID_LABEL "Sector ID"
#define DRC_LABEL "DRC"
#define CDMA_ECIO_LABEL "CDMA ECIO"
#define HDR_ECIO_LABEL "HDR ECIO"

#define START_TEST_STRING "Start Test"
#define DRIVER_TEST_LABEL "Driver Test"
#define REGISTRY_TEST_LABEL "Registry Test"
#define MODEM_TEST_LABEL "Modem Test"
#define PORT_TEST_LABEL "Port Test"
#define PROFILES_TEST_LABEL "Profiles Test"
#define UNKNOWN "Unknown"
#define PASS_STRING "Pass"
#define FAIL_STRING "Fail"

#define OPEN_DEFAULT_STRING "Open Default Page After Connect"

#define DATABASE_TYPE "QSQLITE"
#define DATABASE_NAME "OliveDatabase"
#define DATABASE_HOST "OliveHost"
#define DATABASE_USER "OliveUser"
#define DATABASE_PASSWORD "OlivePassword"

#define CREATE_PROFILE_TABLE "create table if not exists profile(name varchar(20), username varchar(40), password varchar(40), number varchar(40), connection int, authentication int, dynamic int, ip varchar(15), dns varchar(15), dnsAlternate varchar(15), wins varchar(15), winsAlternate varchar(15))"
#define SELECT_PROFILE_NAMES "SELECT name FROM profile"
#define SELECT_PROFILES "SELECT * FROM profile"
#define READ_PROFILE "SELECT * FROM profile WHERE name = :name"
#define READ_DEFAULT_PROFILE "SELECT * FROM profile WHERE connection != 0"
#define WRITE_PROFILE "UPDATE profile SET username = :username, password = :password, number = :number, connection = :connection, authentication = :authentication, dynamic = :dynamic, ip = :ip, dns = :dns, dnsAlternate = :dnsAlternate, wins = :wins, winsAlternate = :winsAlternate WHERE name = :name"
#define INSERT_PROFILE "INSERT INTO profile (name, username, password, number, connection, authentication, dynamic, ip, dns, dnsAlternate, wins, winsAlternate) VALUES (:name, :username, :password, :number, :connection, :authentication, :dynamic, :ip, :dns, :dnsAlternate, :wins, :winsAlternate)"
#define DELETE_PROFILE "DELETE FROM profile WHERE name = :name"

#define NAME ":name"
#define USERNAME ":username"
#define PASSWORD ":password"
#define NUMBER ":number"
#define CONNECTION ":connection"
#define AUTHENTICATION ":authentication"
#define DYNAMIC ":dynamic"
#define IP ":ip"
#define DNS ":dns"
#define DNS_ALTERNATE ":dnsAlternate"
#define WINS ":wins"
#define WINS_ALTERNATE ":winsAlternate"

#define PROFILE_NAME "TATA Photon MAX"
#define PROFILE_USERNAME "internet"
#define PROFILE_USERNAME_SUFFIX "@revb.ttsl.in"
#define PROFILE_PASSWORD "internet"
#define PROFILE_NUMBER "#777"
#define PROFILE_CONNECTION true
#define PROFILE_AUTHENTICATION AUTO
#define PROFILE_DYNAMIC true
#define PROFILE_IP "0.0.0.0"
#define PROFILE_DNS "0.0.0.0"
#define PROFILE_DNS_ALTERNATE "0.0.0.0"
#define PROFILE_WINS "0.0.0.0"
#define PROFILE_WINS_ALTERNATE "0.0.0.0"

#define PROFILE_NAME_LABEL "Profile Name"
#define USER_NAME_LABEL "User Name"
#define PASSWORD_LABEL "Password"
#define NUMBER_LABEL "Number"
#define AUTHENTICATION_LABEL "Authentication Type"
#define DEFAULT_CONNECTION "Set Default"

#define NETWORK_MODE_LABEL "Network Mode"
#define PROFILE_NAME_LABEL "Profile Name"

#define CREATE_TABLE_SENTBOX "create table if not exists sentbox(number varchar(20),message varchar(170),datetim varchar(40))"
#define CREATE_TABLE_RECYCLE "create table if not exists recycle(number varchar(20),message varchar(170),datetim varchar(40),storage varchar(40))"
#define CREATE_TABLE_DRAFTS "create table if not exists drafts(number varchar(20),message varchar(170),datetim varchar(40))"
#define CREATE_TABLE_PHONEBOOK "create table if not exists phonebook(name varchar(40),birthday varchar(40),company varchar(60),mobile varchar(18),telephone varchar(20),email varchar (50),memo varchar (100))"
#define CREATE_TABLE_PHONEBOOK_RECYCLE "create table if not exists phonebook_recycle(name varchar(40),birthday varchar(40),company varchar(60),mobile varchar(18),telephone varchar(20),email varchar (50),memo varchar (100))"
#define CREATE_TABLE_CONNECTTION_LOGS "create table if not exists connlogs(start_datetim varchar(40),stop_datetim varchar(40),sent_data varchar(20),rcvd_data varchar(40))"

#define CREATE_TABLE_PREFERENCE "create table if not exists preferences(setting INTEGER PRIMARY KEY ASC,value varchar(20))"
#define SELECT_PREFERENCES "SELECT * FROM preferences"
#define READ_PREFERENCE "SELECT value FROM preferences WHERE setting = :setting"
#define WRITE_PREFERENCE "UPDATE preferences SET value = :value WHERE setting = :setting"
#define INSERT_PREFERENCE "INSERT INTO preferences(setting, value) VALUES (:setting, :value)"
#define SETTING ":setting"
#define VALUE ":value"

#define TRUE_STRING "true"
#define FALSE_STRING "false"

#define OK_STRING "OK"
#define CANCEL_STRING "Cancel"

#define AUTO_STRING "Auto"
#define PAP_STRING "PAP"
#define CHAP_STRING "CHAP"


#define AUTO_TERMINATE_SETTING "11"
#define AUTO_EXECUTE_SETTING "12"
#define EXECUTE_ACCESS_SETTING "13"
#define AUTO_DIAL_SETTING "14"
#define USER_INFORMATION_SETTING "15"

#define GENERAL_LOCK_SETTING "21"
#define INTERNET_LOCK_SETTING "22"
#define LOCK_CODE_SETTING "23"

#define NETWORK_MODE_SETTING "31"
#define PROFILE_NAME_SETTING "32"
#define DEFAULT_PROFILE_SETTING "33"
#define OPEN_DEFAULT_SETTING "34"

#define DYNAMIC_IP_SETTING "41"
#define DEFAULT_IP_SETTING "42"
#define DNS_SETTING "43"
#define ALTERNATE_DNS_SETTING "44"
#define DEFAULT_WINS_SETTING "45"
#define ALTERNATE_WINS_SETTING "46"

#define CLOSE_APPLICATION "Close Application Only"
#define CLOSE_AND_SAFELY_REMOVE "Close Application & Safely Remove Device"
#define CANCEL_STRING "Cancel"

#define PIN_LENGTH 14

#define VERSION_URL "www.olive.net/vme500/tata/version"
#define SETUP_URL "www.olive.net/vme500/tata/setup"

#define VERSION 0001
#define NETWORK_ERROR "Network Error"
#define VERSION_ERROR "Unable to contact Upgrader Server"
#define SETUP_ERROR "Unable to download the latest Setup"
#define NEW_VERSION "New Version"
#define NETWORK_SUCCESS "Network Success"
#define VERSION_SUCCESS "A new version is available, Click Upgrade to download"
#define VERSION_LATEST "You are using the latest version"
#define SETUP_SUCCESS "Latest version downloaded, Do you wnat to run the setup"

enum Tabs {
	NONE,
	GENERAL,
	LOCK,
	NETWORK,
	IP_ADDRESS,
	INFORMATION,
	WEB_SECTION,
	ACTIVATION,
	TAB_COUNT
};

enum ServiceStatus {
	NO_SERVICES_STATUS = 0,
	LIMITED_SERVICES,
	SERVICE_VALID,
	LIMITED_REGION_SERVICE,
	ENERGY_SAVING_DEEP_SLEEP
};

enum ServiceDomain {
	NO_SERVICES_DOMAIN = 0,
	CS_ONLY = 1,
	PS_ONLY = 2,
	PS_CS = 3,
	CS_PS_NOT_REGISTERED_SEARCHING_STATE = 4,
	CDMA_NOT_SUPPORTED = 255
};

enum RoamingStatus {
	NOT_ROAMING = 0,
	ROAMING = 1
};

enum SystemMode {
	NO_SERVICE_MODE = 0,
	CDMA_MODE = 2,
	HDR_MODE = 4,
	CDMA_HDR_HYBRID = 8
};

enum SimStatus {
	SIM_NOT_PRESENT,
	SIM_PRESENT
};

enum AuthenticationType {
	AUTO = 0,
	PAP,
	CHAP
};

enum NetworkMode {
	ONE_X = 0,
	HDR,
	HYBRID
};

#endif // DEFINES
