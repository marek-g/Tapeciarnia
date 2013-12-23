#include "WallpapersWideProvider.h"

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
    QByteArray data = GetDataFromUrl(url);
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
        int randomPage = (qrand() % numberOfPages) + 1;
        QString randomUrl = url;
        randomUrl.remove(".html");
        randomUrl.append("/page/");
        randomUrl.append(QString::number(randomPage));

        data = GetDataFromUrl(randomUrl);
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
    int randomImageNumber = (qrand() % numberOfImages) + 1;

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
            result.image = GetDataFromUrl(bestResolutionUrl);
        }
    }

    return result;
}

QString WallpapersWideProvider::GetBestImageUrl(WallpaperParameters parameters, QString imageName)
{
    QString resolutionsUrl = QString("http://wallpaperswide.com/") +
            imageName + QString(".html");
    QByteArray data = GetDataFromUrl(resolutionsUrl);
    QString strData(data);

    // remove 's' from end of the name ("-wallpapers")
    if (imageName.endsWith("wallpapers"))
    {
        imageName.remove(imageName.length() - 1, 1);
    }

    // iterate through resolutions
    int bestWidth = 0;
    int bestHeight = 0;
    QRegExp rxResolution(QRegExp::escape(imageName) + "-(\\d+)x(\\d+).jpg\"");
    int pos = 0;
    while ((pos = rxResolution.indexIn(strData, pos)) != -1)
    {
        int width = rxResolution.cap(1).toInt();
        int height = rxResolution.cap(2).toInt();

        // first resolution is as good as any other
        if (bestWidth == 0 || bestHeight == 0)
        {
            bestWidth = width; bestHeight = height;

            pos += rxResolution.matchedLength();
            continue;
        }

        double aspectDiff = std::abs((width*1.0) / height - (parameters.prefferedWidth*1.0) / parameters.prefferedHeight);
        double bestAspectDiff = std::abs((bestWidth*1.0) / bestHeight - (parameters.prefferedWidth*1.0) / parameters.prefferedHeight);

        // skip resolutions with worst aspect than found so far
        if (aspectDiff > bestAspectDiff)
        {
            pos += rxResolution.matchedLength();
            continue;
        }

        if (width >= parameters.prefferedWidth &&
            height >= parameters.prefferedHeight)
        {
            if (bestWidth >= parameters.prefferedWidth &&
                bestHeight >= parameters.prefferedHeight)
            {
                if (width*height < bestWidth*bestHeight)
                {
                    bestWidth = width; bestHeight = height;
                }
            }
            else
            {
                bestWidth = width; bestHeight = height;
            }
        }
        else
        {
            if (width*height > bestWidth*bestHeight &&
                width <= parameters.prefferedWidth &&
                height <= parameters.prefferedHeight)
            {
                bestWidth = width; bestHeight = height;
            }
        }

        pos += rxResolution.matchedLength();
    }

    if (bestWidth == 0 || bestHeight == 0)
    {
        return 0;
    }

    return QString("http://wallpaperswide.com/download/") +
            imageName +
            QString("-") +
            QString::number(bestWidth) +
            QString("x") +
            QString::number(bestHeight) +
            QString(".jpg");
}

QByteArray WallpapersWideProvider::GetDataFromUrl(const QString &url)
{
    QNetworkAccessManager networkManager;

    QNetworkRequest request(url);

    request.setRawHeader("Host", "wallpaperswide.com");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "en-us,en;q=0.7,pl;q=0.3");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate");
    request.setRawHeader("DNT", "1");
    request.setRawHeader("Referer", "http://wallpaperswide.com");

    QNetworkReply *reply = networkManager.get(request);

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    return reply->readAll();
}
