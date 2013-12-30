#ifndef IMPERIUMTAPETPROVIDER_H
#define IMPERIUMTAPETPROVIDER_H

#include <QObject>

#include "IWallpaperProvider.h"
#include "../RandomGenerator.h"

class ImperiumTapetProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

public:

    ImperiumTapetProvider(RandomGenerator &randomGenerator) :
        _randomGenerator(randomGenerator) { }
    virtual ~ImperiumTapetProvider() { }

    virtual QString GetMainPageUrl();
    virtual bool IsAddressSupported(const QString &url);
    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters);

    QByteArray GetDataFromUrl(const QString &url);

private:

    RandomGenerator &_randomGenerator;
};

#endif // IMPERIUMTAPETPROVIDER_H
