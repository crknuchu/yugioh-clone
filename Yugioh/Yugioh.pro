TEMPLATE = app
CONFIG += console c++17

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

QT += \
        widgets

SOURCES += \
        sources/GameSettings.cpp \
        sources/mainmenu.cpp \
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
    headers/GameSettings.h \
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
    headers/CardMenu.h \
    headers/mainmenu.h

RESOURCES += \
        resources.qrc

FORMS += \
    sources/GameSettings.ui \
    sources/mainmenu.ui \
    sources/mainwindow.ui


