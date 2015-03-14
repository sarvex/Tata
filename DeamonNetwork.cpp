#include "DeamonNetwork.h"


#include "At.h"
#include "DeamonDatabase.h"
#include "DeamonPort.h"
#include "Settings.h"
#include "SystemInformation.h"

#include <QDebug>
#include <QMutex>
#include <QWaitCondition>

DeamonNetwork* DeamonNetwork::singleton = NULL;

DeamonNetwork* DeamonNetwork::getInstance () {
    if (NULL == singleton) {
        singleton = new DeamonNetwork();
    }
    return (singleton);
}

DeamonNetwork::DeamonNetwork(QObject *parent) : QObject(parent) {
}

QStringList DeamonNetwork::getNetworkModes () const {
    return (this->networkModes);
}

bool DeamonNetwork::initialize() {
    DeamonPort::getInstance()->initialize();

    this->signalStrengthTimer = new QTimer(this);
    connect(signalStrengthTimer, SIGNAL(timeout()), this, SLOT(onSignalStrengthTimer()));
    this->signalStrengthTimer->start(SIGNAL_STRENGTH_TIMEOUT);

    this->systemInformationTimer = new QTimer(this);
    connect(systemInformationTimer, SIGNAL(timeout()), this, SLOT(onSystemInformationTimer()));
    this->systemInformationTimer->start(SYSTEM_INFORMATION_TIMEOUT);

    return (true);
}

bool DeamonNetwork::onSignalStrengthTimer() {
    if (true == DeamonPort::getInstance()->writeToAtPort(At::signalStrength + At::end)) {
        QTimer::singleShot(SIGNAL_STRENTH_READ_TIMEOUT, this, SLOT(onSignalStrengthReceived()));
    }

    return (true);
}

bool DeamonNetwork::onSignalStrengthReceived() {
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::signalStrength))) {
        int result = data.remove(At::signalStrength).remove(OK_STRING).simplified().split(',', QString::SkipEmptyParts).at(0).toInt();
        emit signalStrengthUpdate(result);
    }

    return (true);
}

bool DeamonNetwork::onSystemInformationTimer() {
    if (true == DeamonPort::getInstance()->writeToAtPort(At::systemInformation + At::end)) {
        QTimer::singleShot(SYSTEM_INFORMATION_READ_TIMEOUT, this, SLOT(onSystemInformationReceived()));
    }

    return (true);
}

bool DeamonNetwork::onSystemInformationReceived() {
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if ((0 < data.length()) && (data.contains(At::systemInformation))) {
        SystemInformation systemInformation;

        int first = data.remove(At::systemInformation).remove(OK_STRING).simplified().split(':', QString::SkipEmptyParts).at(1).split(',', QString::SkipEmptyParts).at(0).toInt();
        int second = data.remove(At::systemInformation).remove(OK_STRING).simplified().split(':', QString::SkipEmptyParts).at(1).split(',', QString::SkipEmptyParts).at(1).toInt();
        int third = data.remove(At::systemInformation).remove(OK_STRING).simplified().split(':', QString::SkipEmptyParts).at(1).split(',', QString::SkipEmptyParts).at(2).toInt();
        int fourth = data.remove(At::systemInformation).remove(OK_STRING).simplified().split(':', QString::SkipEmptyParts).at(1).split(',', QString::SkipEmptyParts).at(3).toInt();
        int fifth = data.remove(At::systemInformation).remove(OK_STRING).simplified().split(':', QString::SkipEmptyParts).at(1).split(',', QString::SkipEmptyParts).at(4).toInt();


        Q_UNUSED(first);Q_UNUSED(second);Q_UNUSED(third);Q_UNUSED(fourth);Q_UNUSED(fifth);
    }

    return (true);
}

bool DeamonNetwork::activate(QString cardType, QString number) {
    this->cardType = cardType;
    this->number = number;
    DeamonPort::getInstance()->writeToAtPort( At::dial + ACTIVATION_NUMBER + At::end);
    QTimer::singleShot(DIAL_WAIT_TIMEOUT, this, SLOT(onDial()));

    return (true);
}

bool DeamonNetwork::onDial() {
    DeamonPort::getInstance()->writeToAtPort( At::toneDial + LANGUAGE + At::end);
    QTimer::singleShot(LANGUAGE_TIMEOUT, this, SLOT(onLanguage()));

    return (true);
}

bool DeamonNetwork::onLanguage() {
    DeamonPort::getInstance()->writeToAtPort( At::toneDial + this->cardType + At::end);
    QTimer::singleShot(CARD_TYPE_TIMEOUT, this, SLOT(onCardType()));

    return (true);
}

bool DeamonNetwork::onCardType() {
    DeamonPort::getInstance()->writeToAtPort( At::toneDial + this->number + At::end);
    QTimer::singleShot(RESPONSE_TIMEOUT, this, SLOT(onResponse()));

    return (true);
}

bool DeamonNetwork::onResponse() {
    bool result = false;

    QString response = DeamonPort::getInstance()->readFromAtPort();

    emit activationComplete(result);
    return (result);
}

bool DeamonNetwork::readSidNid() {
    DeamonPort::getInstance()->writeToAtPort(At::sidNid + At::end);
    QTimer::singleShot(SID_NID_TIMEOUT, this, SLOT(onReadSidNid()));

    return (true);
}

