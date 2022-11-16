TEMPLATE = app
CONFIG += console c++17

QT += \
        widgets

HEADERS += \
        headers/Game.h \
        headers/Card.h

SOURCES += \
        sources/Game.cpp \
        sources/main.cpp \
        sources/Card.cpp

RESOURCES += \
        resources.qrc
