#ifndef PROFILE
#define PROFILE

#include <QString>
#include "Defines.h"

class Profile {
public:

	Profile(const QString& name, const QString& userName, const QString& password, const QString& number, bool defaultConnection, AuthenticationType authenticationType);
	Profile(const QString& name, const QString& userName, const QString& password, const QString& number, bool defaultConnection, AuthenticationType authenticationType, bool dynamic, const QString& ipAddress, const QString& dnsAddress, const QString& dnsAlternateAddress, const QString& winsAddress, const QString& winsAlternateAddress);

	Profile();
	~Profile();


	QString getName() const;
	bool setName(const QString& name);

	QString getUserName() const;
	bool setUserName(const QString& name);

	QString getPassword() const;
	bool setPassword(const QString& password);

	QString getNumber() const;
	bool setNumber(const QString& number);

	bool getConnectionType() const;
	bool setConnectionType(bool);

	AuthenticationType getAuthenticationType() const;
	bool setAuthenticationType(AuthenticationType);

	bool getDynamic() const;
	bool setDynamic(bool dynamic);

	QString getIpAddress() const;
	bool setIpAddress(const QString& ipAddress);

	QString getDnsAddress() const;
	bool setDnsAddress(const QString& dnsAddress);

	QString getDnsAlternateAddress() const;
	bool setDnsAlternateAddress(const QString& dnsAlternateAddress);

	QString getWinsAddress() const;
	bool setWinsAddress(const QString& winsAddress);

	QString getWinsAlternateAddress() const;
	bool setWinsAlternateAddress(const QString& winsAlternateAddress);

private:
	QString name;
	QString userName;
	QString password;
	QString number;
	bool connectionType;
	AuthenticationType authenticationType;

	bool dynamic;
	QString ipAddress;
	QString dnsAddress;
	QString dnsAlternateAddress;
	QString winsAddress;
	QString winsAlternateAddress;
};

#endif // PROFILE
