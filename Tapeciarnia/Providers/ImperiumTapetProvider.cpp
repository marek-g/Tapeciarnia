#include "ImperiumTapetProvider.h"
#include "Utils.h"

#include <QApplication>
#include <QClipboard>
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
    return GetRandomWallpaper(parameters, strData);
}

QString ImperiumTapetProvider::GetRandomPage(const QString &url)
{
    QString strData;

    int numberOfPages = GetNumberOfPages(url);

    if (numberOfPages > 0)
    {
        int randomPage = (_randomGenerator.get() % numberOfPages) + 1;
        QString randomUrl = url + "?page=" + QString::number(randomPage);

        QByteArray data = Utils::GetDataFromUrl(randomUrl, "www.imperiumtapet.com", "http://www.imperiumtapet.com");
        strData = QString::fromUtf8(data.data());
    }

    return strData;
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
        bool pageExists = Utils::CheckIfPageExists(urlToPage, "www.imperiumtapet.com", "http://www.imperiumtapet.com");

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

WallpaperResult ImperiumTapetProvider::GetRandomWallpaper(WallpaperParameters parameters, const QString &page)
{
    (void) parameters;

    WallpaperResult result;

    // find image info on the page
    QList<QPair<QString, QString> > lstImageInfo;
    QRegExp rxImageInfo("<a href=\"/tapeta/([^/]*)/(\\d+)/\"");
    int pos = 0;
    while ((pos = rxImageInfo.indexIn(page, pos)) != -1)
    {
        QString name = rxImageInfo.cap(1);
        QString number = rxImageInfo.cap(2);
        lstImageInfo.push_back(QPair<QString, QString>(name, number));

        pos += rxImageInfo.matchedLength();
    }

    if (lstImageInfo.count() == 0)
    {
        return WallpaperResult();
    }

    // rand image
    int randomImageNumber = (_randomGenerator.get() % lstImageInfo.count());

    // download page with image link
    QByteArray pageWithImageLink = Utils::GetDataFromUrl(QString("http://www.imperiumtapet.com/tapeta/pokaz/") +
                                                         lstImageInfo[randomImageNumber].second + "/",
                                                         "www.imperiumtapet.com", "http://www.imperiumtapet.com");
    QString strPageWithImageLink(pageWithImageLink);

    // find image link on the page
    QRegExp rxImageLink("<img src=\"([^\"]*)\"");
    pos = 0;
    if (rxImageLink.indexIn(strPageWithImageLink, pos) == -1)
    {
        // not found
        return WallpaperResult();
    }

    QString nameFiltered = lstImageInfo[randomImageNumber].first;
    nameFiltered.replace("-", " ");

    result.name = Utils::UnescapeHtml(nameFiltered);
    result.url = QString("http://www.imperiumtapet.com/tapeta/") + lstImageInfo[randomImageNumber].first + "/" + lstImageInfo[randomImageNumber].second + "/";
    result.image = Utils::GetDataFromUrl("http://www.imperiumtapet.com" + rxImageLink.cap(1),
                                         "www.imperiumtapet.com", "http://www.imperiumtapet.com");

    return result;
}
