#ifndef GAMEPHASE_H
#define GAMEPHASE_H

#include <QString>
#include <map>

enum class GamePhases {
  DRAW_PHASE,
  STANDBY_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

namespace GamePhaseExternVars {
extern const std::map<GamePhases, QString> gamePhaseToQString;
extern const std::map<QString, GamePhases> QStringToGamePhase;
extern GamePhases currentGamePhase;
} // namespace GamePhaseExternVars

#endif // GAMEPHASE_H
