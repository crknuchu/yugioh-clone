#include "headers/GamePhase.h"

std::map<GamePhasesEnum, QString> GamePhase::gamePhaseToQString{
            {GamePhasesEnum::DRAW_PHASE,        "DRAW PHASE"},
            {GamePhasesEnum::STANDBY_PHASE,     "STANDBY PHASE"},
            {GamePhasesEnum::MAIN_PHASE1,       "MAIN PHASE 1"},
            {GamePhasesEnum::BATTLE_PHASE,      "BATTLE PHASE"},
            {GamePhasesEnum::MAIN_PHASE2,       "MAIN PHASE 2"},
            {GamePhasesEnum::END_PHASE,         "END PHASE"}
};

std::map<QString, GamePhasesEnum> GamePhase::qStringToGamePhase{
            {"DRAW PHASE",GamePhasesEnum::DRAW_PHASE},
            {"STANDBY PHASE",GamePhasesEnum::STANDBY_PHASE},
            {"MAIN PHASE 1",GamePhasesEnum::MAIN_PHASE1},
            {"BATTLE PHASE",GamePhasesEnum::BATTLE_PHASE},
            {"MAIN PHASE 2",GamePhasesEnum::MAIN_PHASE2},
            {"END PHASE",GamePhasesEnum::END_PHASE}
};

GamePhasesEnum GamePhase::currentGamePhase;
