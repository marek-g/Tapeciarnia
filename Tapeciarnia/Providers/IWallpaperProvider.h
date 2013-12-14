#ifndef IWALLPAPERPROVIDER_H
#define IWALLPAPERPROVIDER_H

#include <QByteArray>
#include <QString>

struct WallpaperParameters
{
    int prefferedWidth;

    int prefferedHeight;

    QString url;
};

struct WallpaperResult
{
    // for display purposes
    QString name;

    // the image data
    QByteArray image;

    // the url user may want to copy to clipboard
    QString url;
};


class IWallpaperProvider
{

public:

    virtual ~IWallpaperProvider() { }

    virtual QString GetMainPageUrl() = 0;

    virtual bool IsAddressSupported(const QString &url) = 0;

    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters) = 0;

};

#endif // IWALLPAPERPROVIDER_H
