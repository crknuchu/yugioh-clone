#include "catch.hpp"
#include "headers/Card.h"
#include "headers/Spellcard.h"
#include "headers/Monstercard.h"
#include "headers/Trapcard.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/EffectActivator.h"

//TEST_CASE("Card","[class][getter][setter][constructor]")
//{
//    SECTION("Card method getCardName() will return card name")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        std::string expected = "Change of Heart";
//        std::string output = card.getCardName();
//        REQUIRE(output == expected);
//    }

//    SECTION("Card method getCardType() will return card type")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        CardType expected = CardType::SPELL_CARD;
//        CardType output = card.getCardType();
//        REQUIRE(output == expected);
//    }

//    SECTION("Card method getCardTypeString() will return string representation of card type ")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        std::string expected = "spell card";
//        std::string output = card.getCardTypeString();
//        REQUIRE(output == expected);
//    }



//    SECTION("Card method getCardLocation() will return card location")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        CardLocation expected = CardLocation::DECK ;
//        CardLocation output = card.getCardLocation();
//        REQUIRE(output == expected);
//    }

//    SECTION("Card method getCardLocationString() will return string representation of card location")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        std::string expected = "deck";
//        std::string output = card.getCardLocationString();
//        REQUIRE(output == expected);
//    }

//    SECTION("Card method getCardDescription() will return card description")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"Target 1 monster your opponent controls; take control of it until the End Phase.", ":/resources/pictures/ChangeofHeart.jpg",  false);
//        std::string expected = "Target 1 monster your opponent controls; take control of it until the End Phase.";
//        std::string output = card.getCardDescription();
//        REQUIRE(output == expected);
//    }

//}



//TEST_CASE("Monstercard","[class][getter][setter][constructor]")
//{
//    SECTION("Monstercard method getAttackPoins() will return monster's attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        int expected = 2500;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }
//    SECTION("Monstercard method getDeffensePoins() will return monster's defense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        int expected = 2100;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }
//    SECTION("Monstercard method getLevel() will return monster's level")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        int expected = 7;
//        int output = card.getLevel();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method getMonsterTypeString() will return string representation of monster's type")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        std::string expected = card.getMonsterTypeString();
//        std::string output = "spell caster";
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method getMonsterKindString() will return string representation of monster's kind")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        std::string expected = card.getMonsterKindString();
//        std::string output = "normal monster";
//        REQUIRE(output == expected);
//    }



//    SECTION("Monstercard method getAttributeString() will return string representation of monster's attribute")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        std::string expected = card.getAttributeString();
//        std::string output = "dark";
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method getAttribute() will return monster's attribute")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        MonsterAttribute expected = card.getAttribute() ;
//        MonsterAttribute output = MonsterAttribute::DARK;
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method getMonsterKind() will return monster's kind")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        MonsterKind expected =MonsterKind::NORMAL_MONSTER;
//        MonsterKind output = card.getMonsterKind();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method getPosition() will return monster's position")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        MonsterPosition expected =MonsterPosition::NONE;
//        MonsterPosition output = card.getPosition();
//        REQUIRE(output == expected);
//    }


//    SECTION("Monstercard method setPosition(const MonsterPosition &newPosition) will set new position")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.setPosition(MonsterPosition::ATTACK);
//        MonsterPosition expected =MonsterPosition::ATTACK;
//        MonsterPosition output = card.getPosition();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method setAttackPoints(int newAttackPoints) will set new attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.setAttackPoints(500);
//        int expected =500;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }


//    SECTION("Monstercard method setDefensePoints(int newDefensePoints) will set new defense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.setDefensePoints(500);
//        int expected =500;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method increaseAttackPoints(int increaseBy) wil increase attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.increaseAttackPoints(500);
//        int expected =3000;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method decreaseAttackPoints(int decreaseBy) will decrease attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.decreaseAttackPoints(500);
//        int expected =2000;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method multiplyAttackPoints(float multiplyBy) will muptiply attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.multiplyAttackPoints(4);
//        int expected =10000;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }


//    SECTION("Monstercard method multiplyAttackPoints(float multiplyBy) will divide attack points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.multiplyAttackPoints(0.2);
//        int expected =500;
//        int output = card.getAttackPoints();
//        REQUIRE(output == expected);
//    }




//    SECTION("Monstercard method increaseDefensePoints(int increaseBy) wil increase defense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.increaseDefensePoints(500);
//        int expected =2600;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method decreaseDefensePoints(int decreaseBy) will decrease defense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.decreaseDefensePoints(500);
//        int expected =1600;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }

//    SECTION("Monstercard method multiplyDefensePoints(float multiplyBy) will multiply defense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.multiplyDefensePoints(4);
//        int expected =8400;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }


//    SECTION("Monstercard method multiplyDefensePoints(float multiplyBy) will divide deffense points")
//    {
//        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
//        card.multiplyDefensePoints(0.5);
//        int expected =1050;
//        int output = card.getDefensePoints();
//        REQUIRE(output == expected);
//    }


//}


//TEST_CASE("Spellcard","[class][getter][setter][constructor]")
//{
//    SECTION("Spellcard method getSpellType() will return spell type")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        SpellType expected = SpellType::NORMAL_SPELL;
//        SpellType output = card.getSpellType();
//        REQUIRE(output == expected);
//    }


//    SECTION("Spellcard method getSpellType() will return string representation of spell type")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        std::string expected = "normal spell";
//        std::string output = card.getSpellTypeString();
//        REQUIRE(output == expected);
//    }

//    SECTION("Spellcard method getCardLocationString() will return string representation of spellcard location")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        std::string expected = "deck";
//        std::string output = card.getCardLocationString();
//        REQUIRE(output == expected);
//    }

