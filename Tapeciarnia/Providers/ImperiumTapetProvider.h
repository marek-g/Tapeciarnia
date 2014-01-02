#ifndef IMPERIUMTAPETPROVIDER_H
#define IMPERIUMTAPETPROVIDER_H

#include "IWallpaperProvider.h"
#include "../RandomGenerator.h"

#include <QObject>
#include <QHash>

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

private:

    QString GetRandomPage(const QString &url);
    int GetNumberOfPages(const QString &url);

    RandomGenerator &_randomGenerator;
    QHash<QString, int> _numberOfPages;
};

#endif // IMPERIUMTAPETPROVIDER_H
