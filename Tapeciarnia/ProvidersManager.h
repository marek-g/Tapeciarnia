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

    ProvidersManager()
    {
        // create providers
        _providers.push_back((IWallpaperProvider *)new WallpapersWideProvider());

        // initialize random number generator
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
    }

    ~ProvidersManager()
    {
        for (int i = 0; i < (int)_providers.size(); i++)
        {
            delete _providers[i];
        }
    }

    WallpaperResult DownloadRandomImage(QList<SourceViewModel*> &sources,
                                        int prefferedWidth, int prefferedHeight)
    {
        SourceViewModel *source = GetRandomSource(sources);
        IWallpaperProvider *provider = GetProviderForUrl(source->Url());

        if (provider == 0)
        {
            WallpaperResult result;
            return result;
        }

        WallpaperParameters params;
        params.prefferedWidth = prefferedWidth;
        params.prefferedHeight = prefferedHeight;
        params.url = source->Url();

        return provider->DownloadRandomImage(params);
    }

private:

    SourceViewModel *GetRandomSource(QList<SourceViewModel*> sources)
    {
        int maxProbability = 0;
        for (int i = 0; i < sources.size(); i++)
        {
            maxProbability += sources[i]->Weight();
        }

        if (maxProbability == 0)
        {
            return 0;
        }

        int randomValue = qrand() % maxProbability;

        for (int i = 0; i < sources.size(); i++)
        {
            randomValue -= sources[i]->Weight();
            if (randomValue < 0) {
                return sources[i];
            }
        }

        return 0;
    }

    IWallpaperProvider *GetProviderForUrl(QString &url)
    {
        for (int i = 0; i < (int)_providers.size(); i++)
        {
            if (_providers[i]->IsAddressSupported(url))
            {
                return _providers[i];
            }
        }

        return 0;
    }

    std::vector<IWallpaperProvider*> _providers;
};

#endif // PROVIDERSMANAGER_H
