#ifndef DEAMON_DATABASE
#define DEAMON_DATABASE

#include <QObject>

#include "Profile.h"

#include <QtSql/QSqlDatabase>

class DeamonDatabase : public QObject {
	Q_OBJECT
public:
	static DeamonDatabase* getInstance();
	~DeamonDatabase();

	bool initilize();
	bool closeDatabase();

	bool checkSettings();
	QString readSetting (const QString& setting);
	bool writeSetting (const QString& setting, const QString& value);

	bool checkProfiles();
	Profile getDefaultProfile()const;
	QStringList getProfileNames () const;
	QList<Profile> readProfiles();
	bool writeProfiles(QList<Profile> profiles);

	Profile readProfile(const QString&);
	bool writeProfile(const Profile&);
	bool deleteProfile(const QString& profileName);


	signals:

public slots:

protected:

private:
	explicit DeamonDatabase(QObject *parent = 0);
	static DeamonDatabase* singleton;

	QSqlDatabase sqlDatabase;
};

#endif // DEAMON_DATABASE
