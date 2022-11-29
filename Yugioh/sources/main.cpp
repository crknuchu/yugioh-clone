#include "headers/Card.h"
#include "headers/Monstercard.h"
#include "headers/Spellcard.h"
#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/Hand.h"
#include "headers/MonsterZone.h"
#include <iostream>
#include <QApplication>

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    Player player1("Nikola");
    Player player2("Milan");

    Game game(player1, player2);
    //  game.start();
    //game->show(); this is to turn on the graphics, need to decide if we use Game as pointer


    //MonsterCard::MonsterCard(int attackPoints, int defensePoints, MonsterType tip,MonsterKind kind,
    //  Attribute atribut, int level, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)

    MonsterCard card(3000, 2500,
                   MonsterType::DRAGON, MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                   8, "Sibirski Plavac", CardType::MONSTER_CARD, CardLocation::HAND, "Placeholder Description"
                   );

    MonsterCard card3(3000, 2500,
                   MonsterType::DRAGON, MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                   8, "Blue-Eyes White Dragon", CardType::MONSTER_CARD, CardLocation::HAND, "Placeholder Description"
                   );
    //  std::cout << card << std::endl;

    SpellCard card2(SpellType::NORMAL_SPELL, "Dark Hole", CardType::SPELL_CARD, CardLocation::HAND, "Destroy all monsters on the field.");

    Hand h = Hand();
    h.addToHand(card);
    h.addToHand(card3);

    MonsterZone m = MonsterZone();
    m.placeInMonsterZone(h.removeFromHand(card), 1);
    m.placeInMonsterZone(h.removeFromHand(card3), 2);

    std::cout << *m[0] << std::endl;
    std::cout << *m[1] << std::endl;

    m.removeFromMonsterZone(&card3);
    std::cout << *m[0] << std::endl;
    app.exec();
    return 0;
}
