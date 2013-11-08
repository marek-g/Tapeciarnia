#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>

#include "TapeciarniaQMLWindow.h"
#include "ProvidersManager.h"

#include "ViewModels/SettingsViewModel.h"

class QMenu;
class QQuickView;
class QQuickCloseEvent;

class TrayIcon : public QObject
{
    Q_OBJECT
    
public:
    TrayIcon();
    ~TrayIcon();

    void show();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void toggleConfigView();
    void configViewClosing();
    void copyWallpaperAddress();
    void nextWallpaper();
    void quit();

private:
    void createTrayIcon();

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    TapeciarniaQMLWindow *_configView;
    SettingsViewModel *_settingsViewModel;
    ProvidersManager *_providersManager;
};

#endif // TRAYICON_H
