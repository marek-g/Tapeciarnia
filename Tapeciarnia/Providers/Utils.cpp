#include "Utils.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QSize Utils::ChooseBestResolution(const QList<QSize> &resolutions, int screenWidth, int screenHeight)
{
    QSize bestResolution(0, 0);

    for (int i = 0; i < resolutions.count(); i++)
    {
        int width = resolutions[i].width();
        int height = resolutions[i].height();

        // first resolution is as good as any other
        if (bestResolution.width() == 0 || bestResolution.height() == 0)
        {
            bestResolution.setWidth(width);
            bestResolution.setHeight(height);

            continue;
        }

        double aspectDiff = std::abs((width*1.0) / height - (screenWidth*1.0) / screenHeight);
        double bestAspectDiff = std::abs((bestResolution.width()*1.0) / bestResolution.height() -
                                         (screenWidth*1.0) / screenHeight);

        // skip resolutions with worst aspect than found so far
        if (aspectDiff > bestAspectDiff)
        {
            continue;
        }

        if (width >= screenWidth && height >= screenHeight)
        {
            if (bestResolution.width() >= screenWidth && bestResolution.height() >= screenHeight)
            {
                if (width*height < bestResolution.width()*bestResolution.height())
                {
                    bestResolution.setWidth(width);
                    bestResolution.setHeight(height);
                }
            }
            else
            {
                bestResolution.setWidth(width);
                bestResolution.setHeight(height);
            }
        }
        else
        {
            if (width*height > bestResolution.width()*bestResolution.height() &&
                width <= screenWidth && height <= screenHeight)
            {
                bestResolution.setWidth(width);
                bestResolution.setHeight(height);
            }
        }
    }

    return bestResolution;
}

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
