#-------------------------------------------------
#
# Project created by QtCreator 2011-07-06T16:45:14
#
#-------------------------------------------------

QT += core gui sql network webkit
CONFIG += qt warn_on

DEFINES += WINVER=0x0501

TARGET = Tata
TEMPLATE = app

RESOURCES += resource/images.qrc
RC_FILE = resource/tata.rc

LIBS += -lrasapi32

SOURCES += main.cpp\
    MainWindow.cpp \
    ImageButton.cpp \
    UserInterface.cpp \
    DeamonConnection.cpp \
    DeamonDatabase.cpp \
    Profile.cpp \
    AnimateButton.cpp \
    SingleApplication.cpp \
    IpValidator.cpp \
    DeamonSetting.cpp \
    AboutDialog.cpp \
    PinChangeDialog.cpp \
    ExitDialog.cpp \
    TestDialog.cpp \
    PinDialog.cpp \
    DiagnosticDialog.cpp \
    MessageWidget.cpp \
    ProfileDialog.cpp \
    SystemInformationDialog.cpp \
    DeamonInterface.cpp \
    ActivationWidget.cpp \
    GeneralWidget.cpp \
    InformationWidget.cpp \
    IpAddressWidget.cpp \
    NetworkWidget.cpp \
    LockWidget.cpp \
    WebSectionWidget.cpp

HEADERS  += MainWindow.h \
    ImageButton.h \
    UserInterface.h \
    DeamonConnection.h \
    Defines.h \
    DeamonDatabase.h \
    Profile.h \
    AnimateButton.h \
    SingleApplication.h \
    IpValidator.h \
    DeamonSetting.h \
    DeamonInterface.h \
    AboutDialog.h \
    PinChangeDialog.h \
    ExitDialog.h \
    TestDialog.h \
    PinDialog.h \
    DiagnosticDialog.h \
    MessageWidget.h \
    ProfileDialog.h \
    SystemInformationDialog.h \
    ActivationWidget.h \
    GeneralWidget.h \
    InformationWidget.h \
    IpAddressWidget.h \
    NetworkWidget.h \
    LockWidget.h \
    WebSectionWidget.h

HEADERS += SerialPort.h \
        SerialEnumerator.h \

SOURCES	+= SerialPort.cpp

unix:SOURCES += SerialPortPosix.cpp
unix:!macx:SOURCES += SerialPortUnix.cpp

macx {
  SOURCES          += SerialPortOsx.cpp
  LIBS             += -framework IOKit -framework CoreFoundation
}

win32 {
  SOURCES          += SerialPortWin.cpp SerialEnumeratorWin.cpp
  LIBS             += -lsetupapi -ladvapi32 -luser32
}











































































