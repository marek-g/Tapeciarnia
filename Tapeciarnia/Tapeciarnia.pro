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
    TrayIcon.cpp

HEADERS  += \
    TrayIcon.h

FORMS    +=

OTHER_FILES += \
	images/tray_icon_loading.png \
	images/tray_icon.png \
    translations/Tapeciarnia_pl_PL.ts \
	translations/Tapeciarnia_pl_PL.qm \
	views/config.qml

# install files

InstallViewFiles.path = $${OUT_PWD}/views
InstallViewFiles.files += views/*.qml

InstallTranslationFiles.path = $${OUT_PWD}/translations
InstallTranslationFiles.files += translations/*.ts
InstallTranslationFiles.files += translations/*.qm

InstallImageFiles.path = $${OUT_PWD}/images
InstallImageFiles.files += images/*.png

INSTALLS += InstallViewFiles InstallTranslationFiles InstallImageFiles
