TEMPLATE = app
CONFIG += console c++17

QT += \
        widgets

SOURCES += \
        sources/Card.cpp \
        sources/Monstercard.cpp \
        sources/Spellcard.cpp \
        sources/Trapcard.cpp \
        sources/main.cpp \
        sources/Game.cpp \
        sources/Player.cpp 

HEADERS += \
    headers/Card.h \
    headers/Monstercard.h \
    headers/Spellcard.h \
    headers/Trapcard.h \
    headers/Game.h \
    headers/Player.h

RESOURCES += \
        resources.qrc

