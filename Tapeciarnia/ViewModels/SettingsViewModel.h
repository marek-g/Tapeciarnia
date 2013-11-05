#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include <QList>

class SettingsViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> Sources READ Sources WRITE setSources NOTIFY SourcesChanged)

public:

    QList<QObject*> Sources() { return _sources; }

    void setSources(QList<QObject*> &sources) {
        if (_sources != sources) {
            _sources = sources;
            SourcesChanged();
        }
    }

signals:

    void SourcesChanged();

private:

    QList<QObject*> _sources;

};

#endif // SETTINGSVIEWMODEL_H
