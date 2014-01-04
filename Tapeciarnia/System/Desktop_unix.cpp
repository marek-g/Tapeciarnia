#ifdef __unix

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
    QString wallpaperPathJPG = QDir::homePath() + "/Pictures/Wallpaper";

    QDir().mkdir(wallpaperPathJPG);

    wallpaperPathJPG += "/wallpaper.jpg";

    // save array
    QFile file(wallpaperPathJPG);
    file.open(QIODevice::WriteOnly);
    file.write(image);
    file.close();
}


#endif // __unix

