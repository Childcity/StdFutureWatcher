QT -= gui

CONFIG += c++1z c++17 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../src/StdFutureWatcher.pri)

SOURCES += \
        main.cpp
