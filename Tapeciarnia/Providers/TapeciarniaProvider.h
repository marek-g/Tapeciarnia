#ifndef TAPECIARNIAPROVIDER_H
#define TAPECIARNIAPROVIDER_H

#include "IWallpaperProvider.h"
#include <QObject>

class TapeciarniaProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

public:

    TapeciarniaProvider() { }
    virtual ~TapeciarniaProvider() { }

    virtual QString GetMainPageUrl();
    virtual bool IsAddressSupported(const QString &url);
    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters);

};

#endif // TAPECIARNIAPROVIDER_H
