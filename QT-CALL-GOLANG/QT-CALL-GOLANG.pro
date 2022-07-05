QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



macx: LIBS += -L$$PWD/../build/mac/ -ldemo

INCLUDEPATH += $$PWD/../build/mac
DEPENDPATH += $$PWD/../build/mac

macx: PRE_TARGETDEPS += $$PWD/../build/mac/libdemo.a


win32: LIBS += -L$$PWD/../build/windows/ -llibdemo

INCLUDEPATH += $$PWD/../build/windows
DEPENDPATH += $$PWD/../build/windows

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../build/windows/libdemo.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../build/windows/liblibdemo.a
