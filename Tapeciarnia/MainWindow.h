#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSystemTrayIcon *getTrayIcon() const;
    void setTrayIcon(QSystemTrayIcon *value);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void copyWallpaperAddress();
    void nextWallpaper();

private:
    void createActions();
    void createTrayIcon();

    QAction *_actionConfig;
    QAction *_actionCopyWallpaperAddress;
    QAction *_actionNextWallpaper;
    QAction *_actionQuit;

    QSystemTrayIcon *_trayIcon;
    QMenu *_trayIconMenu;

    Ui::MainWindow *_ui;
};

#endif // MAINWINDOW_H
