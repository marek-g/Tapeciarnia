#if __linux__

#include "Desktop.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDir>
#include <QDateTime>

#include <QProcess>

QRect Desktop::GetSize()
{
    return QApplication::desktop()->screenGeometry();
}

void Desktop::SetWallpaper(const QByteArray &image)
{
    QString wallpaperDirectory = QDir::homePath() + "/Obrazy/Tapeciarnia";
    QString wallpaperFilePath = wallpaperDirectory + "/wallpaper_"
        + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + ".jpg";

    QDir().mkdir(wallpaperDirectory);

    QDir dir(wallpaperDirectory);
    dir.setNameFilters(QStringList() << "wallpaper_*.jpg");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }

    // save array
    QFile file(wallpaperFilePath);
    file.open(QIODevice::WriteOnly);
    file.write(image);
    file.close();

    QProcess process;

    //
    // GNOME
    //

    process.start(QString("gsettings set org.gnome.desktop.background picture-uri ") + wallpaperFilePath);
    process.waitForFinished();
    process.start(QString("gsettings set org.gnome.desktop.background picture-options wallpaper"));
    process.waitForFinished();

    //
    // KDE
    // requires filename to change everytime to detect change
    //

    QString script;
    script = "var allDesktops=desktops();";
    script += "for(var i=0;i<allDesktops.length;i++){";
    script += "  var d=allDesktops[i];";
    script += "  d.wallpaperPlugin=\"org.kde.image\";";
    script += "  d.currentConfigGroup=Array(\"Wallpaper\",\"org.kde.image\",\"General\");";
    script += "  d.writeConfig(\"Image\",\"file://" + wallpaperFilePath + "\");";
    script += "  d.reloadConfig();";
    script += "}";
    QStringList args;
    args << "org.kde.plasmashell"
         << "/PlasmaShell"
         << "org.kde.PlasmaShell.evaluateScript"
         << script;
    process.start(QString("qdbus"), args);
    process.waitForFinished();
}


#endif // __linux__

