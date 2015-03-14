#include "DeamonConnection.h"

#include "DeamonSetting.h"

#include <QDebug>
#include <QMessageBox>

#define errorMessageSize 256

static HRASCONN rasConnection = NULL;
static RASCONNSTATE rasConnectionState;
static DWORD longParameter = 0;

DeamonConnection* DeamonConnection::singleton = NULL;

DeamonConnection* DeamonConnection::getInstance () {
    if (NULL == singleton) {
        singleton = new DeamonConnection();
    }
    return (singleton);
}

DeamonConnection::DeamonConnection(QObject * parent) : QObject(parent) {
}

DeamonConnection::~DeamonConnection (){
}

bool DeamonConnection::connectDataCall() {
    bool result = false;

    Profile profile (DeamonSetting::getInstance()->getCurrentProfile());

    if (profile.getName().isEmpty()) {
        QMessageBox::critical (NULL, ERROR_MESSAGE, PROFILE_NULL, QMessageBox::Ok, QMessageBox::Ok);
        emit disconnected();
        return false;
    }

    // create and initialize dial up parameters
    RASDIALPARAMS rasDialParameters;
    ZeroMemory(&rasDialParameters, sizeof(RASDIALPARAMS));
    rasDialParameters.dwSize = sizeof(RASDIALPARAMS);

    // set connection name
    if (profile.getName().size() > 0) {
        WCHAR *connectionName = new WCHAR[profile.getName().size()+1];
        profile.getName().toWCharArray(connectionName);
        connectionName[profile.getName().size()] = 0;
        for (int count = 0; count < profile.getName().size(); count++) {
            rasDialParameters.szEntryName[count] = connectionName[count];
        }
    }

    // set connection username
    if (profile.getUserName().size()>0) {
        WCHAR * connectionUserName = new WCHAR[profile.getUserName().size()+1];
        profile.getUserName().toWCharArray(connectionUserName);
        connectionUserName[profile.getUserName().size()] = 0;
        for (int count = 0; count < profile.getUserName().size(); count++) {
            rasDialParameters.szUserName[count] = connectionUserName[count];
        }
    }

    // set connection password
    if (profile.getPassword().size()>0) {
        WCHAR *connectionPassword = new WCHAR[profile.getPassword().size()+1];
        profile.getPassword().toWCharArray(connectionPassword);
        connectionPassword[profile.getPassword().size()] = 0;
        for (int count = 0; count < profile.getPassword().size(); count++) {
            rasDialParameters.szPassword[count] = connectionPassword[count];
        }
    }

    rasDialParameters.szCallbackNumber[0] = ' ';
    rasDialParameters.szDomain[0] = '*';

    rasConnection = NULL;
    longParameter = -1;

    // connect the call
    DWORD returnValue = RasDial(NULL, NULL, &rasDialParameters, 0L, (LPVOID)RasDialFunc, &rasConnection);

    if (ERROR_CANNOT_FIND_PHONEBOOK_ENTRY == returnValue) {
        if (false == this->createRasPhonebookConnectionEntry(profile, true)) {
            emit disconnected();
            return false;
        } else {
            returnValue = RasDial(NULL, NULL, &rasDialParameters, 0L, (LPVOID)RasDialFunc, &rasConnection);
            qDebug () << "Ras Dial :" << returnValue;
        }
    }

    if (returnValue) {
        result = true;
    } else {
        WCHAR errorMessage[errorMessageSize];
        if (ERROR_SUCCESS  == RasGetErrorString(returnValue, errorMessage, errorMessageSize)) {
            qDebug () << "Error Message :" << "returnValue :" << returnValue << " : "<< QString::fromWCharArray(errorMessage);
        } else {
            qDebug () << "Failure getting RAS error message = " << returnValue;
        }
    }
    return (result);
}

bool DeamonConnection::disconnectDataCall() {
    bool result = false;

    // create and initialize ras connection status
    RASCONNSTATUS rasConnectionStatus;
    ZeroMemory(&rasConnectionStatus, sizeof(RASCONNSTATUS));
    rasConnectionStatus.dwSize = sizeof(RASCONNSTATUS);

    DWORD returnValue = RasGetConnectStatus(rasConnection, &rasConnectionStatus);

    if (ERROR_INVALID_HANDLE != returnValue) {

        returnValue = RasHangUp(rasConnection);
        qDebug () << "RasHangUp Return Value : " << returnValue;

        returnValue = RasGetConnectStatus(rasConnection, &rasConnectionStatus);
        while (returnValue != ERROR_INVALID_HANDLE) {
            returnValue = RasGetConnectStatus(rasConnection, &rasConnectionStatus);
        }

        rasConnection = NULL;
        result =  true;

        emit disconnected();
    }

    return(result);
}

