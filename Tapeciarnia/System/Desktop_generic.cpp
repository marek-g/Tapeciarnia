#if !_WIN32 && !__linux__

#include "Desktop.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDir>

QRect Desktop::GetSize()
{
    return QApplication::desktop()->screenGeometry();
}

void Desktop::SetWallpaper(const QByteArray &image)
{
    QString wallpaperDirectory = QDir::homePath() + "/Obrazy/Wallpaper";
    QString wallpaperFilePath = wallpaperDirectory + "/wallpaper.jpg";

    QDir().mkdir(wallpaperDirectory);

    // save array
    QFile file(wallpaperFilePath);
    file.open(QIODevice::WriteOnly);
    file.write(image);
    file.close();
}

#endif // !_WIN32 && !__linux__

