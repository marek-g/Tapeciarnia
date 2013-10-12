#include "TrayIcon.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QShowEvent>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("translations/Tapeciarnia_" + QLocale::system().name());
    a.installTranslator(&myappTranslator);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Tapeciarnia"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    TrayIcon trayIcon;
    trayIcon.show();
    
    return a.exec();
}
