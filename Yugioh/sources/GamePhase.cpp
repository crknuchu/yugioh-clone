#include "headers/GamePhase.h"

const std::map<GamePhases, QString> GamePhaseExternVars::gamePhaseToQString{
            {GamePhases::DRAW_PHASE,        "DRAW PHASE"},
            {GamePhases::STANDBY_PHASE,     "STANDBY PHASE"},
            {GamePhases::MAIN_PHASE1,       "MAIN PHASE 1"},
            {GamePhases::BATTLE_PHASE,      "BATTLE PHASE"},
            {GamePhases::MAIN_PHASE2,       "MAIN PHASE 2"},
            {GamePhases::END_PHASE,         "END PHASE"}
};

GamePhases GamePhaseExternVars::currentGamePhase;
