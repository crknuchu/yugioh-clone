TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        sources/Card.cpp \
        sources/Monstercard.cpp \
        sources/Spellcard.cpp \
        sources/Trapcard.cpp \
        sources/main.cpp

HEADERS += \
    headers/Card.h \
    headers/Monstercard.h \
    headers/Spellcard.h \
    headers/Trapcard.h

