#ifndef TAPETYTJAPROVIDER_H
#define TAPETYTJAPROVIDER_H

#include "IWallpaperProvider.h"
#include "../RandomGenerator.h"

#include <QObject>

class TapetyTJAProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

public:

    TapetyTJAProvider() { }
    virtual ~TapetyTJAProvider() { }

    virtual QString GetMainPageUrl();
    virtual bool IsAddressSupported(const QString &url);
    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters);

};

#endif // TAPETYTJAPROVIDER_H
