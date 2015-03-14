#include "MainWindow.h"
#include "SerialPort.h"
#include "SerialEnumerator.h"

#include <QApplication>
#include <QList>
#include <QProcess>
#include <QSettings>

MainWindow::MainWindow(
        QWidget *parent)
    : QMainWindow(parent) {

    if (false == this->checkRegistry ()) {

        this->runSetup ();

    } else {

        this->runApplication ();
    }

}

MainWindow::~MainWindow() {

}

bool MainWindow::checkRegistry () {

    QSettings setting("HKEY_LOCAL_MACHINE\\Software\\Wow6432Node\\Aircel", QSettings::NativeFormat);
    this->installDirectory = setting.value ("InstallationDirectory").toString ();
    this->amd = true;

    if (true == this->installDirectory.isEmpty ()) {

        QSettings setting("HKEY_LOCAL_MACHINE\\Software\\Aircel", QSettings::NativeFormat);
        this->installDirectory = setting.value ("InstallationDirectory").toString ();
        this->amd = false;
    }

    this->installDirectory.replace ("\\", "/");
    return (false == this->installDirectory.isEmpty ());
}

bool MainWindow::runSetup () {

    QProcess::startDetached (qApp->applicationDirPath() + "/setup.exe");

    return true;
}

bool MainWindow::installDriver () {
    QString driverDirectory = this->installDirectory + "/drivers";
    QString driverPath = driverDirectory;

    if (false == this->amd) {
        \
        driverPath += "/x86";

    } else {

        driverPath += "/x64";
    }

    QProcess::startDetached (driverPath + "/dpinst.exe", QStringList (), driverDirectory);

    return true;
}

bool MainWindow::runApplication () {

    QProcess::startDetached (this->installDirectory + "/Aircel.exe", QStringList (), this->installDirectory);

    return true;
}
