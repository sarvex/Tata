#include "DeamonDatabase.h"

#include "DeamonConnection.h"
#include "Defines.h"
#include "DeamonSetting.h"

#include <QDebug>
#include <QVariant>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

DeamonDatabase* DeamonDatabase::singleton = NULL;

DeamonDatabase* DeamonDatabase::getInstance () {
    if (NULL == singleton) {
        singleton = new DeamonDatabase();
    }
    return (singleton);
}

DeamonDatabase::DeamonDatabase ( QObject * parent) : QObject(parent) {
    sqlDatabase = QSqlDatabase::addDatabase(DATABASE_TYPE);

    sqlDatabase.setHostName(DATABASE_HOST);

    sqlDatabase.setDatabaseName(DATABASE_NAME);
    sqlDatabase.setUserName(DATABASE_USER);
    sqlDatabase.setPassword(DATABASE_PASSWORD);

    if (false == sqlDatabase.open()) {
        qDebug() <<" Unable to open sqlDatabase " << sqlDatabase.lastError();
    }

    QSqlQuery sqlQuery (sqlDatabase);

    if (false == (sqlQuery.exec(CREATE_PROFILE_TABLE))) {
        qDebug () << "Profile table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_PREFERENCE))) {
        qDebug () << "Preference table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_SENTBOX))) {
        qDebug () << "Sentbox table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_RECYCLE))) {
        qDebug () << "Recycle table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_DRAFTS))) {
        qDebug () << "Drafts table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_PHONEBOOK))) {
        qDebug () << "Phonebook table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_PHONEBOOK_RECYCLE))) {
        qDebug () << "Recycle Phonebook table not created" << sqlQuery.lastError();
    }

    sqlQuery.clear();
    if (false == (sqlQuery.exec(CREATE_TABLE_CONNECTTION_LOGS))) {
        qDebug () << "Connection Logs table not created" << sqlQuery.lastError();
    }
}

DeamonDatabase::~DeamonDatabase () {

}

bool DeamonDatabase::closeDatabase() {
    sqlDatabase.commit();
    sqlDatabase.close();
    sqlDatabase.removeDatabase (DATABASE_NAME);

    return (true);
}

bool DeamonDatabase::checkSettings(){

    QSqlQuery sqlQuery (this->sqlDatabase);

    sqlQuery.exec (SELECT_PREFERENCES);
    bool result = sqlQuery.first();
    return result;
}

QString DeamonDatabase::readSetting (const QString& setting) {
    QSqlQuery sqlQuery(this->sqlDatabase);

    sqlQuery.prepare (READ_PREFERENCE);
    sqlQuery.bindValue (SETTING, setting.toInt());

    if (false == sqlQuery.exec()) {
        return "";
    } else  {
        sqlQuery.first();
        return (sqlQuery.value(0).toString());
    }
}

bool DeamonDatabase::writeSetting (const QString& setting, const QString& value) {
    bool result = false;

    QSqlQuery sqlQuery(this->sqlDatabase);

    sqlQuery.prepare(READ_PREFERENCE);
    sqlQuery.bindValue(SETTING, setting.toInt());
    sqlQuery.exec();

    bool existing = sqlQuery.first();
    sqlQuery.clear();

    if ( false == existing ) {
        sqlQuery.prepare(INSERT_PREFERENCE);
    } else {
        sqlQuery.prepare(WRITE_PREFERENCE);
    }

    sqlQuery.bindValue (SETTING, setting.toInt());
    sqlQuery.bindValue (VALUE, value);

    result = sqlQuery.exec ();
    return (result);
}

bool DeamonDatabase::checkProfiles(){
    QSqlQuery sqlQuery (this->sqlDatabase);

    sqlQuery.exec (SELECT_PROFILES);

    return sqlQuery.first();
}


Profile DeamonDatabase::getDefaultProfile() const {
    QSqlQuery sqlQuery(this->sqlDatabase);

    if ( false == sqlQuery.exec(READ_DEFAULT_PROFILE) ) {
        return Profile ();
    } else {
        sqlQuery.first();

        return Profile (sqlQuery.value(0).toString(), sqlQuery.value(1).toString(), sqlQuery.value(2).toString(), sqlQuery.value(3).toString(), sqlQuery.value(4).toBool(), static_cast<AuthenticationType>(sqlQuery.value(5).toInt()), sqlQuery.value(6).toBool(), sqlQuery.value(7).toString(), sqlQuery.value(8).toString(), sqlQuery.value(9).toString(), sqlQuery.value(10).toString(), sqlQuery.value(11).toString());
    }

}

