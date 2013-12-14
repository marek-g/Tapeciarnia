#ifndef WALLPAPERSWIDEPROVIDER_H
#define WALLPAPERSWIDEPROVIDER_H

#include <QObject>

#include "IWallpaperProvider.h"

class WallpapersWideProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

    virtual ~WallpapersWideProvider() { }

    virtual QString GetMainPageUrl();
    virtual bool IsAddressSupported(const QString &url);
    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters);

private:

    QString GetRandomPage(const QString &url);
    WallpaperResult GetRandomWallpaper(WallpaperParameters parameters, const QString &page);
    QString GetBestImageUrl(WallpaperParameters parameters, QString imageName);
    QByteArray GetDataFromUrl(const QString &url);
};

#endif // WALLPAPERSWIDEPROVIDER_H
