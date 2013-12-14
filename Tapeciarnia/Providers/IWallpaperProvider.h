#ifndef IWALLPAPERPROVIDER_H
#define IWALLPAPERPROVIDER_H

#include <QString>

struct WallpaperParameters
{
    int prefferedWidth;

    int prefferedHeight;

    QString url;
};

struct WallpaperResult
{
    QString name;

    QByteArray image;
};


class IWallpaperProvider
{

public:

    virtual ~IWallpaperProvider() { }

    virtual QString GetDescription() = 0;

    virtual bool IsAddressSupported(const QString &url) = 0;

    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters) = 0;

};

#endif // IWALLPAPERPROVIDER_H
