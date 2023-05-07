cmake_minimum_required(VERSION 3.16)

project(Yugioh VERSION 1.0 LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Set the compile flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")

# Export the compile commands automatically
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set INCLUDE_CURRENT_DIR to ON so it can find the files easier:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Automatically solve qt's vtable and moc errors:
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Multimedia Network Widgets)

set(HeadersPath "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(SourcesPath "${CMAKE_CURRENT_SOURCE_DIR}/sources")

# Headers
set(Headers
    "${HeadersPath}/BotPlayer.h"
    "${HeadersPath}/Card.h"
    "${HeadersPath}/CardList.h"
    "${HeadersPath}/CardMenu.h"
    "${HeadersPath}/Deck.h"
    "${HeadersPath}/DeckSettings.h"
    "${HeadersPath}/EffectActivator.h"
    "${HeadersPath}/EffectRequirement.h"
    "${HeadersPath}/Field.h"
    "${HeadersPath}/FieldZone.h"
    "${HeadersPath}/Game.h"
    "${HeadersPath}/GamePhase.h"
    "${HeadersPath}/GameSettings.h"
    "${HeadersPath}/Graveyard.h"
    "${HeadersPath}/Hand.h"
    "${HeadersPath}/MonsterZone.h"
    "${HeadersPath}/Monstercard.h"
    "${HeadersPath}/Player.h"
    "${HeadersPath}/Serializer.h"
    "${HeadersPath}/SpellTrapZone.h"
    "${HeadersPath}/Spellcard.h"
    "${HeadersPath}/Trapcard.h"
    "${HeadersPath}/Zone.h"
    "${HeadersPath}/mainmenu.h"
    "${HeadersPath}/ui_decksettings.h"
    "${HeadersPath}/ui_mainmenu.h"
    "${HeadersPath}/ui_mainwindow.h"
    "${SourcesPath}/profilesettings.h"
)

# Sources
set(Sources
    "${SourcesPath}/BotPlayer.cpp"
    "${SourcesPath}/Card.cpp"
    "${SourcesPath}/CardList.cpp"
    "${SourcesPath}/CardMenu.cpp"
    "${SourcesPath}/Deck.cpp"
    "${SourcesPath}/DeckSettings.cpp"
    "${SourcesPath}/EffectActivator.cpp"
    "${SourcesPath}/EffectRequirement.cpp"
    "${SourcesPath}/Field.cpp"
    "${SourcesPath}/FieldZone.cpp"
    "${SourcesPath}/Game.cpp"
    "${SourcesPath}/GamePhase.cpp"
    "${SourcesPath}/GameSettings.cpp"
    "${SourcesPath}/Graveyard.cpp"
    "${SourcesPath}/Hand.cpp"
    "${SourcesPath}/MonsterZone.cpp"
    "${SourcesPath}/Monstercard.cpp"
    "${SourcesPath}/Player.cpp"
    "${SourcesPath}/Serializer.cpp"
    "${SourcesPath}/SpellTrapZone.cpp"
    "${SourcesPath}/Spellcard.cpp"
    "${SourcesPath}/Trapcard.cpp"
    "${SourcesPath}/Zone.cpp"
    "${SourcesPath}/main.cpp"
    "${SourcesPath}/mainmenu.cpp"
    "${SourcesPath}/profilesettings.cpp"
)

# Forms
set(Forms
    "${SourcesPath}/decksettings.ui"
    "${SourcesPath}/GameSettings.ui"
    "${SourcesPath}/mainmenu.ui"
    "${SourcesPath}/mainwindow.ui"
    "${SourcesPath}/profilesettings.ui"
)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/forms")

# Resources
set(CMAKE_AUTORCC ON)
set(Resources "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc")

add_executable(Yugioh ${Sources} ${Headers} ${Forms} ${Resources})

target_link_libraries(Yugioh
    Qt::Core
    Qt::Gui
    Qt::Multimedia
    Qt::Network
    Qt::Widgets
)
