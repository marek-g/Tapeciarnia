#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Tapeciarnia);

    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Tapeciarnia"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    
    return a.exec();
}
