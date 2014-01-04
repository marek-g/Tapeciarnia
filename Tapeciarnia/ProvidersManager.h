#ifndef PROVIDERSMANAGER_H
#define PROVIDERSMANAGER_H

#include <QTime>
#include <vector>

#include "Providers/IWallpaperProvider.h"
#include "ViewModels/SourceViewModel.h"

#include "RandomGenerator.h"

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

    RandomGenerator _randomGenerator;
};

#endif // PROVIDERSMANAGER_H
