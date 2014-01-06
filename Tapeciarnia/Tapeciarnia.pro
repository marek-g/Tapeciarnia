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
    ProvidersManager.cpp \
    Providers/ImperiumTapetProvider.cpp \
    Providers/Utils.cpp \
    System/Desktop_win32.cpp \
    System/Desktop_generic.cpp \
    Providers/TapetyTJAProvider.cpp

HEADERS  += \
    TrayIcon.h \
    ViewModels/SettingsViewModel.h \
    ViewModels/SourceViewModel.h \
    TapeciarniaQMLWindow.h \
    Providers/IWallpaperProvider.h \
    Providers/WallpapersWideProvider.h \
    ProvidersManager.h \
    System/Desktop.h \
    RandomGenerator.h \
    Providers/ImperiumTapetProvider.h \
    Providers/Utils.h \
    Providers/TapetyTJAProvider.h

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

CONFIG(debug,debug|release) {
    InstallViewFiles.path = $${OUT_PWD}/debug/views
    InstallTranslationFiles.path = $${OUT_PWD}/debug/translations
    InstallImageFiles.path = $${OUT_PWD}/debug/images
} else {
    InstallViewFiles.path = $${OUT_PWD}/release/views
    InstallTranslationFiles.path = $${OUT_PWD}/release/translations
    InstallImageFiles.path = $${OUT_PWD}/release/images
}

InstallViewFiles.files += views/*.qml

InstallTranslationFiles.files += translations/*.ts
InstallTranslationFiles.files += translations/*.qm

InstallImageFiles.files += images/*.png

INSTALLS += InstallViewFiles InstallTranslationFiles InstallImageFiles
