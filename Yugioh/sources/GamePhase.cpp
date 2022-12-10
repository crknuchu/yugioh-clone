#include "headers/GamePhase.h"

const std::map<GamePhasesEnum, QString> GamePhase::gamePhaseToQString{
            {GamePhasesEnum::DRAW_PHASE,        "DRAW PHASE"},
            {GamePhasesEnum::STANDBY_PHASE,     "STANDBY PHASE"},
            {GamePhasesEnum::MAIN_PHASE1,       "MAIN PHASE 1"},
            {GamePhasesEnum::BATTLE_PHASE,      "BATTLE PHASE"},
            {GamePhasesEnum::MAIN_PHASE2,       "MAIN PHASE 2"},
            {GamePhasesEnum::END_PHASE,         "END PHASE"}
};

GamePhasesEnum GamePhase::currentGamePhase;
