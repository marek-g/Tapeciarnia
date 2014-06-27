#ifndef SETTINGSVIEWMODEL_H
#define SETTINGSVIEWMODEL_H

#include <QObject>
#include <QApplication>
#include <QList>
#include <QQmlListProperty>
#include <QSettings>

#include "../TrayIcon.h"
#include "SourceViewModel.h"

//class TrayIcon;

class SettingsViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<SourceViewModel> Sources READ Sources NOTIFY SourcesChanged)
    Q_PROPERTY(int ChangeEveryMinutes READ ChangeEveryMinutes WRITE setChangeEveryMinutes NOTIFY ChangeEveryMinutesChanged)

public:

    SettingsViewModel() :
        _trayIcon(0),
        _changeEveryMinutes(30)
    { }

    void SetTrayIcon(TrayIcon *trayIcon) { _trayIcon = trayIcon; }

    QList<SourceViewModel*> & GetSources() { return _sources; }

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

    Q_INVOKABLE void addNewSource(bool enabled, const QString &url, int weight, const QString &description) {
        _sources.append(new SourceViewModel(enabled, url, weight, description));
        SourcesChanged();
    }

    Q_INVOKABLE void deleteSource(int index) {
        _sources.removeAt(index);
        SourcesChanged();
    }

    Q_INVOKABLE void acceptSettings() {
        saveToFile();
        if (_trayIcon != 0) {
            _trayIcon->toggleConfigView();
        }
    }

    Q_INVOKABLE void cancelSettings() {
        loadFromFile();
        if (_trayIcon != 0) {
            _trayIcon->toggleConfigView();
        }
    }

    void loadFromFile() {
        QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);

        _changeEveryMinutes = settings.value("ChangeEveryMinutes", 30).toInt();
        ChangeEveryMinutesChanged();

        _sources.clear();
        int size = settings.beginReadArray("sources");
        for (int i = 0; i < size; i++) {
            settings.setArrayIndex(i);
            _sources.append(new SourceViewModel(
                                !settings.value("disabled").toBool(),
                                settings.value("url").toString(),
                                settings.value("weight").toInt(),
                                settings.value("description").toString()));
        }
        settings.endArray();
        SourcesChanged();
    }

    void saveToFile() {
        QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);

        settings.setValue("ChangeEveryMinutes", _changeEveryMinutes);

        settings.beginWriteArray("sources", _sources.length());
        for (int i = 0; i < _sources.length(); i++) {
            settings.setArrayIndex(i);
            settings.setValue("disabled", !_sources.at(i)->Enabled());
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

    TrayIcon *_trayIcon;

    QList<SourceViewModel*> _sources;
    int _changeEveryMinutes;

};

#endif // SETTINGSVIEWMODEL_H