bool DeamonConnection::createRasPhonebookConnectionEntry(const Profile& profile, bool newEntry  ) {

    DWORD dwError = ERROR_SUCCESS;
    LPTSTR rasEntryName = (LPTSTR)profile.getName().utf16();

    // Allocate heap memory and initialize RASENTRY structure
    LPRASENTRY rasEntry = (LPRASENTRY)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(RASENTRY));
    if (NULL == rasEntry) {
        qDebug("HeapAlloc failed");
        HeapFree(GetProcessHeap(), 0, rasEntry);
        return(false);
    }

    // set dwSize to sizeof(RASENTRY) to identify the version of the structure
    rasEntry->dwSize = sizeof(RASENTRY);

    // qDebug () << "assign the connection phone number";
    WCHAR *phoneNumber = new WCHAR[profile.getNumber().size()];
    profile.getNumber().toWCharArray(phoneNumber);
    phoneNumber[profile.getNumber().size()] = 0;

    for (int count = 0; count < profile.getNumber().size(); count++)
        rasEntry->szLocalPhoneNumber[count] = phoneNumber[count];

    // qDebug () "assign device name ";
    QString modemName = OLIVE_DEVICE_NAME;
    WCHAR *deviceName = new WCHAR[modemName.size()];
    modemName.toWCharArray(deviceName);
    deviceName[modemName.size()] = 0;

    for (int count = 0; count < modemName.size(); count++)
        rasEntry->szDeviceName[count] = deviceName[count];

    // qDebug () << "assign the device type";
    QString modemType = OLIVE_DEVICE_TYPE;
    WCHAR *deviceType = new WCHAR[modemType.size()];
    modemType.toWCharArray(deviceType);
    deviceType[modemType.size()] = 0;

    for (int count = 0; count < modemType.size(); count++)
        rasEntry->szDeviceType[count] = deviceType[count];

    // set the Point-to-Point Protocol (PPP). protocol
    rasEntry->dwFramingProtocol = RASFP_Ppp;

    // try to negotiate both IPv4 and IPv6 protocols
    rasEntry->dwfNetProtocols = RASNP_Ip /*| RASNP_Ipv6*/;

    // set the default connection options
    rasEntry->dwfOptions = 0;
    rasEntry->dwfOptions = RASEO_RemoteDefaultGateway | RASEO_IpHeaderCompression | RASEO_SwCompression;

    switch (profile.getAuthenticationType()) {
    case PAP : {
            rasEntry->dwfOptions = rasEntry->dwfOptions | RASEO_RequirePAP;
        } break;
    case CHAP : {
            rasEntry->dwfOptions = rasEntry->dwfOptions | RASEO_RequireCHAP;
        } break;
    case AUTO : {
            rasEntry->dwfOptions = rasEntry->dwfOptions | RASEO_RequirePAP | RASEO_RequireCHAP;
        } break;
    }

    rasEntry->dwfOptions |= RASEO_ShowDialingProgress | RASEO_RemoteDefaultGateway | RASEO_IpHeaderCompression | RASEO_PreviewPhoneNumber;
    rasEntry->dwfOptions2 |=RASEO2_DontNegotiateMultilink;

    rasEntry->dwRedialCount = 3;
    rasEntry->dwRedialPause = 60;
    rasEntry->dwIdleDisconnectSeconds = RASIDS_Disabled;


    rasEntry->dwType = RASET_Phone;

    if ( false == profile.getDynamic()) {
        rasEntry->dwfOptions |= RASEO_SpecificNameServers | RASEO_SpecificIpAddr ;
        // RAS entry has a static IP set the properties.
        rasEntry->ipaddr = this->convertStringToIpAddress(profile.getIpAddress());
        rasEntry->ipaddrDns  = this->convertStringToIpAddress(profile.getDnsAddress());
        rasEntry->ipaddrDnsAlt = this->convertStringToIpAddress(profile.getDnsAlternateAddress());
        rasEntry->ipaddrWins = this->convertStringToIpAddress(profile.getWinsAddress());
        rasEntry->ipaddrWinsAlt  = this->convertStringToIpAddress(profile.getWinsAlternateAddress());
    }

    if (dwError != S_OK) {
        qDebug() << "Structure initilization failed: Error = " << dwError;
        HeapFree(GetProcessHeap(), 0, rasEntry);
        return(false);
    }

    // Validate the RAS entry
    switch (RasValidateEntryName(NULL, rasEntryName)) {
    case ERROR_SUCCESS: {
            qDebug() << "Entry name: "<< QString::fromWCharArray(rasEntryName) << "is valid but doesn't exist in the default phone book";
        }break;
    case ERROR_INVALID_NAME:{
            qDebug() << "Entry name: "<< QString::fromWCharArray(rasEntryName) << " is invalid\n";
            HeapFree(GetProcessHeap(), 0, rasEntry);
            return(false);
        } break;
    case ERROR_ALREADY_EXISTS: {
            qDebug() << "Entry name: "<< QString::fromWCharArray(rasEntryName) << " already exists in the default phone book";
            if (true ==  newEntry) {
                qDebug () << "Returning without editing" << newEntry;
                HeapFree(GetProcessHeap(), 0, rasEntry);
                return(false);
            }
        }break;
    default:{
            qDebug() << "RasValidateEntryName failed: Unknown Error";
            HeapFree(GetProcessHeap(), 0, rasEntry);
            return(false);
        }break;
    }

    qDebug() << "Create and set the new entry's properties";
    if (ERROR_SUCCESS != RasSetEntryProperties(NULL, rasEntryName, rasEntry, rasEntry->dwSize, NULL, 0)) {
        qDebug () << "RasSetEntryProperties Failed";
    }

    HeapFree(GetProcessHeap(), 0, rasEntry);
    qDebug () << "Exiting DeamonConnection::createRasPhonebookConnectionEntry";
    return(true);
}

