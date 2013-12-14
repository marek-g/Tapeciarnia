#include "TrayIcon.h"

#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QQuickView>
#include <QQuickWindow>
#include <QQmlContext>

#include "TapeciarniaQMLWindow.h"

#include "ViewModels/SettingsViewModel.h"
#include "ViewModels/SourceViewModel.h"

#include "System/Desktop.h"


TrayIcon::TrayIcon() : _trayIcon(0), _trayIconMenu(0), _configView(0)
{
    _settingsViewModel = new SettingsViewModel();
    _settingsViewModel->loadFromFile();

    _providersManager = new ProvidersManager();
}

TrayIcon::~TrayIcon()
{
    if (_trayIcon != 0) {
        _trayIcon->hide();
        delete _trayIcon;
    }

    if (_trayIconMenu != 0) {
        delete _trayIconMenu;
    }

    delete _settingsViewModel;

    delete _providersManager;
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

    QAction *actionShowProvidersInfo = new QAction(tr("Show providers info"), this);
    connect(actionShowProvidersInfo, &QAction::triggered, this, &TrayIcon::showProvidersInfo);

    QAction *actionCopyWallpaperAddress = new QAction(tr("Copy wallpaper address"), this);
    connect(actionCopyWallpaperAddress, &QAction::triggered, this, &TrayIcon::copyWallpaperAddress);

    QAction *actionNextWallpaper = new QAction(tr("Next wallpaper"), this);
    connect(actionNextWallpaper, &QAction::triggered, this, &TrayIcon::nextWallpaper);

    QAction *actionQuit = new QAction(tr("&Quit"), this);
    connect(actionQuit, &QAction::triggered, this, &TrayIcon::quit);

    _trayIconMenu = new QMenu(0);
    _trayIconMenu->addAction(actionConfig);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(actionShowProvidersInfo);
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
        _configView = new TapeciarniaQMLWindow();

        connect(_configView, &TapeciarniaQMLWindow::windowClosing, this, &TrayIcon::configViewClosing);

        _configView->rootContext()->setContextProperty("dataContext", _settingsViewModel);

        _configView->setSource(QUrl::fromLocalFile("views/config.qml"));
        _configView->setResizeMode(QQuickView::SizeRootObjectToView);

        _configView->setMinimumWidth(500);
        _configView->setMinimumHeight(200);
    }

    if (_configView->isVisible())
    {
        _configView->hide();
    }
    else
    {
        _configView->show();
        _configView->requestActivate();
    }
}

void TrayIcon::configViewClosing()
{
    _settingsViewModel->saveToFile();
}

void TrayIcon::showProvidersInfo()
{
    QMessageBox msgBox;
    msgBox.setText(tr("List of supported sites:"));
    msgBox.setInformativeText(_providersManager->GetProvidersInfo());
    msgBox.exec();
}

void TrayIcon::copyWallpaperAddress()
{
}

void TrayIcon::nextWallpaper()
{
    QRect desktopSize = Desktop::GetSize();

    WallpaperResult result = _providersManager->DownloadRandomImage(
                _settingsViewModel->GetSources(),
                desktopSize.width(),
                desktopSize.height());

    Desktop::SetWallpaper(result.image);
}

void TrayIcon::quit()
{
    QApplication::quit();
}
