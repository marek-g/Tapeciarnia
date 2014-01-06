#ifndef DESKTOP_H
#define DESKTOP_H

#include <QByteArray>
#include <QRect>
#include <QString>

class Desktop
{

public:

    static QRect GetSize();
    static void SetWallpaper(const QByteArray &image);

};

#endif // DESKTOP_H
