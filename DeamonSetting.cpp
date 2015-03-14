#include "DeamonSetting.h"

#include "DeamonConnection.h"
#include "DeamonDatabase.h"
#include "DeamonInterface.h"
#include "Defines.h"

#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QSettings>

DeamonSetting* DeamonSetting::singleton = NULL;

const bool DeamonSetting::defaultAutoTerminate = true;
const bool DeamonSetting::defaultAutoExecute = true;
const bool DeamonSetting::defaultExecuteAccess = true;
const bool DeamonSetting::defaultAutoDial = false;

const bool DeamonSetting::defaultGeneralLock = false;
const bool DeamonSetting::defaultInternetLock = false;
const QString DeamonSetting::defaultLock = "0000";

const QString DeamonSetting::defaultNetworkMode = "Hybrid";
const QString DeamonSetting::defaultProfileName = "Tata Photon MAX";
const bool DeamonSetting::defaultDefaultProfile = true;

const Profile DeamonSetting::defaultCurrentProfile(PROFILE_NAME, PROFILE_USERNAME, PROFILE_PASSWORD, PROFILE_NUMBER, PROFILE_CONNECTION, PROFILE_AUTHENTICATION, PROFILE_DYNAMIC, PROFILE_IP, PROFILE_DNS, PROFILE_DNS_ALTERNATE, PROFILE_WINS, PROFILE_WINS_ALTERNATE);

const bool DeamonSetting::defaultOpenDefault = true;

DeamonSetting* DeamonSetting::getInstance () {
    if (NULL == singleton) {
        singleton = new DeamonSetting();
    }
    return (singleton);
}

DeamonSetting::DeamonSetting (QObject * parent) : QObject(parent), autoTerminate(false), autoExecute(false), executeAccess (false), autoDial (false), generalLock(false), internetLock(false), openDefault(true) {
    this->authenticationTypes.append(AUTO_STRING);
    this->authenticationTypes.append(PAP_STRING);
    this->authenticationTypes.append(CHAP_STRING);

    DeamonSetting::ReadSystemInformation();
}

DeamonSetting::~DeamonSetting () {

}

bool DeamonSetting::ReadSystemInformation () {
    QByteArray byteArray;
    QProcess process;

    process.start( "C:\\Windows\\System32\\systeminfo.exe", QStringList() );
    process.waitForFinished();
    byteArray = process.readAll();

    QList<QByteArray> systemInformation = byteArray.split( '\r' );

    for (int index = 0; index < systemInformation.size(); index++) {
        QString informationString(systemInformation.at(index));

        if (informationString.contains("OS Name")) {
            this->operatingSystemName = informationString.split(':').at(1).simplified();
        } else if (informationString.contains("OS Version") && !informationString.contains("BIOS Version")) {
            this->operatingSystemVersion = informationString.split(':').at(1).simplified();
        } else if (informationString.contains("Processor(s)")) {
            QString processor(systemInformation.at(index+1));
            this->processor = processor.split(':').at(1).simplified();
        } else if (informationString.contains("Total Physical Memory")) {
            this->physicalMemory = informationString.split(':').at(1).simplified();
        } else if (informationString.contains("Virtual Memory: Max Size")) {
            this->virtualMemory = informationString.split(':').at(2).simplified();
        } else if (informationString.contains("System Manufacturer")) {
            this->manufacturerName = informationString.split(':').at(1).simplified();
        } else if (informationString.contains("System Model")) {
            this->manufacturerModel = informationString.split(':').at(1).simplified();
        } else if (informationString.contains("System Type")) {
            this->manufacturerType = informationString.split(':').at(1).simplified();
        }
    }

    this->manufacturer = this->manufacturerName + " " + this->manufacturerModel + " " + this->manufacturerType;

    return (true);
}

QStringList DeamonSetting::getProfileNames () const {
    QStringList result;

    for (int i = 0; i < this->profiles.size(); ++i) {
        result.append(this->profiles.at(i).getName());
    }

    return (result);
}

bool DeamonSetting::getAutoTerminate () const {
    return (this->autoTerminate);
}

