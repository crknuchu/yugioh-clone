#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "Card.h"
#include "GamePhase.h"
#include <map>

enum class MonsterKind {
  NORMAL_MONSTER,
  EFFECT_MONSTER,
  RITUAL_MONSTER,
  FUSION_MONSTER,
  XYZ_MONSTER,
  PENDULUM_MONSTER,
  LINK_MONSTER,
  TOKEN_MONSTER
};

enum class MonsterType {
  AQUA,
  BEAST,
  BEAST_WARRIOR,
  CREATOR_GOD,
  DINOSAUR,
  DIVINE_BEAST,
  DRAGON,
  FAIRY,
  FIEND,
  FISH,
  INSECT,
  MACHINE,
  PLANT,
  PSYCHIC,
  REPTILE,
  ROCK,
  SPELLCASTER,
  WARRIOR,
  WINGED_BEAST
};

enum class MonsterAttribute { DARK, DIVINE, EARTH, FIRE, LIGHT, WATER, WIND };

class MonsterCard : public Card {
public:
  MonsterCard(const std::string& cardName, int attackPoints, int defensePoints, int level,
              MonsterType type, MonsterKind kind, MonsterAttribute attribute, bool active,
              MonsterPosition position, bool alreadyAttackedThisTurn, CardType cardType,
              CardLocation cardLocation, const std::string& cardDescription, std::string imagePath,
              bool isSummonedThisTurn = false);
  ~MonsterCard();

  MonsterCard* clone() override;
  bool shouldBeSentToGraveyard() override;
  int getAttackPoints() const;
  int getDefensePoints() const;
  MonsterType getMonsterType() const;
  std::string getMonsterTypeString() const;
  MonsterKind getMonsterKind() const;
  std::string getMonsterKindString() const;
  MonsterAttribute getAttribute() const;
  std::string getAttributeString() const;
  int getLevel() const;
  MonsterPosition getPosition() const;
  bool getIsSummonedThisTurn() const;
  bool getIsRepositionedThisTurn() const;
  void setIsRepositionThisTurn(bool isRepositioned);
  void setIsSummonedThisTurn(bool isSummoned);
  void setPosition(const MonsterPosition& newPosition); // Just a setter
  void changePosition();                                // Calls a setter + changes the pixmap

  void setAttackPoints(int newAttackPoints);
  void setDefensePoints(int newDefensePoints);

  // methods to be called with the appropriate spell/trap card
  void increaseAttackPoints(int increaseBy);
  void decreaseAttackPoints(int decreaseBy);
  void multiplyAttackPoints(float multiplyBy);

  void increaseDefensePoints(int increaseBy);
  void decreaseDefensePoints(int decreaseBy);
  void multiplyDefensePoints(float multiplyBy);

  bool normalSummon(MonsterPosition position);
  bool specialSummon(MonsterPosition position);

  void setCardMenu(bool isMonsterZoneFull, bool OpponentHaveMonsters) override;

  void setAlreadyAttackedThisTurn(bool didIAlreadyAttack);

  static bool globalSummonedThisTurn;

private:
  int attackPoints;
  int defensePoints;
  MonsterType type;
  MonsterKind monsterKind;
  MonsterAttribute attribute;
  int level;
  bool active;
  MonsterPosition position;
  bool alreadyAttackedThisTurn;
  bool isSummonedThisTurn;
  bool isRepositionedThisTurn;
};

#endif // MONSTERCARD_H
