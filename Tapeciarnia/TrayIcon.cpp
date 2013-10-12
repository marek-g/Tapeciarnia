#include "TrayIcon.h"

#include <QApplication>
#include <QMenu>
#include <QQuickView>


TrayIcon::TrayIcon() : _trayIcon(0), _trayIconMenu(0), _configView(0)
{
}

TrayIcon::~TrayIcon()
{
}

void TrayIcon::show()
{
    createTrayIcon();
}


void TrayIcon::createTrayIcon()
{
    if (_trayIcon != 0) return;

    QAction *actionConfig = new QAction(tr("Config"), this);
    connect(actionConfig, &QAction::triggered, this, &TrayIcon::toggleConfigView);

    QAction *actionCopyWallpaperAddress = new QAction(tr("Copy wallpaper address"), this);
    connect(actionCopyWallpaperAddress, &QAction::triggered, this, &TrayIcon::copyWallpaperAddress);

    QAction *actionNextWallpaper = new QAction(tr("Next wallpaper"), this);
    connect(actionNextWallpaper, &QAction::triggered, this, &TrayIcon::nextWallpaper);

    QAction *actionQuit = new QAction(tr("&Quit"), this);
    connect(actionQuit, &QAction::triggered, this, &TrayIcon::quit);

    _trayIconMenu = new QMenu(0);
    _trayIconMenu->addAction(actionConfig);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(actionCopyWallpaperAddress);
    _trayIconMenu->addAction(actionNextWallpaper);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(actionQuit);

    _trayIcon = new QSystemTrayIcon(0);
    _trayIcon->setContextMenu(_trayIconMenu);
    _trayIcon->setIcon(QIcon("images/tray_icon.png"));
    _trayIcon->setToolTip(tr("Tapeciarnia"));

    connect(_trayIcon, &QSystemTrayIcon::activated,
            this, &TrayIcon::iconActivated);

    _trayIcon->show();
}

void TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        toggleConfigView();
        break;
    default:
        break;
    }
}

void TrayIcon::toggleConfigView()
{
    if (_configView == 0)
    {
        _configView = new QQuickView();
        _configView->setSource(QUrl::fromLocalFile("views/config.qml"));
        _configView->setResizeMode(QQuickView::SizeViewToRootObject);
    }

    if (_configView->isVisible())
    {
        _configView->hide();
    }
    else
    {
        _configView->show();
    }
}

void TrayIcon::copyWallpaperAddress()
{
}

void TrayIcon::nextWallpaper()
{
}

void TrayIcon::quit()
{
    QApplication::quit();
}