bool DeamonSetting::setAutoTerminate ( bool value ) {
    this->autoTerminate = value;
    DeamonDatabase::getInstance()->writeSetting(AUTO_TERMINATE_SETTING, this->boolToString (value));
    return (true);
}

bool DeamonSetting::getAutoExecute () const {
    return (this->autoExecute);
}

bool DeamonSetting::setAutoExecute ( bool value ) {
    this->autoExecute = value;
    DeamonDatabase::getInstance()->writeSetting(AUTO_EXECUTE_SETTING, this->boolToString (value));
    QSettings setting(REGISTRY_AUTORUN, QSettings::NativeFormat);

    if (value == true) {
        QString applicationPath = "\"" + qApp->applicationFilePath() + "\"";
        applicationPath.replace("/", "\\");
        setting.setValue(APPLICATION_NAME, QVariant::fromValue(applicationPath));
    } else {
        setting.remove(APPLICATION_NAME);
    }

    return (true);
}

bool DeamonSetting::getExecuteAccess () const {
    return (this->executeAccess);
}

bool DeamonSetting::setExecuteAccess ( bool value ) {
    DeamonDatabase::getInstance()->writeSetting(EXECUTE_ACCESS_SETTING, this->boolToString (value));
    this->executeAccess = value;
    return (true);
}

bool DeamonSetting::getAutoDial () const {
    return (this->autoDial);
}

bool DeamonSetting::setAutoDial ( bool value ) {
    DeamonDatabase::getInstance()->writeSetting(AUTO_DIAL_SETTING, this->boolToString(value));
    this->autoDial = value;
    return (true);
}

Profile DeamonSetting::getCurrentProfile () const {
    return (this->currentProfile);
}

bool DeamonSetting::setCurrentProfile ( const QString& value ) {
    this->currentProfile = DeamonDatabase::getInstance()->readProfile(value);
    emit reloadGeneral();
    emit reloadNetwork();
    return (true);
}

bool DeamonSetting::addProfile(const Profile& profile) {
    this->profiles.append(profile);
    qDebug() << "Settings::addProfile Before creating RAS" << profile.getName();
    DeamonConnection::getInstance()->createRasPhonebookConnectionEntry(profile, true);
    qDebug() << "Settings::addProfile After creating RAS" << profile.getName();
    DeamonDatabase::getInstance()->writeProfile(profile);
    qDebug() << "Settings::addProfile After updating database" << profile.getName();

    emit reloadGeneral();
    emit reloadNetwork();

    return (true);
}

bool DeamonSetting::editProfile(const Profile& profile) {
    bool result = false;

    for (int index = 0; index < this->profiles.size(); index++) {

        if (profiles.at(index).getName() == profile.getName()) {
            profiles.replace(index, profile);
            result = true;
        }
    }

    qDebug() << "Settings::editProfile Before creating RAS" << profile.getName();
    DeamonConnection::getInstance()->createRasPhonebookConnectionEntry(profile, false);
    qDebug() << "Settings::editProfile After creating RAS" << profile.getName();
    DeamonDatabase::getInstance()->writeProfile(profile);
    qDebug() << "Settings::editProfile After updating database" << profile.getName();

    emit reloadGeneral();
    emit reloadNetwork();

    return (result);
}

bool DeamonSetting::deleteProfile(const QString& profileName) {
    bool result = false;

    for (int index = 0; index < this->profiles.size(); index++) {

        if (profiles.at(index).getName() == profileName) {
            profiles.removeAt(index);
            result = true;
        }
    }

    return (result);
}

bool DeamonSetting::getGeneralLock() const {
    return (this->generalLock);
}

bool DeamonSetting::setGeneralLock( bool value) {
    this->generalLock = value;
    DeamonDatabase::getInstance()->writeSetting(GENERAL_LOCK_SETTING, value?TRUE_STRING:FALSE_STRING);
    return (true);
}

bool DeamonSetting::getInternetLock() const {
    return (this->internetLock);
}

