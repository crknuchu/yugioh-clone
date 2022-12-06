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
        sources/CardList.cpp \
        sources/Deck.cpp \
        sources/Graveyard.cpp \
        sources/Hand.cpp \
        sources/Player.cpp \
        sources/CardMenu.cpp

HEADERS += \
    headers/Card.h \
    headers/Monstercard.h \
    headers/Spellcard.h \
    headers/Trapcard.h \
    headers/Game.h \
    headers/CardList.h \
    headers/Deck.h \
    headers/Graveyard.h \
    headers/Hand.h \
    headers/Player.h \
    headers/ui_mainwindow.h \
    headers/CardMenu.h

RESOURCES += \
        resources.qrc

FORMS += \
    sources/mainwindow.ui


