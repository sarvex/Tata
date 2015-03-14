#ifndef DEAMON_CONNECTION
#define DEAMON_CONNECTION

#include "Profile.h"

#include <QObject>
#include <QTimer>

#include <windows.h>
#include <ras.h>
#include <raserror.h>


class DeamonConnection : public QObject {
	Q_OBJECT
public:
	static DeamonConnection* getInstance ();
	~DeamonConnection();

	bool connectDataCall();
	bool disconnectDataCall();

	bool createRasPhonebookConnectionEntry(const Profile& profile, bool newEntry);
	bool deleteRasPhonebookConnectionEntry(const QString& connectionName);
	bool readRasPhonebookConnectionEntry(const QString& connectionName);

signals:
	bool connected();
	bool disconnected();
	bool rasError(long errorNumber, const QString& errorString);

	bool updateIpAddress(bool isDynamic, const QString& ipAddress, const QString& dnsAddress, const QString& dnsAlternateAddress, const QString& winsAddress, const QString& winsAlternateAddress);

public slots:

protected:

private:
	explicit DeamonConnection(QObject *parent = 0);
	static DeamonConnection* singleton;

	RASIPADDR convertStringToIpAddress (const QString& value);
	QString convertIpAddressToString (RASIPADDR value);

	friend void  CALLBACK RasDialFunc(UINT unMsg, RASCONNSTATE rasconnstate, DWORD dwError);
};

void CALLBACK RasDialFunc(UINT unMsg, RASCONNSTATE rasconnstate, DWORD dwError);

#endif // DEAMON_CONNECTION
