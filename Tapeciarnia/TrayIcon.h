#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>

class QMenu;
class QQuickView;

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
    void copyWallpaperAddress();
    void nextWallpaper();
    void quit();

private:
    void createTrayIcon();

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;
    QQuickView *_configView;
};

#endif // TRAYICON_H
