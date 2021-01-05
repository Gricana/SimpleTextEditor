QT       += core gui
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    searchdialog.cpp \
    settingsdialog.cpp

HEADERS += \
    mainwindow.h \
    searchdialog.h \
    settingsdialog.h

FORMS += \
    mainwindow.ui \
    searchdialog.ui \
    settingsdialog.ui

MAJ_VERSION = 1
MIN_VERSION = 0
DEFINES +=\
    MAJ_VERSION=$$MAJ_VERSION \
    MIN_VERSION=$$MIN_VERSION

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


