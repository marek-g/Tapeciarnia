#ifndef PROVIDERSMANAGER_H
#define PROVIDERSMANAGER_H

#include <QGlobal.h>
#include <QTime>
#include <vector>

#include "Providers/IWallpaperProvider.h"
#include "Providers/WallpapersWideProvider.h"
#include "ViewModels/SourceViewModel.h"

class ProvidersManager
{

public:

    ProvidersManager();
    ~ProvidersManager();

    WallpaperResult DownloadRandomImage(QList<SourceViewModel*> &sources,
                                        int prefferedWidth, int prefferedHeight);
    QString GetProvidersInfo();

private:

    SourceViewModel *GetRandomSource(QList<SourceViewModel*> sources);
    IWallpaperProvider *GetProviderForUrl(const QString &url);

    std::vector<IWallpaperProvider*> _providers;
};

#endif // PROVIDERSMANAGER_H
