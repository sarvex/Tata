#ifndef DEAMON_SETTINGS
#define DEAMON_SETTINGS

#include "Profile.h"

#include <QStringList>

class DeamonSetting : public QObject{
	Q_OBJECT

public:
	static DeamonSetting* getInstance();
	~DeamonSetting ();

	bool readSettingsFromDatabase();
	bool writeSettingsToDatabase();

	QStringList getProfileNames() const;

	bool getAutoTerminate () const;
	bool setAutoTerminate (bool value);

	bool getAutoExecute () const;
	bool setAutoExecute (bool value);

	bool getExecuteAccess () const;
	bool setExecuteAccess (bool value);

	bool getAutoDial () const;
	bool setAutoDial (bool value);

	Profile getCurrentProfile () const;
	bool setCurrentProfile ( const QString& name );

	bool getGeneralLock() const;
	bool setGeneralLock(bool value);

	bool getInternetLock() const;
	bool setInternetLock(bool value);

	bool checkLock(const QString&);
	QString getLock();
	bool setLock(const QString&);

	bool setNetworkMode(const QString& value);
	QString getNetworkMode();

	bool setProfileName(const QString& value);
	QString getProfileName();

	bool setDefaultProfile(bool value);
	bool getDefaultProfile();

	bool setOpenDefault (bool value);
	bool getOpenDefault ();

	QList<Profile> getProfiles() const;
	bool setProfiles(QList<Profile>);

	bool addProfile(const Profile& profile);
	bool editProfile(const Profile& profile);
	bool deleteProfile(const QString& profileName);

	QStringList getAuthenticationTypes();
	bool setAuthenticationType(QStringList authenticationTypes);

	bool resetAllSettings();

	// System Information
	QString getOperatingSystemName();
	QString getOperatingSystemVersion();
	QString getProcessor();
	QString getPhysicalMemory();
	QString getVirtualMemory();
	QString getManufacturer();

signals:
	bool reloadActivation();
	bool reloadGeneral();
	bool reloadInformation();
	bool reloadIpAddress();
	bool reloadLock();
	bool reloadNetwork();
	bool reloadWebSection();

public slots:


protected:

private:
	DeamonSetting(QObject *parent = 0);
	bool ReadSystemInformation();

	bool stringToBool(const QString& string);
	QString boolToString(bool value);

	static DeamonSetting* singleton;

	QList<Profile> profiles;
	QStringList authenticationTypes;

	Profile currentProfile;

	bool autoTerminate;
	bool autoExecute;
	bool executeAccess;
	bool autoDial;

	bool generalLock;
	bool internetLock;
	QString lock;

	QString networkMode;
	QString profileName;
	bool defaultProfile;
	bool openDefault;

	const static bool defaultAutoTerminate;
	const static bool defaultAutoExecute;
	const static bool defaultExecuteAccess;
	const static bool defaultAutoDial;

	const static bool defaultGeneralLock;
	const static bool defaultInternetLock;
	const static QString defaultLock;

	const static QString defaultNetworkMode;
	const static QString defaultProfileName;
	const static bool defaultDefaultProfile;
	const static Profile defaultCurrentProfile;

	const static bool defaultOpenDefault;

	QString operatingSystemName;
	QString operatingSystemVersion;
	QString processor;
	QString physicalMemory;
	QString virtualMemory;
	QString manufacturer;
	QString manufacturerName;
	QString manufacturerModel;
	QString manufacturerType;
};

#endif // DEAMON_SETTINGS
