#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QString>

class Utils
{
public:

    static QByteArray GetDataFromUrl(const QString &url, const QByteArray &host, const QByteArray &referer);

};

#endif // UTILS_H
