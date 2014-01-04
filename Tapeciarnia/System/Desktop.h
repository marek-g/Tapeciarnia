#ifndef DESKTOP_H
#define DESKTOP_H

#include <QByteArray>
#include <QRect>
#include <QString>

#ifdef _WIN32
#include <windows.h>
#include <minmax.h>
#include <gdiplus.h>
#endif // _WIN32

class Desktop
{
public:

    static QRect GetSize();
    static void SetWallpaper(const QByteArray &image);

private:

#ifdef _WIN32
    static void ConvertImageToBMP(const QString &src, const QString &dest);
    static Gdiplus::Bitmap *RescaleBitmapToFillScreen(Gdiplus::Bitmap *bmp);
#endif // _WIN32

};

#endif // DESKTOP_H
