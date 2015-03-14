#include <QtGui/QApplication>

#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QSplashScreen>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QTextStream>

#include "MainWindow.h"

#include "Defines.h"
#include "SingleApplication.h"
#include "UserInterface.h"

void myMessageHandler(QtMsgType messageType, const char *message) {
    QString logMessage;

    switch (messageType) {
    case QtDebugMsg: {
            logMessage = QString("Debug: %1").arg(message);
            fprintf(stderr, "Debug: %s\n", message);
        }break;

    case QtWarningMsg: {
            logMessage = QString("Warning: %1").arg(message);
            fprintf(stderr, "Warning: %s\n", message);
        }break;

    case QtCriticalMsg: {
            logMessage = QString("Critical: %1").arg(message);
            fprintf(stderr, "Critical: %s\n", message);
        }break;

    case QtFatalMsg: {
            logMessage = QString("Fatal: %1").arg(message);
            fprintf(stderr, "Fatal: %s\n", message);
            abort();
        }break;
    }

    QFile outFile(QDir::tempPath () + SLASH + "tata");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&outFile);
    textStream << logMessage << endl;
}

int main(int argc, char *argv[]) {

    SingleApplication application(argc, argv, "0b40dd2b-9147-4754-a8ef-15cdf17584cf");

    if (application.isRunning()) {
        application.sendMessage("Message from other instace");
        return (0);
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return (1);
    }

    qInstallMsgHandler(myMessageHandler);

    // SingleApplication::setQuitOnLastWindowClosed(false);

    QSplashScreen splash(QPixmap(":/splash.png"));
    splash.show();
    application.processEvents();

    MainWindow mainWindow;
    mainWindow.setFixedSize(UserInterface::windowWidth, UserInterface::windowHeight);
    mainWindow.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    mainWindow.setWindowIcon(QIcon(":/ttslMax.png"));
    mainWindow.setAttribute(Qt::WA_TranslucentBackground);
    QObject::connect (&application, SIGNAL(messageAvailable(const QString&)), &mainWindow, SLOT(onReceiveMessage(const QString&)));

    QTimer::singleShot(SPLASH_SCREEN_TIMEOUT, &splash, SLOT(close()));
    QTimer::singleShot(SPLASH_SCREEN_TIMEOUT, &mainWindow, SLOT(show()));

    return (application.exec());
}
