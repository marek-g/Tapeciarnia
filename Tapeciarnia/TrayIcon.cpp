#include "TrayIcon.h"

#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QMessageBox>
#include <QQuickView>
#include <QQuickWindow>
#include <QQmlContext>

#include "TapeciarniaQMLWindow.h"

#include "ViewModels/SettingsViewModel.h"
#include "ViewModels/SourceViewModel.h"

#include "System/Desktop.h"


TrayIcon::TrayIcon() : _trayIcon(0),
    _normalIcon(new QIcon(QApplication::applicationDirPath() + "/images/tray_icon.png")),
    _loadingIcon(new QIcon(QApplication::applicationDirPath() + "/images/tray_icon_loading.png")),
    _trayIconMenu(0), _configView(0),
    _timeCounter(0)
{
    _settingsViewModel = new SettingsViewModel();
    _settingsViewModel->SetTrayIcon(this);
    _settingsViewModel->loadFromFile();

    _providersManager = new ProvidersManager();

    _timer = new QTimer();
    connect(_timer, &QTimer::timeout, this, &TrayIcon::onTimer);
    _timer->start(10000);
}

TrayIcon::~TrayIcon()
{
    if (_timer != 0)
    {
        _timer->stop();
        delete _timer; _timer = 0;
    }

    if (_trayIcon != 0) {
        _trayIcon->hide();
        delete _trayIcon; _trayIcon = 0;
    }

    if (_trayIconMenu != 0) {
        delete _trayIconMenu; _trayIconMenu = 0;
    }

    if (_normalIcon != 0) {
        delete _normalIcon; _normalIcon = 0;
    }

    if (_loadingIcon != 0) {
        delete _loadingIcon; _loadingIcon = 0;
    }

    delete _settingsViewModel; _settingsViewModel = 0;

    delete _providersManager; _providersManager = 0;
}

void TrayIcon::show()
{
    createTrayIcon();

    nextWallpaper();
}

void TrayIcon::createTrayIcon()
{
    if (_trayIcon != 0) return;

    QAction *actionConfig = new QAction(tr("Config..."), this);
    connect(actionConfig, &QAction::triggered, this, &TrayIcon::toggleConfigView);

    QAction *actionAbout = new QAction(tr("About..."), this);
    connect(actionAbout, &QAction::triggered, this, &TrayIcon::about);

    QAction *actionShowProvidersInfo = new QAction(tr("Show providers info..."), this);
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
    _trayIconMenu->addAction(actionAbout);
    _trayIconMenu->addAction(actionShowProvidersInfo);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(actionCopyWallpaperAddress);
    _trayIconMenu->addAction(actionNextWallpaper);
    _trayIconMenu->addSeparator();
    _trayIconMenu->addAction(actionQuit);

    _trayIcon = new QSystemTrayIcon(0);
    _trayIcon->setContextMenu(_trayIconMenu);
    _trayIcon->setIcon(*_normalIcon);
    _trayIcon->setToolTip(tr("Tapeciarnia"));

    connect(_trayIcon, &QSystemTrayIcon::activated,
            this, &TrayIcon::iconActivated);

    _trayIcon->show();
}

void TrayIcon::updateToolTip()
{
    int secondsLeft = _settingsViewModel->ChangeEveryMinutes() * 60 -
            _timeCounter;
    QString strTimeLeft;
    strTimeLeft.sprintf("%02d:%02d:%02d",
        secondsLeft / (60*60),
        (secondsLeft / 60) % 60,
        (secondsLeft % 60));

    _trayIcon->setToolTip(_currentName + "\r\n" +
                          _currentDescription + "\r\n" +
                          strTimeLeft);
}

void TrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:

        // show config menu after left click on the icon
        //toggleConfigView();

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

        _configView->setSource(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/views/config.qml"));
        _configView->setResizeMode(QQuickView::SizeRootObjectToView);

        _configView->setMinimumWidth(500);
        _configView->setMinimumHeight(250);
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
    _settingsViewModel->loadFromFile();
}

void TrayIcon::about()
{
    QMessageBox msgBox;
    msgBox.setText(QString("<html>") +
                   QString("<h1><b>Tapeciarnia</b></h1><br>") +
                   QString("<b>") + tr("Author:") + QString("</b> Marek Gibek<br>") +
                   QString("<b>") + tr("Compilation date:") + "</b> " + __DATE__ + " " + __TIME__ +
                   QString("<br><br></html>"));
    msgBox.exec();
}

void TrayIcon::showProvidersInfo()
{
    QMessageBox msgBox;
    msgBox.setText(QString("<html>") +
                   "<h2>" + tr("List of supported sites:") + "</h2><br>" +
                   _providersManager->GetProvidersInfo() +
                   QString("</html>"));
    msgBox.exec();
}

void TrayIcon::copyWallpaperAddress()
{
    QApplication::clipboard()->setText(_currentUrl);
}

void TrayIcon::nextWallpaper()
{
    try
    {
        QRect desktopSize = Desktop::GetSize();

        _trayIcon->setIcon(*_loadingIcon);

        WallpaperResult result = _providersManager->DownloadRandomImage(
                    _settingsViewModel->GetSources(),
                    desktopSize.width(),
                    desktopSize.height());

        Desktop::SetWallpaper(result.image);

        _trayIcon->setIcon(*_normalIcon);

        _currentUrl = result.url;
        _currentDescription = result.urlDescription;
        _currentName = result.name;

        _trayIcon->showMessage(result.name,
                               result.urlDescription,
                               QSystemTrayIcon::Information, 4000);

        _timeCounter = 0;
        updateToolTip();
    }
    catch (...)
    {
    }
}

void TrayIcon::onTimer()
{
    _timeCounter += 10;
    if (_timeCounter >= _settingsViewModel->ChangeEveryMinutes()*60)
    {
        nextWallpaper();
    }
    else
    {
        updateToolTip();
    }
}

void TrayIcon::quit()
{
    QApplication::quit();
}
