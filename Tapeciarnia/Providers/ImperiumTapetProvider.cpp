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

QByteArray ImperiumTapetProvider::GetDataFromUrl(const QString &url)
{
    QNetworkAccessManager networkManager;

    QNetworkRequest request(url);

    request.setRawHeader("Host", "imperiumtapet.pl");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "en-us,en;q=0.7,pl;q=0.3");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate");
    request.setRawHeader("DNT", "1");
    request.setRawHeader("Referer", "http://imperiumtapet.pl");

    QNetworkReply *reply = networkManager.get(request);

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    return reply->readAll();
}