bool DeamonSetting::setInternetLock( bool value) {
    this->internetLock = value;
    DeamonDatabase::getInstance()->writeSetting(INTERNET_LOCK_SETTING, value?TRUE_STRING:FALSE_STRING);
    return (true);
}

bool DeamonSetting::checkLock(const QString& lockCode) {
    return(this->lock == lockCode);
}

QString DeamonSetting::getLock() {
    return this->lock;
}

bool DeamonSetting::setLock(const QString& value) {
    this->lock = value;
    DeamonDatabase::getInstance()->writeSetting(LOCK_CODE_SETTING, value);
    return (true);
}

bool DeamonSetting::setNetworkMode(const QString& value) {
    this->networkMode = value;
    DeamonDatabase::getInstance()->writeSetting(NETWORK_MODE_SETTING, value);

    return (true);
}

QString DeamonSetting::getNetworkMode() {
    return (this->networkMode);
}

bool DeamonSetting::setProfileName(const QString& value) {
    this->profileName = value;
    DeamonDatabase::getInstance()->writeSetting(PROFILE_NAME_SETTING, value);

    return (true);
}

QString DeamonSetting::getProfileName() {
    return (this->profileName);
}

bool DeamonSetting::setDefaultProfile(bool value) {
    this->defaultProfile = value;
    DeamonDatabase::getInstance()->writeSetting(DEFAULT_PROFILE_SETTING, value?TRUE_STRING:FALSE_STRING);

    return (true);
}

bool DeamonSetting::getDefaultProfile() {
    return (this->defaultProfile);
}

bool DeamonSetting::setOpenDefault (bool value) {
    this->openDefault = value;
    DeamonDatabase::getInstance()->writeSetting(OPEN_DEFAULT_SETTING, value?TRUE_STRING:FALSE_STRING);

    return (true);
}

bool DeamonSetting::getOpenDefault () {
    return (this->openDefault);
}


QList<Profile> DeamonSetting::getProfiles() const {
    return (this->profiles);
}

bool DeamonSetting::setProfiles(QList<Profile> profiles) {
    this->profiles = profiles;
    return (true);
}

QStringList DeamonSetting::getAuthenticationTypes() {
    return (this->authenticationTypes);
}

bool DeamonSetting::setAuthenticationType(QStringList authenticationTypes) {
    bool result = false;

    this->authenticationTypes = authenticationTypes;

    return (result);
}

bool DeamonSetting::resetAllSettings() {
    bool result = false;

    this->setAutoTerminate (DeamonSetting::defaultAutoTerminate);
    this->setAutoExecute (DeamonSetting::defaultAutoExecute);
    this->setExecuteAccess (DeamonSetting::defaultExecuteAccess);
    this->setAutoDial (DeamonSetting::defaultAutoDial);

    this->setGeneralLock (DeamonSetting::defaultGeneralLock);
    this->setInternetLock (DeamonSetting::defaultInternetLock);
    this->setLock (DeamonSetting::defaultLock);

    this->setNetworkMode (DeamonSetting::defaultNetworkMode);
    this->setProfileName (DeamonSetting::defaultProfileName);
    this->setDefaultProfile (DeamonSetting::defaultDefaultProfile);
    this->setCurrentProfile (DeamonSetting::defaultProfileName);
    this->currentProfile.setDynamic (true);

    this->setOpenDefault (DeamonSetting::defaultOpenDefault);

    emit reloadActivation();
    emit reloadGeneral();
    emit reloadInformation();
    emit reloadIpAddress();
    emit reloadLock();
    emit reloadNetwork();
    emit reloadWebSection();

    return (result);
}

// System Information
QString DeamonSetting::getOperatingSystemName() {
    return (this->operatingSystemName);
}

QString DeamonSetting::getOperatingSystemVersion() {
    return (this->operatingSystemVersion);
}

QString DeamonSetting::getProcessor() {
    return (this->processor);
}

QString DeamonSetting::getPhysicalMemory() {
    return (this->physicalMemory);
}

QString DeamonSetting::getVirtualMemory() {
    return (this->virtualMemory);
}