bool DeamonNetwork::onReadSidNid () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::sidNid))) {
        QString value = data.remove(At::sidNid).remove(OK_STRING).simplified();
        emit sidNidUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readSectorId () {
    DeamonPort::getInstance()->writeToAtPort(At::sectorId + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadSectorId()));

    return true;
}

bool DeamonNetwork::onReadSectorId () {
    bool result = false;

    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::sectorId))) {
        QString value = data.remove(At::sectorId).remove(OK_STRING).simplified();
        emit sectorIdUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readDrc () {
    DeamonPort::getInstance()->writeToAtPort(At::drc+At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onDrcLabel()));

    return true;
}


bool DeamonNetwork::onReadDrc() {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::drc))) {
        QString value = data.remove(At::drc).remove(OK_STRING).simplified();
        emit sectorIdUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readCdmaEcio() {
    DeamonPort::getInstance()->writeToAtPort(At::cdmaEcio + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onCdmaEcio()));

    return (true);
}

bool DeamonNetwork::onReadCdmaEcio () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::cdmaEcio))) {
        QString value = data.remove(At::cdmaEcio).remove(OK_STRING).simplified();
        emit cdmaEcioUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readHdrEcio () {
    DeamonPort::getInstance()->writeToAtPort(At::hdrEcio + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onHdrEcio()));

    return (true);
}

bool DeamonNetwork::onReadHdrEcio () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::hdrEcio))) {
        QString value = data.remove(At::hdrEcio).remove(OK_STRING).simplified();
        emit hdrEcioUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readEsn () {
    DeamonPort::getInstance()->writeToAtPort(At::esn + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadEsn()));

    return (true);
}

bool DeamonNetwork::onReadEsn () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::esn))) {
        QString value = data.remove(At::hdrEcio).remove(OK_STRING).simplified();
        emit esnUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readHardwareVersion () {
    DeamonPort::getInstance()->writeToAtPort(At::hardwareVersion + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadHardwareVersion()));

    return (true);
}

bool DeamonNetwork::onReadHardwareVersion () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::hardwareVersion))) {
        QString value = data.remove(At::hardwareVersion).remove(OK_STRING).simplified();
        emit hardwareVersionUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readPrl () {
    DeamonPort::getInstance()->writeToAtPort(At::prl + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadPrl()));

    return (true);
}

bool DeamonNetwork::onReadPrl () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::prl))) {
        QString value = data.remove(At::prl).remove(OK_STRING).simplified();
        emit hdrEcioUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readCompileDate () {
    DeamonPort::getInstance()->writeToAtPort(At::compileDate + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadCompileDate()));

    return (true);
}

bool DeamonNetwork::onReadCompileDate () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::compileDate))) {
        QString value = data.remove(At::compileDate).remove(OK_STRING).simplified();
        emit compileDateUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readPEsn () {
    DeamonPort::getInstance()->writeToAtPort(At::pEsn + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadPEsn()));

    return (true);
}

bool DeamonNetwork::onReadPEsn () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::pEsn))) {
        QString value = data.remove(At::pEsn).remove(OK_STRING).simplified();
        emit pEsnUpdate(value);
        result = true;
    }

    return (result);
}

bool DeamonNetwork::readSoftwareVersion () {
    DeamonPort::getInstance()->writeToAtPort(At::softwareVersion + At::end);
    QTimer::singleShot(SECTOR_ID_TIMEOUT, this, SLOT(onReadSoftwareVersion()));

    return (true);
}

bool DeamonNetwork::onReadSoftwareVersion () {
    bool result = false;
    QString data = DeamonPort::getInstance()->readFromAtPort();

    if (( 0 < data.length()) && (data.contains(At::softwareVersion))) {
        QString value = data.remove(At::softwareVersion).remove(OK_STRING).simplified();
        emit softwareVersionUpdate(value);
        result = true;
    }

    return (result);
}


bool DeamonNetwork::setNetworkMode(QString networkModeName) {
    if ( NETWORK_MODE_ZERO == networkModeName ){
        DeamonPort::getInstance()->writeToAtPort(At::setModeZero + At::end);
    } else if ( NETWORK_MODE_ONE == networkModeName) {
       DeamonPort::getInstance()->writeToAtPort(At::setModeZero + At::end);
    } else if ( NETWORK_MODE_TWO == networkModeName) {
        DeamonPort::getInstance()->writeToAtPort(At::setModeTwo + At::end);
    } else if ( NETWORK_MODE_THREE == networkModeName) {
        DeamonPort::getInstance()->writeToAtPort(At::setModeThree + At::end);
    }

    return true;
}

bool DeamonNetwork::readModemInformation(){
    QWaitCondition sleep;
    QMutex mutex;

    this->readCompileDate();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_COMPILE_DATE_TIMEOUT);
    mutex.unlock();

    this->readPrl();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_PRL_TIMEOUT);
    mutex.unlock();

    this->readEsn();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_ESN_TIMEOUT);
    mutex.unlock();

    this->readPEsn();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_P_ESN_TIMEOUT);
    mutex.unlock();

    this->readHardwareVersion();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_HARDWARE_VERSION_TIMEOUT);
    mutex.unlock();

    this->readSoftwareVersion();
    mutex.lock();
    qDebug() << sleep.wait(&mutex, READ_SOFTWARE_VERSION_TIMEOUT);
    mutex.unlock();

    return true;
}
