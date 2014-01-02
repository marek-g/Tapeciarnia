#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QList>
#include <QSize>
#include <QString>

class Utils
{
public:

    static QSize ChooseBestResolution(const QList<QSize> &resolutions, int screenWidth, int screenHeight);
    static QByteArray GetDataFromUrl(const QString &url, const QByteArray &host, const QByteArray &referer);

};

#endif // UTILS_H
