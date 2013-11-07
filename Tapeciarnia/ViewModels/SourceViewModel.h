#ifndef SOURCEVIEWMODEL_H
#define SOURCEVIEWMODEL_H

#include <QObject>

class SourceViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString Url READ Url WRITE setUrl NOTIFY UrlChanged)
    Q_PROPERTY(int Weight READ Weight WRITE setWeight NOTIFY WeightChanged)
    Q_PROPERTY(QString Description READ Description WRITE setDescription NOTIFY DescriptionChanged)

public:

    SourceViewModel() { }

    SourceViewModel(const QString &url, int weight, const QString &description) :
        _url(url), _weight(weight), _description(description)
    {
    }

    QString Url() { return _url; }

    void setUrl(QString url) {
        if (_url != url) {
            _url = url;
            UrlChanged();
        }
    }

    int Weight() { return _weight; }

    void setWeight(int weight) {
        if (_weight != weight) {
            _weight = weight;
            WeightChanged();
        }
    }

    QString Description() { return _description; }

    void setDescription(QString description) {
        if (_description != description) {
            _description = description;
            DescriptionChanged();
        }
    }

signals:

    void UrlChanged();
    void WeightChanged();
    void DescriptionChanged();

private:

    QString _url;
    int _weight;
    QString _description;
};

#endif // SOURCEVIEWMODEL_H