QStringList DeamonDatabase::getProfileNames () const {
    QStringList result;
    QSqlQuery sqlQuery(this->sqlDatabase);

    if (true == sqlQuery.exec (SELECT_PROFILE_NAMES)) {
        while (sqlQuery.next()) {
            result.append( sqlQuery.value(0).toString() );
        }
    } else {
        qDebug() << "Unable to get profile names";
    }

    return (result);
}

QList<Profile> DeamonDatabase::readProfiles () {
    QList<Profile> result;
    QSqlQuery sqlQuery (this->sqlDatabase);

    sqlQuery.exec(SELECT_PROFILES);

    while (true == sqlQuery.next()) {
        Profile profile( sqlQuery.value(0).toString(), sqlQuery.value(1).toString(), sqlQuery.value(2).toString(), sqlQuery.value(3).toString(), sqlQuery.value(4).toBool(), static_cast<AuthenticationType>(sqlQuery.value(5).toInt()), sqlQuery.value(6).toBool(), sqlQuery.value(7).toString(), sqlQuery.value(8).toString(), sqlQuery.value(9).toString(), sqlQuery.value(10).toString(), sqlQuery.value(11).toString());

        result.append(profile);
    }


    return (result);
}

bool DeamonDatabase::writeProfiles(QList<Profile> profiles){
    foreach (Profile profile, profiles) {
        this->writeProfile(profile);
    }

    return true;
}

Profile DeamonDatabase::readProfile(const QString& name) {
    QSqlQuery sqlQuery(this->sqlDatabase);

    sqlQuery.prepare(READ_PROFILE);
    sqlQuery.bindValue(NAME, name);

    sqlQuery.exec();
    sqlQuery.first();

    qDebug() << sqlQuery.value(0).toString() << sqlQuery.value(1).toString() << sqlQuery.value(2).toString() << sqlQuery.value(3).toString() << sqlQuery.value(4).toBool() << static_cast<AuthenticationType>(sqlQuery.value(5).toInt()) << sqlQuery.value(6).toBool() << sqlQuery.value(7).toString() << sqlQuery.value(8).toString() << sqlQuery.value(9).toString() << sqlQuery.value(10).toString() << sqlQuery.value(11).toString();

    Profile profile(sqlQuery.value(0).toString(), sqlQuery.value(1).toString(), sqlQuery.value(2).toString(), sqlQuery.value(3).toString(), sqlQuery.value(4).toBool(), static_cast<AuthenticationType>(sqlQuery.value(5).toInt()), sqlQuery.value(6).toBool(), sqlQuery.value(7).toString(), sqlQuery.value(8).toString(), sqlQuery.value(9).toString(), sqlQuery.value(10).toString(), sqlQuery.value(11).toString());
    return (profile);

}

bool DeamonDatabase::writeProfile(const Profile& profile) {
    QSqlQuery sqlQuery(this->sqlDatabase);

    sqlQuery.prepare(READ_PROFILE);
    sqlQuery.bindValue(NAME, profile.getName());

    sqlQuery.exec();
    bool existing = sqlQuery.first();
    sqlQuery.clear();
    if ( false == existing ) {
        sqlQuery.prepare(INSERT_PROFILE);
    } else {
        sqlQuery.prepare(WRITE_PROFILE);
    }

    sqlQuery.bindValue(NAME, profile.getName());
    sqlQuery.bindValue(USERNAME, profile.getUserName());
    sqlQuery.bindValue(PASSWORD, profile.getPassword());
    sqlQuery.bindValue(NUMBER, profile.getNumber());
    sqlQuery.bindValue(CONNECTION, profile.getConnectionType()?1:0);
    sqlQuery.bindValue(AUTHENTICATION, profile.getAuthenticationType());

    sqlQuery.bindValue(DYNAMIC, profile.getDynamic()?1:0);
    sqlQuery.bindValue(IP, profile.getIpAddress());
    sqlQuery.bindValue(DNS, profile.getDnsAddress());
    sqlQuery.bindValue(DNS_ALTERNATE, profile.getDnsAlternateAddress());
    sqlQuery.bindValue(WINS, profile.getWinsAddress());
    sqlQuery.bindValue(WINS_ALTERNATE, profile.getWinsAlternateAddress());


    return (sqlQuery.exec());
}

bool DeamonDatabase::deleteProfile(const QString& profileName) {
    QSqlQuery sqlQuery(this->sqlDatabase);

    sqlQuery.prepare(DELETE_PROFILE);
    sqlQuery.bindValue(NAME, profileName);

    return (sqlQuery.exec());
}
