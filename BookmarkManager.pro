QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS = -std=c++11

SOURCES += \
    View/bookmarkiconprovider.cpp \
    View/favicondownloader.cpp \
    View/newbookmark.cpp \
    View/newfolder.cpp \
    main.cpp \
    View/mainwindow.cpp

HEADERS += \
    View/bookmarkiconprovider.h \
    View/favicondownloader.h \
    View/mainwindow.h \
    View/newbookmark.h \
    View/newfolder.h

FORMS += \
    View/mainwindow.ui \
    View/newbookmark.ui \
    View/newfolder.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    settings.json
