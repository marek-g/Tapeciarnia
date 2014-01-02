#include "ImperiumTapetProvider.h"
#include "Utils.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QRegExp>
#include <cmath>

QString ImperiumTapetProvider::GetMainPageUrl()
{
    return "http://www.imperiumtapet.com/";
}

bool ImperiumTapetProvider::IsAddressSupported(const QString &url)
{
    if (url.startsWith("http://www.imperiumtapet.com/") || url.startsWith("https://www.imperiumtapet.com/"))
    {
        return true;
    }
    return false;
}

WallpaperResult ImperiumTapetProvider::DownloadRandomImage(WallpaperParameters parameters)
{
    QString url = parameters.url;
    if (!url.endsWith('/')) url += "/";

    QString strData = GetRandomPage(parameters.url);

    return WallpaperResult();
}

QString ImperiumTapetProvider::GetRandomPage(const QString &url)
{
    int i = GetNumberOfPages(url);

    return "";
}

int ImperiumTapetProvider::GetNumberOfPages(const QString &url)
{
    // check in dictionary
    if (_numberOfPages.contains(url))
    {
        return _numberOfPages[url];
    }

    int lastWorking = 0;
    int lastNotWorking = -1;

    while (lastNotWorking == -1 || lastWorking + 1 < lastNotWorking)
    {
        int pageToCheck;
        if (lastWorking == 0 && lastNotWorking == -1)
        {
            // initial check
            pageToCheck = 16;
        }
        else if (lastNotWorking == -1)
        {
            pageToCheck = lastWorking * 2;
        }
        else
        {
            pageToCheck = (lastWorking + lastNotWorking) / 2;
            if (pageToCheck <= lastWorking) pageToCheck = lastWorking + 1;
        }

        QString urlToPage = url + "?page=" + QString::number(pageToCheck);
        bool pageExists = Utils::CheckIfPageExists(urlToPage,  "www.imperiumtapet.com", "http://www.imperiumtapet.com");

        if (pageExists)
        {
            lastWorking = pageToCheck;
        }
        else
        {
            if (lastNotWorking == -1 || pageToCheck < lastNotWorking)
            {
                lastNotWorking = pageToCheck;
            }
        }

    }

    // cache in dictionary
    _numberOfPages[url] = lastWorking;

    return lastWorking;
}
