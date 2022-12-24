TEMPLATE = app
CONFIG += console c++17

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

QT +=   widgets \
        multimedia

SOURCES += \
        sources/BotPlayer.cpp \
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
        sources/Graveyard.cpp \
        sources/Hand.cpp \
        sources/Player.cpp \
        sources/CardMenu.cpp \
        sources/MonsterZone.cpp  \
        sources/profilesettings.cpp \
        sources/Serializer.cpp

HEADERS += \
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
    headers/Graveyard.h \
    headers/Hand.h \
    headers/Player.h \
    headers/CardMenu.h \ 
    headers/MonsterZone.h \
    headers/mainmenu.h \
    headers/Zone.h \
    headers/ui_mainwindow.h \
    headers/ui_mainmenu.h \
    headers/CardMenu.h \  \
    sources/profilesettings.h \
    headers/MonsterZone.h \
    headers/mainmenu.h \
    headers/Zone.h \
    sources/BotPlayer.h \
    headers/Serializer.h

RESOURCES += \
        resources.qrc

FORMS += \
    sources/GameSettings.ui \
    sources/mainmenu.ui \
    sources/mainwindow.ui \
    sources/profilesettings.ui


