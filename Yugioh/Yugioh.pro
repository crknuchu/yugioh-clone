TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    sources/Deck.cpp \
    sources/Hand.cpp \
    sources/main.cpp

HEADERS += \
    headers/CardList.h \
    headers/Deck.h \
    headers/Hand.h
