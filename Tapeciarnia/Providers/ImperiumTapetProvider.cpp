#include "ImperiumTapetProvider.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QRegExp>
#include <cmath>

QString ImperiumTapetProvider::GetMainPageUrl()
{
    return "http://imperiumtapet.pl/";
}

bool ImperiumTapetProvider::IsAddressSupported(const QString &url)
{
    if (url.startsWith("http://imperiumtapet.pl/") || url.startsWith("https://imperiumtapet.pl/"))
    {
        return true;
    }
    return false;
}

WallpaperResult ImperiumTapetProvider::DownloadRandomImage(WallpaperParameters parameters)
{
    return WallpaperResult();
}

