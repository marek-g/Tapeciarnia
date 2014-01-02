#include "WallpapersWideProvider.h"
#include "Utils.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QRegExp>
#include <cmath>

QString WallpapersWideProvider::GetMainPageUrl()
{
    return "http://wallpaperswide.com/";
}

bool WallpapersWideProvider::IsAddressSupported(const QString &url)
{
    if (url.startsWith("http://wallpaperswide.com/") || url.startsWith("https://wallpaperswide.com/"))
    {
        return true;
    }
    return false;
}

WallpaperResult WallpapersWideProvider::DownloadRandomImage(WallpaperParameters parameters)
{
    QString strData = GetRandomPage(parameters.url);
    return GetRandomWallpaper(parameters, strData);
}

QString WallpapersWideProvider::GetRandomPage(const QString &url)
{
    // get first page
    QByteArray data = Utils::GetDataFromUrl(url, "wallpaperswide.com", "http://wallpaperswide.com");
    QString strData(data);

    // find number of pages
    int numberOfPages = 0;
    QRegExp rxPageNumber("/page/(\\d+)\">");
    int pos = 0;
    while ((pos = rxPageNumber.indexIn(strData, pos)) != -1)
    {
        int page = rxPageNumber.cap(1).toInt();
        if (page > numberOfPages) numberOfPages = page;
        pos += rxPageNumber.matchedLength();
    }

    // get random page
    if (numberOfPages > 0)
    {
        int randomPage = (_randomGenerator.get() % numberOfPages) + 1;
        QString randomUrl = url;
        randomUrl.remove(".html");
        randomUrl.append("/page/");
        randomUrl.append(QString::number(randomPage));

        data = Utils::GetDataFromUrl(randomUrl, "wallpaperswide.com", "http://wallpaperswide.com");
        strData = QString::fromUtf8(data.data());
    }

    return strData;
}

WallpaperResult WallpapersWideProvider::GetRandomWallpaper(WallpaperParameters parameters, const QString &page)
{
    WallpaperResult result;

    QRegExp rxBeginImage("<div class=\"thumb\">");

    // find number of images
    int numberOfImages = 0;
    int pos = 0;
    while ((pos = rxBeginImage.indexIn(page, pos)) != -1)
    {
        numberOfImages++;
        pos += rxBeginImage.matchedLength();
    }

    if (numberOfImages == 0)
    {
        return result;
    }

    // rand image number
    int randomImageNumber = (_randomGenerator.get() % numberOfImages) + 1;

    // get pos of random image
    pos = 0;
    int n = 0;
    while ((pos = rxBeginImage.indexIn(page, pos)) != -1)
    {
        n++;
        if (n == randomImageNumber) break;
        pos += rxBeginImage.matchedLength();
    }

    // read image data
    QRegExp rxImageData("<a href=\"/([^\\.]*)\\.html\" title=\"([^\"]*)\"");
    if (rxImageData.indexIn(page, pos) != -1)
    {
        QString href = rxImageData.cap(1);
        QString name = rxImageData.cap(2);

        // better name
        QRegExp rxName("<h1>([^<]*)<");
        if (rxName.indexIn(page, pos) != -1)
        {
            name = rxName.cap(1);
        }

        if (href.endsWith("wallpapers"))
        {
            QString bestResolutionUrl = GetBestImageUrl(parameters, href);
            if (bestResolutionUrl == 0)
            {
                return result;
            }

            result.name = name;
            result.url = QString("http://wallpaperswide.com/") +
                    href + QString(".html");
            result.image = Utils::GetDataFromUrl(bestResolutionUrl, "wallpaperswide.com", "http://wallpaperswide.com");
        }
    }

    return result;
}

QString WallpapersWideProvider::GetBestImageUrl(WallpaperParameters parameters, QString imageName)
{
    QString resolutionsUrl = QString("http://wallpaperswide.com/") +
            imageName + QString(".html");
    QByteArray data = Utils::GetDataFromUrl(resolutionsUrl, "wallpaperswide.com", "http://wallpaperswide.com");
    QString strData(data);

    // remove 's' from end of the name ("-wallpapers")
    if (imageName.endsWith("wallpapers"))
    {
        imageName.remove(imageName.length() - 1, 1);
    }

    // iterate through resolutions
    QList<QSize> listOfResolutions;
    QRegExp rxResolution(QRegExp::escape(imageName) + "-(\\d+)x(\\d+).jpg\"");
    int pos = 0;
    while ((pos = rxResolution.indexIn(strData, pos)) != -1)
    {
        int width = rxResolution.cap(1).toInt();
        int height = rxResolution.cap(2).toInt();
        pos += rxResolution.matchedLength();

        listOfResolutions.push_back(QSize(width, height));
    }

    QSize bestResolution = Utils::ChooseBestResolution(listOfResolutions, parameters.prefferedWidth, parameters.prefferedHeight);

    return QString("http://wallpaperswide.com/download/") +
            imageName +
            QString("-") +
            QString::number(bestResolution.width()) +
            QString("x") +
            QString::number(bestResolution.height()) +
            QString(".jpg");
}