//    SECTION("Spellcard method getSpellPosition() will return spellcard position")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        SpellTrapPosition expected = SpellTrapPosition::NONE;
//        SpellTrapPosition output = card.getSpellPosition();
//        REQUIRE(output == expected);
//    }

//    SECTION("Spellcard method setSpellPosition() will set new position")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
//        SpellTrapPosition expected = SpellTrapPosition::SET;
//        card.setPosition(SpellTrapPosition::SET);
//        SpellTrapPosition output = SpellTrapPosition::SET;
//        REQUIRE(output == expected);
//    }

//    SECTION("Spellcard method getActive will return is spell active")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);

//        bool output = card.getActive();
//        bool expected = false;
//        REQUIRE(output == expected);
//    }

//    SECTION("Spellcard method activate spell will activate spell")
//    {
//        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/ChangeofHeart.jpg", false);

//        card.activateSpell();
//        bool output = card.getActive();
//        bool expected = true;
//        REQUIRE(output == expected);
//    }

//}


//TEST_CASE("Trapcard","[class][getter][setter][constructor]")
//{
//    SECTION("Trapcard method getTrapType() will return trap type")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        TrapType expected = TrapType::NORMAL_TRAP;
//        TrapType output = card.getTrapType();
//        REQUIRE(output == expected);
//    }


//    SECTION("Trapcard method getTrapTypeString() will return string representation of trap type")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        std::string expected = "normal trap";
//        std::string output = card.getTrapTypeString();
//        REQUIRE(output == expected);
//    }

//    SECTION("Trapcard method getCardLocationString() will return string representation of trapcard location")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        std::string expected = "deck";
//        std::string output = card.getCardLocationString();
//        REQUIRE(output == expected);
//    }


//    SECTION("Trapcard method getTrapPosition will return trap position")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        SpellTrapPosition expected = SpellTrapPosition::NONE;
//        SpellTrapPosition output = card.getTrapPosition();
//        REQUIRE(output == expected);
//    }


//    SECTION("Trapcard method setTrapPosition() will set new position")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        SpellTrapPosition expected = SpellTrapPosition::SET;
//        card.setPosition(SpellTrapPosition::SET);
//        SpellTrapPosition output = SpellTrapPosition::SET;
//        REQUIRE(output == expected);
//    }

//    SECTION("Trapcard method getActive will return is trap active")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        bool output = card.getActive();
//        bool expected = false;
//        REQUIRE(output == expected);
//    }

//    SECTION("Trapcard method activate trap will activate trap")
//    {
//        auto card = TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
//        card.activateTrap();
//        bool output = card.getActive();
//        bool expected = true;
//        REQUIRE(output == expected);
//    }
//}


// Game tests
TEST_CASE("Game","[class][getter][setter][constructor]")
{

    SECTION("Getter getLifePoints will return life points specified in the constructor")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2, 5000);

        int output = m_pGame->getLifePoints();
        int expected = 5000;
        REQUIRE(output == expected);
    }

    SECTION("Setter setLifePoints will set m_lifePoints to the specified value")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2);

        m_pGame->setLifePoints(5000);
        int output = m_pGame->getLifePoints();
        int expected = 5000;
        REQUIRE(output == expected);
    }

    SECTION("Getter getNumberOfCards will return number of cards specified in the constructor")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2, 5000, 10);

        int output = m_pGame->getNumberOfCards();
        int expected = 10;
        REQUIRE(output == expected);
    }

    SECTION("Setter setNumberOfCards will set m_numberOfCards to the specified value")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2);

        m_pGame->setNumberOfCards(10);
        int output = m_pGame->getNumberOfCards();
        int expected = 10;
        REQUIRE(output == expected);
    }

    SECTION("Getter getTimePerMove will return time per move specified in the constructor")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2, 5000, 10, 100);

        int output = m_pGame->getTimePerMove();
        int expected = 100;
        REQUIRE(output == expected);
    }

    SECTION("Setter setTimePerMove will set m_timePerMove to the specified value")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2);

        m_pGame->setTimePerMove(100);
        int output = m_pGame->getTimePerMove();
        int expected = 100;
        REQUIRE(output == expected);
    }

    SECTION("Setter setGamePhase will set m_timePerMove to the specified value")
    {
        Player *player1 = new Player("Nikola");
        Player *player2 = new Player("Milan");
        Game *m_pGame = new Game(*player1, *player2);

        m_pGame->setTimePerMove(100);
        int output = m_pGame->getTimePerMove();
        int expected = 100;
        REQUIRE(output == expected);
    }
}

// EffectActivator tests
TEST_CASE("EffectActivator","[class][getter][setter][constructor]")
{
    SECTION("Getter getCard will return the card that is bound to this EffectActivator object")
    {
        Card* card = new TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);

        EffectActivator effectActivator(*card);
        Card* output = effectActivator.getCard();
        Card* expected = card;
        REQUIRE(output == expected);
    }

    SECTION("Setter setCard will set the card that is bound to this EffectActivator object")
    {
        Card* oldCard = new TrapCard(TrapType::NORMAL_TRAP ,"Ultimate Offering", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);
        Card* newCard = new TrapCard(TrapType::NORMAL_TRAP ,"NEW CARD", CardType::TRAP_CARD, CardLocation::DECK, SpellTrapPosition::NONE,"...", ":/resources/pictures/UltimateOffering.jpg", false);

        EffectActivator effectActivator(*oldCard);
        effectActivator.setCard(*newCard);

        Card* output = effectActivator.getCard();
        Card* expected = newCard;
        REQUIRE(output == expected);
    }
}
