#include "ProvidersManager.h"
#include <time.h>

ProvidersManager::ProvidersManager() :
    _randomGenerator(time(NULL))
{
    // create providers
    _providers.push_back((IWallpaperProvider *)new WallpapersWideProvider(_randomGenerator));
}

ProvidersManager::~ProvidersManager()
{
    for (int i = 0; i < (int)_providers.size(); i++)
    {
        delete _providers[i];
    }
}

WallpaperResult ProvidersManager::DownloadRandomImage(QList<SourceViewModel*> &sources,
                                    int prefferedWidth, int prefferedHeight)
{
    SourceViewModel *source = GetRandomSource(sources);
    if (source == 0) {
        WallpaperResult result;
        return result;
    }

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

    WallpaperResult result = provider->DownloadRandomImage(params);
    result.urlDescription = source->Description();
    return result;
}

QString ProvidersManager::GetProvidersInfo()
{
    QString urls;
    for (int i = 0; i < (int)_providers.size(); i++)
    {
        urls += (_providers[i]->GetMainPageUrl() + "\n");
    }
    return urls;
}

SourceViewModel *ProvidersManager::GetRandomSource(QList<SourceViewModel*> sources)
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

    int randomValue = _randomGenerator.get() % maxProbability;

    for (int i = 0; i < sources.size(); i++)
    {
        randomValue -= sources[i]->Weight();
        if (randomValue < 0) {
            return sources[i];
        }
    }

    return 0;
}

IWallpaperProvider *ProvidersManager::GetProviderForUrl(const QString &url)
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
