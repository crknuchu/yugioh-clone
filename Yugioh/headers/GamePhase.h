#ifndef GAMEPHASE_H
#define GAMEPHASE_H

#include <map>
#include <QString>

enum class GamePhases {
  DRAW_PHASE,
  STANDBY_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

// Unnamed namespaces?

namespace GamePhaseExternVars {
    extern const std::map<GamePhases, QString> gamePhaseToQString;

    extern GamePhases currentGamePhase;
}

#endif // GAMEPHASE_H
