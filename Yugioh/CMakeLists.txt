cmake_minimum_required(VERSION 3.22.1)
project(YUGIOG VERSION 1.0.0 LANGUAGES CXX)

set(PROJECT_NAME Yugioh)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/sources")
set(headers_path "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(forms_path "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(CMAKE_PREFIX_PATH "/home/dusan/Qt/6.4.1/gcc_64/lib/cmake")
find_package(Qt6 COMPONENTS Core Widgets Multimedia REQUIRED)



set(source_headers
"${source_path}/BotPlayer.cpp"
"${source_path}/Card.cpp"
"${source_path}/CardList.cpp"
"${source_path}/CardMenu.cpp"
"${source_path}/Deck.cpp"
"${source_path}/DeckSettings.cpp"
"${source_path}/EffectActivator.cpp"
"${source_path}/EffectRequirement.cpp"
"${source_path}/Field.cpp"
"${source_path}/FieldZone.cpp"
"${source_path}/Game.cpp"
"${source_path}/GamePhase.cpp"
"${source_path}/GameSettings.cpp"
"${source_path}/Graveyard.cpp"
"${source_path}/Hand.cpp"
"${source_path}/main.cpp"
"${source_path}/mainmenu.cpp"
"${source_path}/Monstercard.cpp"
"${source_path}/MonsterZone.cpp"
"${source_path}/Player.cpp"
"${source_path}/profilesettings.cpp"
"${source_path}/Serializer.cpp"
"${source_path}/Spellcard.cpp"
"${source_path}/SpellTrapZone.cpp"
"${source_path}/Trapcard.cpp"
"${source_path}/Zone.cpp"
"${headers_path}/BotPlayer.h"
"${headers_path}/Card.h"
"${headers_path}/CardList.h"
"${headers_path}/CardMenu.h"
"${headers_path}/Deck.h"
"${headers_path}/DeckSettings.h"
"${headers_path}/EffectActivator.h"
"${headers_path}/EffectRequirement.h"
"${headers_path}/Field.h"
"${headers_path}/FieldZone.h"
"${headers_path}/Game.h"
"${headers_path}/GamePhase.h"
"${headers_path}/GameSettings.h"
"${headers_path}/Graveyard.h"
"${headers_path}/Hand.h"
"${headers_path}/mainmenu.h"
"${headers_path}/Monstercard.h"
"${headers_path}/MonsterZone.h"
"${headers_path}/Player.h"
"${source_path}/profilesettings.h"
"${headers_path}/Serializer.h"
"${headers_path}/Spellcard.h"
"${headers_path}/SpellTrapZone.h"
"${headers_path}/Trapcard.h"
"${headers_path}/ui_mainmenu.h"
"${headers_path}/ui_decksettings.h"
"${headers_path}/ui_mainwindow.h"
"${headers_path}/Zone.h"
)

set(forms
"${forms_path}/GameSettings.ui"
"${forms_path}/profilesettings.ui"
"${forms_path}/mainmenu.ui"
"${forms_path}/DeckSettings.ui"
"${forms_path}/mainwindow.ui"
)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${forms_path})  

set(resources "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc")

add_executable(${PROJECT_NAME} ${source_headers} ${forms} ${resources})
    
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets Qt6::Multimedia)
# target_link_libraries(${PROJECT_NAME}  yugioh_lib)