bool DeamonConnection::readRasPhonebookConnectionEntry(const QString& connectionName) {
    qDebug () << "Entering DeamonConnection::readRasPhonebookConnectionEntry";
    DWORD returnValue = ERROR_SUCCESS;
    LPTSTR rasEntryName = (LPTSTR)connectionName.utf16();

    // Allocate heap memory and initialize RASENTRY structure
    LPRASENTRY rasEntry = (LPRASENTRY)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(RASENTRY));
    if (NULL == rasEntry) {
        qDebug("HeapAlloc failed");
        HeapFree(GetProcessHeap(), 0, rasEntry);
        return(false);
    }

    rasEntry->dwSize = sizeof(RASENTRY);

    returnValue = RasGetEntryProperties(NULL, rasEntryName, rasEntry, &rasEntry->dwSize, NULL, NULL);
    if (ERROR_SUCCESS != RasSetEntryProperties(NULL, rasEntryName, rasEntry, rasEntry->dwSize, NULL, 0)) {
        qDebug () << "RasGetEntryProperties Failed";
        return false;
    }

    if ((rasEntry->dwfOptions & RASEO_SpecificIpAddr) || (rasEntry->dwfOptions & RASEO_SpecificNameServers)) {

        QString ipAddress = this->convertIpAddressToString(rasEntry->ipaddr);
        QString dnsAddress = this->convertIpAddressToString(rasEntry->ipaddrDns);
        QString dnsAlternateAddress = this->convertIpAddressToString(rasEntry->ipaddrDnsAlt);
        QString winsAddress = this->convertIpAddressToString(rasEntry->ipaddrWins);
        QString winsAlternateAddress = this->convertIpAddressToString(rasEntry->ipaddrWinsAlt);

        emit updateIpAddress(false, ipAddress, dnsAddress, dnsAlternateAddress, winsAddress, winsAlternateAddress);
    }

    HeapFree(GetProcessHeap(), 0, rasEntry);
    return(true);
}

bool DeamonConnection::deleteRasPhonebookConnectionEntry(const QString& connectionName) {

    WCHAR *name = new WCHAR[connectionName.size()];
    connectionName.toWCharArray(name);
    name[connectionName.size()] = 0;

    // Clean up: delete the new entry
    if (ERROR_SUCCESS != RasDeleteEntry(NULL, name)) {
        qDebug () << "Unable to delete Ras Entry" << connectionName;
        return (false);
    } else {
        return (true);
    }
}

RASIPADDR DeamonConnection::convertStringToIpAddress ( const QString& value) {
    RASIPADDR result;
    // qDebug () << "Entering DeamonConnection::convertStringToIpAddress" << value;

    QStringList stringList = value.split(DOT);
    // qDebug () << "Ipaddress split" << stringList;
    result.a = stringList.at(0).toInt();
    result.b = stringList.at(1).toInt();
    result.c = stringList.at(2).toInt();
    result.d = stringList.at(3).toInt();

    // qDebug () << "Exiting DeamonConnection::convertStringToIpAddress" << result.a << result.b << result.c << result.d;
    return result;
}

 QString DeamonConnection::convertIpAddressToString (RASIPADDR value) {
    // qDebug () << "Entering DeamonConnection::convertIpAddressToString" << value.a << value.b << value.c << value.d;

    QString result = QString::number(value.a).append(DOT).append(QString::number(value.b)).append(DOT).append(QString::number(value.c)).append(DOT).append(QString::number(value.d));

    // qDebug () << "IpAddress String :" << result;
    return result;
}


