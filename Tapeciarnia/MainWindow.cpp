#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    createActions();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::createActions()
{
    _actionConfig = new QAction(tr("Config"), this);
    connect(_actionConfig, SIGNAL(triggered()), this, SLOT(show()));

    _actionCopyWallpaperAddress = new QAction(tr("Copy wallpaper address"), this);
    connect(_actionCopyWallpaperAddress, SIGNAL(triggered()), this, SLOT(copyWallpaperAddress()));

    _actionNextWallpaper = new QAction(tr("Next wallpaper"), this);
    connect(_actionNextWallpaper, SIGNAL(triggered()), this, SLOT(nextWallpaper()));

    _actionQuit = new QAction(tr("&Quit"), this);
    connect(_actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    _trayIconMenu = new QMenu(this);
    _trayIconMenu->addAction(_actionConfig);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(_actionCopyWallpaperAddress);
    _trayIconMenu->addAction(_actionNextWallpaper);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(_actionQuit);

    _trayIcon = new QSystemTrayIcon(this);
    _trayIcon->setContextMenu(_trayIconMenu);
    _trayIcon->setIcon(QIcon(":/images/tray_icon.png"));
    _trayIcon->setToolTip(tr("Tapeciarnia"));

    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    _trayIcon->show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        show();
        break;
    default:
        break;
    }
}

void MainWindow::copyWallpaperAddress()
{
}

void MainWindow::nextWallpaper()
{
}
