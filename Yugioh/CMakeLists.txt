cmake_minimum_required(VERSION 3.22)

project(Yugioh  VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Multimedia Network Widgets)

set(HeaderPath "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(SourcePath "${CMAKE_CURRENT_SOURCE_DIR}/sources")

#headers
set(Headers
    "${HeaderPath}/BotPlayer.h"
    "${HeaderPath}/Card.h"
    "${HeaderPath}/CardList.h"
    "${HeaderPath}/CardMenu.h"
    "${HeaderPath}/Deck.h"
    "${HeaderPath}/DeckSettings.h"
    "${HeaderPath}/EffectActivator.h"
    "${HeaderPath}/EffectRequirement.h"
    "${HeaderPath}/Field.h"
    "${HeaderPath}/FieldZone.h"
    "${HeaderPath}/Game.h"
    "${HeaderPath}/GamePhase.h"
    "${HeaderPath}/GameSettings.h"
    "${HeaderPath}/Graveyard.h"
    "${HeaderPath}/Hand.h"
    "${HeaderPath}/mainmenu.h"
    "${HeaderPath}/Monstercard.h"
    "${HeaderPath}/MonsterZone.h"
    "${HeaderPath}/Player.h"
    "${HeaderPath}/Serializer.h"
    "${HeaderPath}/Spellcard.h"
    "${HeaderPath}/SpellTrapZone.h"
    "${HeaderPath}/Trapcard.h"
    "${HeaderPath}/ui_decksettings.h"
    "${HeaderPath}/ui_mainmenu.h"
    "${HeaderPath}/ui_mainwindow.h"
    "${HeaderPath}/Zone.h"
    "${SourcePath}/profilesettings.h"
)

set(Sources
    "${SourcePath}/BotPlayer.cpp"
    "${SourcePath}/Card.cpp"
    "${SourcePath}/CardList.cpp"
    "${SourcePath}/CardMenu.cpp"
    "${SourcePath}/Deck.cpp"
    "${SourcePath}/DeckSettings.cpp"
    "${SourcePath}/EffectActivator.cpp"
    "${SourcePath}/EffectRequirement.cpp"
    "${SourcePath}/Field.cpp"
    "${SourcePath}/FieldZone.cpp"
    "${SourcePath}/Game.cpp"
    "${SourcePath}/GamePhase.cpp"
    "${SourcePath}/GameSettings.cpp"
    "${SourcePath}/Graveyard.cpp"
    "${SourcePath}/Hand.cpp"
    "${SourcePath}/mainmenu.cpp"
    "${SourcePath}/main.cpp"
    "${SourcePath}/Monstercard.cpp"
    "${SourcePath}/MonsterZone.cpp"
    "${SourcePath}/Player.cpp"
    "${SourcePath}/Serializer.cpp"
    "${SourcePath}/Spellcard.cpp"
    "${SourcePath}/SpellTrapZone.cpp"
    "${SourcePath}/Trapcard.cpp"
    "${SourcePath}/Zone.cpp"
    "${SourcePath}/profilesettings.cpp"
)

set(Forms
    "${SourcePath}/DeckSettings.ui"
    "${SourcePath}/GameSettings.ui"
    "${SourcePath}/mainmenu.ui"
    "${SourcePath}/mainwindow.ui"
    "${SourcePath}/profilesettings.ui"
)

set(Resources
    "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc"
)

add_executable(Yugioh ${Sources} ${Headers} ${Forms} ${Resources})

target_link_libraries(Yugioh 
    Qt::Widgets 
    Qt::Core 
    Qt::Network 
    Qt::Multimedia 
    Qt::Gui
)