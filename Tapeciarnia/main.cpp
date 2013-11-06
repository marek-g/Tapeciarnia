#include "TrayIcon.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QShowEvent>
#include <QTranslator>
#include <QtQml>

#include "ViewModels/SettingsViewModel.h"
#include "ViewModels/SourceViewModel.h"

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
    
    // register QML types
    qmlRegisterType<SourceViewModel>("SourceViewModel", 1, 0, "SourceViewModel");
    qmlRegisterType<SettingsViewModel>("SettingsViewModel", 1, 0, "SettingsViewModel");

    return a.exec();
}