void CALLBACK RasDialFunc(UINT unMsg, RASCONNSTATE rasconnstate, DWORD dwError) {
    Q_UNUSED(unMsg);

    longParameter = dwError;
    rasConnectionState = rasconnstate;

    switch (longParameter) {
    case ERROR_SERVER_NOT_RESPONDING: {
            qDebug("Server Not Responding");
        }break;
    case ERROR_NETBIOS_ERROR: {
            qDebug("Netbios Error");
        }break;
    case ERROR_AUTH_INTERNAL: {
            qDebug("Internal Authentication Error");
        }break;
    case ERROR_CANNOT_GET_LANA: {
            qDebug("Cannot get LANA");
        }break;
    }

    if (longParameter) {
        WCHAR errorMessage[errorMessageSize];

        if(ERROR_SUCCESS == RasGetErrorString(longParameter, errorMessage, errorMessageSize)) {
            QString errorString = QString::fromWCharArray(errorMessage);
            qDebug () << longParameter << ":"<< errorString;
            switch (longParameter) {
            case 633: // fall through
            case 678: // fall through
            case 680: // fall through
            case 691: // fall through
            case 692: // fall through
            case 719: // fall through
            case 720: // fall through
            case 738: // fall through
            case 797:{
                emit DeamonConnection::getInstance()->rasError(longParameter, errorString);
                } break;
            }
        } else {
            qDebug () << " RasDialFunc Failure getting RAS error" << longParameter;
        }

        emit DeamonConnection::getInstance()->disconnected();
    }

    switch (rasconnstate) {
    case RASCS_OpenPort: {
            qDebug () << "Opening Port";
        }break;
    case RASCS_PortOpened: {
            qDebug () << "Port Opened";
        }break;
    case RASCS_ConnectDevice: {
            qDebug () << "Connecting Device";
        }break;
    case RASCS_DeviceConnected:{
            qDebug () << "Device Connected";
        }break;
    case RASCS_AllDevicesConnected: {
            qDebug () << "All Devices Connected";
        }break;
    case RASCS_Authenticate: {
            qDebug () << "Authenticating";
        }break;
    case RASCS_AuthNotify: {
            qDebug () << "Authentication Notify";
        }break;
    case RASCS_AuthRetry: {
            qDebug () << "Authentication Retry";
        }break;
    case RASCS_AuthCallback: {
            qDebug () << "Authentication Call Back";
        }break;
    case RASCS_AuthChangePassword:{
            qDebug () << "Authentication Change Password";
        }break;
    case RASCS_AuthProject:{
            qDebug () << "Authenticating Project";
        }break;
    case RASCS_AuthLinkSpeed:{
            qDebug () << "Authenticating Link Speed";
        }break;
    case RASCS_AuthAck:{
            qDebug () << "Authentication Acknowledge";
        }break;
    case RASCS_ReAuthenticate:{
            qDebug () << "Reauthentication";
        }break;
    case RASCS_Authenticated:{
            qDebug () << "Authenticated";
        }break;
    case RASCS_PrepareForCallback:{
            qDebug () << "Prepare For Callback";
        }break;
    case RASCS_WaitForModemReset:{
            qDebug () << "Waiting for Modem Reset";
        }break;
    case RASCS_WaitForCallback: {
            qDebug () << "Waiting for Callback";
        }break;
    case RASCS_Projected: {
            qDebug () << "Projected";
        }break;
    case RASCS_SubEntryConnected: {
            qDebug () << "Sub Entry Connected";
        }break;
    case RASCS_SubEntryDisconnected: {
            qDebug () << "Sub Entry Disconnected";
        }break;
    case RASCS_Interactive: {
            qDebug () << "Interactive";
        }break;
    case RASCS_RetryAuthentication: {
            qDebug () << "Retry Authentication";
        }break;
    case RASCS_CallbackSetByCaller:{
            qDebug () << "Callback Set by Caller";
        }break;
    case RASCS_PasswordExpired:{
            qDebug () << "Password Expired";
        }break;
    case RASCS_Connected: {
            qDebug () << "Connected";
            emit DeamonConnection::getInstance()->connected();
        }break;
    case RASCS_Disconnected: {
            qDebug () << "Disconnected";
            emit DeamonConnection::getInstance()->disconnected();
        }break;
    case RASCS_StartAuthentication: {
            qDebug () << "Start Authentication";
        }break;
    case RASCS_CallbackComplete: {
            qDebug () << "Callback Complete";
        }break;
    case RASCS_LogonNetwork: {
            qDebug () << "Logon Network";
        }break;
    case RASCS_InvokeEapUI:{
            qDebug () << "Invoke EapUI";
        }break;
    }
}

