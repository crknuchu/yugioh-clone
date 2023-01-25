TEMPLATE = app
CONFIG += console c++17
QMAKE_CXXFLAGS += -O0 -g -ggdb -Wall -Wextra
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

QT +=   widgets \
        multimedia \
        network

SOURCES += \
        sources/BotPlayer.cpp \
        sources/EffectRequirement.cpp \
        sources/Field.cpp \
        sources/FieldZone.cpp \
        sources/GameSettings.cpp \
        sources/mainmenu.cpp \
        sources/Card.cpp \
        sources/EffectActivator.cpp \
        sources/GamePhase.cpp \
        sources/Monstercard.cpp \
        sources/SpellTrapZone.cpp \
        sources/Spellcard.cpp \
        sources/Trapcard.cpp \
        sources/Zone.cpp \
        sources/main.cpp \
        sources/Game.cpp \
        sources/CardList.cpp \
        sources/Deck.cpp \
        sources/DeckSettings.cpp \
        sources/Graveyard.cpp \
        sources/Hand.cpp \
        sources/Player.cpp \
        sources/CardMenu.cpp \
        sources/MonsterZone.cpp  \
        sources/profilesettings.cpp \
        sources/Serializer.cpp \
#        tests/tests/tests.cpp \
#        tests/tests/catch.cpp

HEADERS += \
    headers/EffectRequirement.h \
    headers/Field.h \
    headers/FieldZone.h \
    headers/GameSettings.h \
    headers/Card.h \
    headers/EffectActivator.h \
    headers/GamePhase.h \
    headers/Monstercard.h \
    headers/SpellTrapZone.h \
    headers/Spellcard.h \
    headers/Trapcard.h \
    headers/Game.h \
    headers/CardList.h \
    headers/Deck.h \
    headers/DeckSettings.h \
    headers/Graveyard.h \
    headers/Hand.h \
    headers/Player.h \
    headers/CardMenu.h \ 
    headers/MonsterZone.h \
    headers/mainmenu.h \
    headers/Zone.h \
    headers/ui_mainwindow.h \
    headers/ui_mainmenu.h \
    headers/ui_decksettings.h \
    headers/CardMenu.h \ 
    sources/profilesettings.h \
    headers/MonsterZone.h \
    headers/BotPlayer.h \
    headers/Serializer.h \
#    tests/catch.hpp


RESOURCES += \
        resources.qrc

FORMS += \
    sources/GameSettings.ui \
    sources/mainmenu.ui \
    sources/DeckSettings.ui \
    sources/mainwindow.ui \
    sources/profilesettings.ui


