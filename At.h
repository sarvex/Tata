#ifndef AT_H
#define AT_H

#include <QString>

class At {
public:
    At();

    static const QString end;
    static const QString dial;
    static const QString toneDial;
    static const QString signalStrength;
    static const QString systemInformation;

    static const QString sidNid;
    static const QString sectorId;
    static const QString drc;
    static const QString cdmaEcio;
    static const QString hdrEcio;

    static const QString compileDate;
    static const QString esn;
    static const QString pEsn;
    static const QString prl;
    static const QString softwareVersion;
    static const QString hardwareVersion;

    static const QString setModeZero;
    static const QString setModeOne;
    static const QString setModeTwo;
    static const QString setModeThree;
};

#endif // AT_H
