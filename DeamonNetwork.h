#ifndef DEAMONNETWORK_H
#define DEAMONNETWORK_H

#include <QObject>

#include <QStringList>
#include <QTimer>

class DeamonNetwork : public QObject {
    Q_OBJECT
public:
    static DeamonNetwork* getInstance();

    bool initialize();
    bool activate(QString cardType, QString number);

    bool setNetworkMode(QString networkModeName);

    bool readSidNid();
    bool readSectorId();
    bool readDrc();
    bool readCdmaEcio();
    bool readHdrEcio();

    bool readModemInformation();

    bool readPrl();
    bool readEsn();
    bool readHardwareVersion();
    bool readCompileDate();
    bool readPEsn();
    bool readSoftwareVersion();

    QStringList getNetworkModes() const;

signals:
    bool signalStrengthUpdate(int level);
    bool systemInformationUpdate ();
    bool activationComplete (bool result);

    bool sidNidUpdate(QString value);
    bool sectorIdUpdate(QString value);
    bool drcUpdate(QString value);
    bool cdmaEcioUpdate(QString value);
    bool hdrEcioUpdate(QString value);

    bool prlUpdate(QString value);
    bool esnUpdate(QString value);
    bool pEsnUpdate(QString value);
    bool hardwareVersionUpdate(QString value);
    bool softwareVersionUpdate(QString value);
    bool compileDateUpdate(QString value);

public slots:
    bool onSignalStrengthTimer();
    bool onSignalStrengthReceived();

    bool onSystemInformationTimer();
    bool onSystemInformationReceived();

    bool onDial();
    bool onLanguage();
    bool onCardType();
    bool onResponse();

    bool onReadSidNid();
    bool onReadSectorId();
    bool onReadDrc();
    bool onReadCdmaEcio();
    bool onReadHdrEcio();

    bool onReadPrl();
    bool onReadEsn();
    bool onReadHardwareVersion();
    bool onReadCompileDate();
    bool onReadPEsn();
    bool onReadSoftwareVersion();

protected:

private:
    explicit DeamonNetwork(QObject *parent = 0);
    static DeamonNetwork* singleton;

    QTimer * signalStrengthTimer;
    QTimer * systemInformationTimer;

    QStringList networkModes;

    QString cardType;
    QString number;
};

#endif // DEAMONNETWORK_H
