#include "TapetyTJAProvider.h"
#include "Utils.h"

#include <QRegExp>
#include <QTextCodec>

QString TapetyTJAProvider::GetMainPageUrl()
{
    return "http://tapety.tja.pl/";
}

bool TapetyTJAProvider::IsAddressSupported(const QString &url)
{
    if (url.startsWith("http://tapety.tja.pl/") || url.startsWith("https://tapety.tja.pl/"))
    {
        return true;
    }
    return false;
}

WallpaperResult TapetyTJAProvider::DownloadRandomImage(WallpaperParameters parameters)
{
    QString url = parameters.url + "?st=los";

    // download page
    QByteArray page1 = Utils::GetDataFromUrl(url, "tapety.tja.pl", "http://tapety.tja.pl");
    QTextCodec *codec = QTextCodec::codecForName("iso-8859-2");
    QString strPage1 = codec->toUnicode(page1);

    // find address of the first image
    QRegExp rxImageLink("<a title='([^'']*)' href='tapeta_(\\d+)\\.html'");
    if (rxImageLink.indexIn(strPage1, 0) == -1)
    {
        // not found
        return WallpaperResult();
    }

    WallpaperResult result;
    result.name = Utils::UnescapeHtml(rxImageLink.cap(1));
    result.url = QString("http://tapety.tja.pl/tapeta_") + rxImageLink.cap(2) + ".html";
    result.image = Utils::GetDataFromUrl("http://tapety.tja.pl/obrazki/tja_normalne/" + rxImageLink.cap(2) + ".jpg",
                                         "tapety.tja.pl", "http://tapety.tja.pl");

    return result;
}
