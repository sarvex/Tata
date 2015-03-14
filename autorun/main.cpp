#include <QtGui/QApplication>
#include "MainWindow.h"

int
main(
        int argc, char *argv[]) {

    QApplication application(argc, argv);
    MainWindow mainWindow;

    Q_UNUSED (application);
    Q_UNUSED (mainWindow);

    return 0;
}
