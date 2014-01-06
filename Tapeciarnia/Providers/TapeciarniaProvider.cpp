#include "TapeciarniaProvider.h"
#include "Utils.h"

#include <QRegExp>
#include <QTextCodec>

QString TapeciarniaProvider::GetMainPageUrl()
{
    return "http://www.tapeciarnia.pl/";
}

bool TapeciarniaProvider::IsAddressSupported(const QString &url)
{
    if (url.startsWith("http://www.tapeciarnia.pl/") || url.startsWith("https://www.tapeciarnia.pl/"))
    {
        return true;
    }
    return false;
}

WallpaperResult TapeciarniaProvider::DownloadRandomImage(WallpaperParameters parameters)
{
    QString url = parameters.url + "?st=los";

    // download page
    QByteArray page1 = Utils::GetDataFromUrl(url, "www.tapeciarnia.pl", "http://www.tapeciarnia.pl");
    QTextCodec *codec = QTextCodec::codecForName("iso-8859-2");
    QString strPage1 = codec->toUnicode(page1);

    // find address of the first image
    //QRegExp rxImageLink("<a href='([^.]*)\\.html' title='([^']*)'><img +tresc='");
    QRegExp rxImageLink("<img +tresc='[^']*' src='tapety/srednie/([^.]*)\\.jpg' alt='([^']*)'");
    if (rxImageLink.indexIn(strPage1, 0) == -1)
    {
        // not found
        return WallpaperResult();
    }

    WallpaperResult result;
    result.name = Utils::UnescapeHtml(rxImageLink.cap(2));
    result.url = QString("http://www.tapeciarnia.pl/") + rxImageLink.cap(1) + ".html";
    result.image = Utils::GetDataFromUrl("http://www.tapeciarnia.pl/tapety/normalne/" + rxImageLink.cap(1) + ".jpg",
                                         "www.tapeciarnia.pl", "http://www.tapeciarnia.pl");

    return result;
}
