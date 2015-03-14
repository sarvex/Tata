#ifndef DEAMON_INTERFACE
#define DEAMON_INTERFACE

#include "SerialPort.h"
#include "Defines.h"

#include <QMutex>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QWaitCondition>

class DeamonInterface : public QThread {
    Q_OBJECT
public:
    static DeamonInterface* getInstance();
    ~DeamonInterface ();

    bool writeToAtPort(const QString& value);

    bool writeAtInformation();
    bool writeAtDiagnostic();

    bool stop();

    static const QString at;
    static const QString dial;
    static const QString toneDial;

    static const QString echoOff;
    static const QString echoOn;

    static const QString enableFlashMessage;
    static const QString enableMessage;
    static const QString flashMessageResponse;
    static const QString messageResponse;

    static const QString programmingSuccessful;
    static const QString programmingUnsuccessful;

    static const QString signalStrength;
    static const QString signalStrengthResponse;

    static const QString systemInformation;
    static const QString systemInformationResponse;

    static const QString modemVersion;
    static const QString modemVersionResponse;
    static const QString modemVersionResponseCompilationDate;
    static const QString modemVersionResponseSoftwareVersion;

    static const QString hardwareVersion;
    static const QString hardwareVersionResponse;

    static const QString sid;
    static const QString sidResponse;

    static const QString nid;
    static const QString nidResponse;

    static const QString sectorId;
    static const QString sectorIdResponse;

    static const QString hdrc;
    static const QString hdrcResponse;

    static const QString cdmaEcio;
    static const QString cdmaEcioResponse;

    static const QString hdrEcio;
    static const QString hdrEcioResponse;

    static const QString meid;
    static const QString meidResponse;

    static const QString cdmaRssi;
    static const QString cdmaRssiResponse;

    static const QString cdmaPnOffset;
    static const QString cdmaPnOffsetResponse;

    static const QString walshCode;
    static const QString walshCodeResponse;

    static const QString channelNumber;
    static const QString channelNumberResponse;

    static const QString bandClass;
    static const QString bandClassResponse;

    static const QString txPower;
    static const QString txPowerResponse;

    static const QString rxPower;
    static const QString rxPowerResponse;

    static const QString bsPrevious;
    static const QString bsPreviousResponse;

    static const QString msPrevious;
    static const QString msPreviousResponse;

    static const QString previousInUse;
    static const QString previousInUseResponse;

    static const QString packetZoneId;
    static const QString packetZoneIdResponse;

    static const QString lastActiveCallState;
    static const QString lastActiveCallStateResponse;

    static const QString hdrRssi;
    static const QString hdrRssiResponse;

    static const QString per;
    static const QString perResponse;

    static const QString atState;
    static const QString atStateResponse;

    static const QString dormantState;
    static const QString dormantResponse;

    static const QString activeStatePnOffset;
    static const QString activeStatePnOffsetResponse;

    static const QString neighborSetPnOffset;
    static const QString neighborSetPnOffsetResponse;

    static const QString neighborSetEcio;
    static const QString neighborSetEcioResponse;

    static const QString esn;
    static const QString esnResponse;

    static const QString prl;
    static const QString prlResponse;

    static const QString defaultMin;
    static const QString defaultMinResponse;

    static const QString setModeZero;
    static const QString setModeOne;
    static const QString setModeTwo;
    static const QString setModeThree;

signals:
    bool modemPlugged();
    bool modemUnplugged();
    void activation(bool status);

    bool signalStrengthUpdate(int value);
    bool serviceStatusUpdate(int value);
    bool serviceDomainUpdate(int value);
    bool roamingStatusUpdate(int value);
    bool systemModeUpdate(int value);
    bool simStatusUpdate(int value);

    bool prlUpdate(const QString& value);
    bool meidUpdate(const QString& value);
    bool hardwareVersionUpdate(const QString& value);
    bool compileDateUpdate(const QString& value);
    bool esnUpdate(const QString& value);
    bool softwareVersionUpdate(const QString& value);
    bool cdmaEcioUpdate(const QString& value);
    bool hdrEcioUpdate(const QString& value);
    bool hdrcUpdate(const QString& value);
    bool sidUpdate(const QString& value);
    bool nidUpdate(const QString& value);
    bool sectorIdUpdate(const QString& value);

    bool cdmaRssiUpdate(const QString& value);
    bool pnOffsetUpdate(const QString& value);
    bool walshCodeUpdate(const QString& value);
    bool channelNumberUpdate(const QString& value);
    bool bandClassUpdate(const QString& value);
    bool txPowerUpdate(const QString& value);
    bool rxPowerUpdate(const QString& value);
    bool bsPreviousUpdate(const QString& value);
    bool msPreviousUpdate(const QString& value);
    bool previousInUseUpdate(const QString& value);
    bool packetZoneIdUpdate(const QString& value);
    bool lastActiveCallStateUpdate(const QString& value);
    bool hdrRssiUpdate(const QString& value);
    bool perUpdate(const QString& value);
    bool atStateUpdate(const QString& value);
    bool dormantStateUpdate(const QString& value);
    bool activeStatePnOffsetUpdate(const QString& value);
    bool neighborSetPnOffsetUpdate(const QString& value);
    bool neighborSetEcioUpdate(const QString& value);

    bool flashMessageUpdate(const QString& value);
    bool defaultMinUpdate();

public slots:
    bool onSystemUpdateTimer();

protected:
    void run();

private:
    explicit DeamonInterface(QObject *parent = 0);
    static DeamonInterface* singleton;

    bool checkModem ();
    bool openAtPort ();

    bool writeToAtPort();
    bool readFromAtPort();
    bool parseResponse(QString& value);

    volatile bool running;

    SerialPort * atPort;
    SerialPort * modemPort;

    QMutex * mutex;

    QQueue<QString> atCommandQueue;

    QString atPortName;
    QString modemPortName;

    QTimer * systemInformationTimer;

    bool modem;
    bool port;

    static const QString end;
};

#endif // DEAMON_INTERFACE
