#ifndef GAMEPHASE_H
#define GAMEPHASE_H

#include <map>
#include <QString>

enum class GamePhasesEnum {
  DRAW_PHASE,
  STANDBY_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

// Unnamed namespaces?

namespace GamePhase {
    extern const std::map<GamePhasesEnum, QString> gamePhaseToQString;

    extern GamePhasesEnum currentGamePhase;
}

#endif // GAMEPHASE_H