QString DeamonSetting::getManufacturer() {
    return (this->manufacturer);
}

bool DeamonSetting::readSettingsFromDatabase(){
    bool result = false;

    if ( false == DeamonDatabase::getInstance()->checkSettings()) {
        this->resetAllSettings();
        this->writeSettingsToDatabase();
    } else {

        this->autoTerminate = this->stringToBool(DeamonDatabase::getInstance()->readSetting(AUTO_TERMINATE_SETTING));
        this->autoExecute = this->stringToBool(DeamonDatabase::getInstance()->readSetting(AUTO_EXECUTE_SETTING));
        this->executeAccess = this->stringToBool(DeamonDatabase::getInstance()->readSetting(EXECUTE_ACCESS_SETTING));
        this->autoDial = this->stringToBool(DeamonDatabase::getInstance()->readSetting(AUTO_DIAL_SETTING));

        this->generalLock = this->stringToBool(DeamonDatabase::getInstance()->readSetting(GENERAL_LOCK_SETTING));
        this->internetLock = this->stringToBool(DeamonDatabase::getInstance()->readSetting(INTERNET_LOCK_SETTING));
        this->lock = DeamonDatabase::getInstance()->readSetting(LOCK_CODE_SETTING);

        this->networkMode = DeamonDatabase::getInstance()->readSetting(NETWORK_MODE_SETTING);
        this->profileName = DeamonDatabase::getInstance()->readSetting(PROFILE_NAME_SETTING);
        this->defaultProfile = this->stringToBool(DeamonDatabase::getInstance()->readSetting(DEFAULT_PROFILE_SETTING));

        this->openDefault = this->stringToBool(DeamonDatabase::getInstance()->readSetting(OPEN_DEFAULT_SETTING));
    }

    if ( false == DeamonDatabase::getInstance()->checkProfiles()) {
        DeamonDatabase::getInstance()->writeProfile(DeamonSetting::defaultCurrentProfile);
        this->currentProfile = DeamonSetting::defaultCurrentProfile;
        this->profiles.append(this->currentProfile);
    } else {
        this->currentProfile = DeamonDatabase::getInstance()->getDefaultProfile();
        this->profiles = DeamonDatabase::getInstance()->readProfiles();
    }

    return result;
}

bool DeamonSetting::writeSettingsToDatabase(){
    bool result = false;

    DeamonDatabase::getInstance()->writeSetting(AUTO_TERMINATE_SETTING, this->boolToString(this->autoTerminate));
    DeamonDatabase::getInstance()->writeSetting(AUTO_EXECUTE_SETTING, this->boolToString(this->autoExecute));
    DeamonDatabase::getInstance()->writeSetting(EXECUTE_ACCESS_SETTING, this->boolToString(this->executeAccess));
    DeamonDatabase::getInstance()->writeSetting(AUTO_DIAL_SETTING, this->boolToString(this->autoDial));

    DeamonDatabase::getInstance()->writeSetting(GENERAL_LOCK_SETTING, this->boolToString(this->generalLock));
    DeamonDatabase::getInstance()->writeSetting(INTERNET_LOCK_SETTING, this->boolToString(this->internetLock));
    DeamonDatabase::getInstance()->writeSetting(LOCK_CODE_SETTING, this->lock);

    DeamonDatabase::getInstance()->writeSetting(NETWORK_MODE_SETTING, this->networkMode);
    DeamonDatabase::getInstance()->writeSetting(PROFILE_NAME_SETTING, this->profileName);
    DeamonDatabase::getInstance()->writeSetting(DEFAULT_PROFILE_SETTING, this->profileName);

    DeamonDatabase::getInstance()->writeSetting(OPEN_DEFAULT_SETTING, this->boolToString(this->openDefault));

    return (result);
}

bool DeamonSetting::stringToBool (const QString& value) {
    if (TRUE_STRING == value) {
        return true;
    } else {
        return false;
    }
}

QString DeamonSetting::boolToString (bool value) {
    return value?TRUE_STRING:FALSE_STRING;
}

