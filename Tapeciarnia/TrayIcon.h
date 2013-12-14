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
    void showProvidersInfo();
    void copyWallpaperAddress();
    void nextWallpaper();
    void quit();

private:
    void createTrayIcon();
    void updateToolTip();

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    TapeciarniaQMLWindow *_configView;
    SettingsViewModel *_settingsViewModel;
    ProvidersManager *_providersManager;

    QString _currentUrl;
    QString _currentDescription;
    QString _currentName;
};

#endif // TRAYICON_H
