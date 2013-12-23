#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T19:17:57
#
#-------------------------------------------------

QT       += core gui widgets quick

TARGET = Tapeciarnia
TEMPLATE = app

TRANSLATIONS = translations/Tapeciarnia_pl_PL.ts

SOURCES += main.cpp \
    TrayIcon.cpp \
    Providers/WallpapersWideProvider.cpp \
    System/Desktop.cpp \
    ProvidersManager.cpp

HEADERS  += \
    TrayIcon.h \
    ViewModels/SettingsViewModel.h \
    ViewModels/SourceViewModel.h \
    TapeciarniaQMLWindow.h \
    Providers/IWallpaperProvider.h \
    Providers/WallpapersWideProvider.h \
    ProvidersManager.h \
    System/Desktop.h

FORMS    +=

#INCLUDEPATH += d:\Uzytkowe\dev\libs\mingw-x86\libxml2\include\libxml2\

LIBS += -lgdiplus

OTHER_FILES += \
	images/tray_icon_loading.png \
	images/tray_icon.png \
    translations/Tapeciarnia_pl_PL.ts \
	translations/Tapeciarnia_pl_PL.qm \
	views/config.qml \
    views/edit_source_dialog.qml \
    views/confirm_delete_dialog.qml \
    views/add_new_dialog.qml

# install files

InstallViewFiles.path = $${OUT_PWD}/views
InstallViewFiles.files += views/*.qml

InstallTranslationFiles.path = $${OUT_PWD}/translations
InstallTranslationFiles.files += translations/*.ts
InstallTranslationFiles.files += translations/*.qm

InstallImageFiles.path = $${OUT_PWD}/images
InstallImageFiles.files += images/*.png

INSTALLS += InstallViewFiles InstallTranslationFiles InstallImageFiles
