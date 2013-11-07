#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include <QApplication>
#include <QList>
#include <QQmlListProperty>
#include <QSettings>

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

    void loadFromFile() {
        QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);

        _changeEveryMinutes = settings.value("ChangeEveryMinutes", 30).toInt();

        _sources.clear();
        int size = settings.beginReadArray("sources");
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            _sources.append(new SourceViewModel(
                                settings.value("url").toString(),
                                settings.value("weight").toInt(),
                                settings.value("description").toString()));
        }
        settings.endArray();
    }

    void saveToFile() {
        QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);

        settings.setValue("ChangeEveryMinutes", _changeEveryMinutes);

        settings.beginWriteArray("sources", _sources.length());
        for (int i = 0; i < _sources.length(); i++) {
            settings.setArrayIndex(i);
            settings.setValue("url", _sources.at(i)->Url());
            settings.setValue("weight", _sources.at(i)->Weight());
            settings.setValue("description", _sources.at(i)->Description());
        }
        settings.endArray();
    }


signals:

    void SourcesChanged();
    void ChangeEveryMinutesChanged();

private:

    QList<SourceViewModel*> _sources;
    int _changeEveryMinutes;

};

#endif // SETTINGSVIEWMODEL_H
