#include "Utils.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QByteArray Utils::GetDataFromUrl(const QString &url, const QByteArray &host, const QByteArray &referer)
{
    QNetworkAccessManager networkManager;

    QNetworkRequest request(url);

    request.setRawHeader("Host", host);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "en-us,en;q=0.7,pl;q=0.3");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate");
    request.setRawHeader("DNT", "1");
    request.setRawHeader("Referer", referer);

    QNetworkReply *reply = networkManager.get(request);

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    return reply->readAll();
}
