#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>

#include "TapeciarniaQMLWindow.h"
#include "ProvidersManager.h"

class SettingsViewModel;

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

public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void toggleConfigView();
    void configViewClosing();
    void about();
    void showProvidersInfo();
    void copyWallpaperAddress();
    void pauseOrResume();
    void nextWallpaper();
    void onTimer();
    void quit();

private:
    void createTrayIcon();
    void updateMenu();
    void updateToolTip();
    void updateTrayIcon();

    QSystemTrayIcon *_trayIcon;
    QIcon *_iconNormal;
    QIcon *_iconLoading;
    QIcon *_iconPaused;
    QMenu *_trayIconMenu;
    TapeciarniaQMLWindow *_configView;
    SettingsViewModel *_settingsViewModel;
    ProvidersManager *_providersManager;

    QAction *_actionPauseOrResume;

    QTimer *_timer;
    int _timeCounter;
    bool _isPaused;

    QString _currentUrl;
    QString _currentDescription;
    QString _currentName;
};

#endif // TRAYICON_H
