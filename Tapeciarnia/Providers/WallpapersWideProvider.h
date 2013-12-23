#ifndef WALLPAPERSWIDEPROVIDER_H
#define WALLPAPERSWIDEPROVIDER_H

#include <QObject>

#include "IWallpaperProvider.h"
#include "../RandomGenerator.h"

class WallpapersWideProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

public:

    WallpapersWideProvider(RandomGenerator &randomGenerator) :
        _randomGenerator(randomGenerator) { }
    virtual ~WallpapersWideProvider() { }

    virtual QString GetMainPageUrl();
    virtual bool IsAddressSupported(const QString &url);
    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters);

private:

    QString GetRandomPage(const QString &url);
    WallpaperResult GetRandomWallpaper(WallpaperParameters parameters, const QString &page);
    QString GetBestImageUrl(WallpaperParameters parameters, QString imageName);
    QByteArray GetDataFromUrl(const QString &url);

    RandomGenerator &_randomGenerator;
};

#endif // WALLPAPERSWIDEPROVIDER_H
