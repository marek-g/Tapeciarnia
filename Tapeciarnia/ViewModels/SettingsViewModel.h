#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>

#include "SourceViewModel.h"

class SettingsViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SourceViewModel> Sources READ Sources NOTIFY SourcesChanged)
    Q_PROPERTY(int ChangeEveryMinutes READ ChangeEveryMinutes WRITE setChangeEveryMinutes NOTIFY ChangeEveryMinutesChanged)

public:

    SettingsViewModel() :
        _changeEveryMinutes(30)
    { }

    QQmlListProperty<SourceViewModel> Sources() { return QQmlListProperty<SourceViewModel>(this, _sources); }

    void setSources(QList<SourceViewModel*> &sources) {
        if (_sources != sources) {
            _sources = sources;
            SourcesChanged();
        }
    }

    int ChangeEveryMinutes() {
        return _changeEveryMinutes;
    }

    void setChangeEveryMinutes(int changeEveryMinutes) {
        if (_changeEveryMinutes != changeEveryMinutes) {
            _changeEveryMinutes = changeEveryMinutes;
            ChangeEveryMinutesChanged();
        }
    }

    Q_INVOKABLE void addNewSource(const QString &url, int weight, const QString &description) {
        _sources.append(new SourceViewModel(url, weight, description));
        SourcesChanged();
    }

    Q_INVOKABLE void deleteSource(int index) {
        _sources.removeAt(index);
        SourcesChanged();
    }

signals:

    void SourcesChanged();
    void ChangeEveryMinutesChanged();

private:

    QList<SourceViewModel*> _sources;
    int _changeEveryMinutes;

};

#endif // SETTINGSVIEWMODEL_H
