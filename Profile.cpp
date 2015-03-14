#include "Profile.h"

Profile::Profile() : connectionType(false), authenticationType(AUTO), dynamic(PROFILE_DYNAMIC),  ipAddress(PROFILE_IP), dnsAddress(PROFILE_DNS), dnsAlternateAddress(PROFILE_DNS_ALTERNATE), winsAddress(PROFILE_WINS), winsAlternateAddress(PROFILE_WINS_ALTERNATE) {

}

Profile::Profile(const QString& name, const QString& userName, const QString& password, const QString& number, bool connectionType, AuthenticationType authenticationType):
        name(name), userName(userName), password(password), number(number), connectionType(connectionType), authenticationType(authenticationType) {

}


Profile::Profile(const QString& name, const QString& userName, const QString& password, const QString& number, bool connectionType, AuthenticationType authenticationType, bool dynamic, const QString& ipAddress, const QString& dnsAddress, const QString& dnsAlternateAddress, const QString& winsAddress, const QString& winsAlternateAddress):
name(name), userName(userName), password(password), number(number), connectionType(connectionType), authenticationType(authenticationType), dynamic(dynamic),  ipAddress(ipAddress), dnsAddress(dnsAddress), dnsAlternateAddress(dnsAlternateAddress), winsAddress(winsAddress), winsAlternateAddress(winsAlternateAddress) {

}

Profile::~Profile () {

}

QString Profile::getName() const {
    return (this->name);
}

bool Profile::setName(const QString& name) {
    this->name = name;
    return (true);
}

QString Profile::getUserName() const {
    return (this->userName);
}

bool Profile::setUserName (const QString& userName) {
    this->userName = userName;
    return (true);
}

QString Profile::getPassword() const {
    return (this->password);
}

bool Profile::setPassword(const QString& password) {
    this->password = password;
    return (true);
}

QString Profile::getNumber() const {
    return (this->number);
}

bool Profile::setNumber(const QString& number) {
    this->number = number;
    return (true);
}

bool Profile::getConnectionType() const {
    return (this->connectionType);
}

bool Profile::setConnectionType(bool connectionType) {
    this->connectionType = connectionType;
    return (true);
}

AuthenticationType Profile::getAuthenticationType() const {
    return (this->authenticationType);
}

bool Profile::setAuthenticationType(AuthenticationType authenticationType) {
    this->authenticationType = authenticationType;
    return (true);
}

bool Profile::getDynamic() const {
    return this->dynamic;
}
bool Profile::setDynamic(bool dynamic) {
    this->dynamic = dynamic;

    return true;
}

QString Profile::getIpAddress() const {
    return this->ipAddress;
}

bool Profile::setIpAddress(const QString& ipAddress){
    this->ipAddress = ipAddress;

    return true;
}

QString Profile::getDnsAddress() const {
    return this->dnsAddress;
}
bool Profile::setDnsAddress(const QString& dnsAddress){
    this->dnsAddress = dnsAddress;

    return true;
}

QString Profile::getDnsAlternateAddress() const {
    return this->dnsAlternateAddress;
}
bool Profile::setDnsAlternateAddress(const QString& dnsAlternateAddress){
    this->dnsAlternateAddress = dnsAlternateAddress;

    return true;
}

QString Profile::getWinsAddress() const {
    return this->winsAddress;
}
bool Profile::setWinsAddress(const QString& winsAddress){
    this->winsAddress = winsAddress;

    return true;
}

QString Profile::getWinsAlternateAddress() const {
    return this->winsAlternateAddress;
}
bool Profile::setWinsAlternateAddress(const QString& winsAlternateAddress){
    this->winsAlternateAddress = winsAlternateAddress;

    return true;
}
