#ifndef DESKTOP_H
#define DESKTOP_H

#include <QByteArray>
#include <QRect>
#include <QString>

#include <windows.h>
#include <gdiplus.h>

class Desktop
{
public:

    static QRect GetSize();
    static void SetWallpaper(const QByteArray &image);
    static void ConvertImageToBMP(const QString &src, const QString &dest);

private:
    static Gdiplus::Bitmap *RescaleBitmapToFillScreen(Gdiplus::Bitmap *bmp);
};

#endif // DESKTOP_H
