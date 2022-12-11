TEMPLATE = app
CONFIG += console c++17

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

QT += \
        widgets

SOURCES += \
        sources/Card.cpp \
        sources/MonsterZone.cpp \
        sources/Monstercard.cpp \
        sources/SpellTrapZone.cpp \
        sources/Spellcard.cpp \
        sources/Trapcard.cpp \
        sources/Zone.cpp \
        sources/main.cpp \
        sources/Game.cpp \
        sources/CardList.cpp \
        sources/Deck.cpp \
        sources/Graveyard.cpp \
        sources/Hand.cpp \
        sources/Player.cpp \
        sources/CardMenu.cpp

HEADERS += \
    headers/Card.h \
    headers/MonsterZone.h \
    headers/Monstercard.h \
    headers/SpellTrapZone.h \
    headers/Spellcard.h \
    headers/Trapcard.h \
    headers/Game.h \
    headers/CardList.h \
    headers/Deck.h \
    headers/Graveyard.h \
    headers/Hand.h \
    headers/Player.h \
    headers/CardMenu.h \
    headers/Zone.h

RESOURCES += \
        resources.qrc

FORMS += \
    sources/mainwindow.ui


