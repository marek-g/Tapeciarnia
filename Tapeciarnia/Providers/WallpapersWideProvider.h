#ifndef WALLPAPERSWIDEPROVIDER_H
#define WALLPAPERSWIDEPROVIDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

#include "IWallpaperProvider.h"

class WallpapersWideProvider : public QObject, IWallpaperProvider
{
    Q_OBJECT

    virtual ~WallpapersWideProvider() { }

    virtual QString GetMainPageUrl()
    {
        return "http://wallpaperswide.com/";
    }

    virtual bool IsAddressSupported(const QString &url)
    {
        if (url.startsWith("http://wallpaperswide.com/") || url.startsWith("https://wallpaperswide.com/"))
        {
            return true;
        }
        return false;
    }

    virtual WallpaperResult DownloadRandomImage(WallpaperParameters parameters)
    {
        QByteArray data = GetDataFromUrl(parameters.url);
        QString strData(data);
        int len = strData.length();

        //tinyxml2::XMLDocument doc;
        //doc.Parse(data.data());

        /*QWebPage page;
        page.mainFrame()->setHtml("<html></html>");
        int children = page.mainFrame()->children().size();*/


        //page.mainFrame()->setHtml(strData);
        //page.mainFrame()->setUrl(QUrl(parameters.url));
        /*int children = page.mainFrame()->children().size();
        QWebElement htmlElement = page.mainFrame()->findFirstElement("title");
        if (htmlElement.isNull())
        {
            int i = 0;
        }*/

        return WallpaperResult();
    }

private:

    QByteArray GetDataFromUrl(QString &url)
    {
        QNetworkAccessManager networkManager;

        QNetworkRequest request(url);
        QNetworkReply *reply = networkManager.get(request);

        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec();

        return reply->readAll();
    }
};

#endif // WALLPAPERSWIDEPROVIDER_H
