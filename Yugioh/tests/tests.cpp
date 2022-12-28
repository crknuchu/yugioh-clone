#include "catch.hpp"
#include "headers/Card.h"
#include "headers/Spellcard.h"
#include "headers/Monstercard.h"


TEST_CASE("Card","[class][getter][setter][constructor]")
{
    SECTION("Card method getCardName() will return card name")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
        std::string expected = "Change of Heart";
        std::string output = card.getCardName();
        REQUIRE(output == expected);
    }

    SECTION("Card method getCardType() will return card type")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
        CardType expected = CardType::SPELL_CARD;
        CardType output = card.getCardType();
        REQUIRE(output == expected);
    }

    SECTION("Card method getCardTypeString() will return string representation of card type ")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
        std::string expected = "spell card";
        std::string output = card.getCardTypeString();
        REQUIRE(output == expected);
    }



    SECTION("Card method getCardLocation() will return card location")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
        CardLocation expected = CardLocation::DECK ;
        CardLocation output = card.getCardLocation();
        REQUIRE(output == expected);
    }

    SECTION("Card method getCardLocationString() will return string representation of card location")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"...", ":/resources/pictures/ChangeofHeart.jpg", false);
        std::string expected = "deck";
        std::string output = card.getCardLocationString();
        REQUIRE(output == expected);
    }

    SECTION("Card method getCardDescription() will return card description")
    {
        auto card = SpellCard(SpellType::NORMAL_SPELL ,"Change of Heart", CardType::SPELL_CARD, CardLocation::DECK, SpellTrapPosition::FACE_UP,"Target 1 monster your opponent controls; take control of it until the End Phase.", ":/resources/pictures/ChangeofHeart.jpg",  false);
        std::string expected = "Target 1 monster your opponent controls; take control of it until the End Phase.";
        std::string output = card.getCardDescription();
        REQUIRE(output == expected);
    }

}



TEST_CASE("Monstercard","[class][getter][setter][constructor]")
{
    SECTION("Monstercard method getAttackPoins() will return monster's attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        int expected = 2500;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }
    SECTION("Monstercard method getDeffensePoins() will return monster's defense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        int expected = 2100;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }
    SECTION("Monstercard method getLevel() will return monster's level")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        int expected = 7;
        int output = card.getLevel();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method getMonsterTypeString() will return string representation of monster's type")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        std::string expected = card.getMonsterTypeString();
        std::string output = "spell caster";
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method getMonsterKindString() will return string representation of monster's kind")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        std::string expected = card.getMonsterKindString();
        std::string output = "normal monster";
        REQUIRE(output == expected);
    }



    SECTION("Monstercard method getAttributeString() will return string representation of monster's attribute")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        std::string expected = card.getAttributeString();
        std::string output = "dark";
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method getAttribute() will return monster's attribute")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        MonsterAttribute expected = card.getAttribute() ;
        MonsterAttribute output = MonsterAttribute::DARK;
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method getMonsterKind() will return monster's kind")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        MonsterKind expected =MonsterKind::NORMAL_MONSTER;
        MonsterKind output = card.getMonsterKind();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method getPosition() will return monster's position")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        MonsterPosition expected =MonsterPosition::NONE;
        MonsterPosition output = card.getPosition();
        REQUIRE(output == expected);
    }


    SECTION("Monstercard method setPosition(const MonsterPosition &newPosition) will set new position")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.setPosition(MonsterPosition::ATTACK);
        MonsterPosition expected =MonsterPosition::ATTACK;
        MonsterPosition output = card.getPosition();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method setAttackPoints(int newAttackPoints) will set new attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.setAttackPoints(500);
        int expected =500;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }


    SECTION("Monstercard method setDefensePoints(int newDefensePoints) will set new defense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.setDefensePoints(500);
        int expected =500;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method increaseAttackPoints(int increaseBy) wil increase attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.increaseAttackPoints(500);
        int expected =3000;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method decreaseAttackPoints(int decreaseBy) will decrease attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.decreaseAttackPoints(500);
        int expected =2000;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method multiplyAttackPoints(float multiplyBy) will muptiply attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.multiplyAttackPoints(4);
        int expected =10000;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }


    SECTION("Monstercard method multiplyAttackPoints(float multiplyBy) will divide attack points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.multiplyAttackPoints(0.2);
        int expected =500;
        int output = card.getAttackPoints();
        REQUIRE(output == expected);
    }




    SECTION("Monstercard method increaseDefensePoints(int increaseBy) wil increase defense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.increaseDefensePoints(500);
        int expected =2600;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method decreaseDefensePoints(int decreaseBy) will decrease defense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.decreaseDefensePoints(500);
        int expected =1600;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }

    SECTION("Monstercard method multiplyDefensePoints(float multiplyBy) will multiply defense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.multiplyDefensePoints(4);
        int expected =8400;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }


    SECTION("Monstercard method multiplyDefensePoints(float multiplyBy) will divide deffense points")
    {
        MonsterCard card = MonsterCard("Dark Magician", 2500,2100,7,MonsterType::SPELLCASTER,MonsterKind::NORMAL_MONSTER,MonsterAttribute::DARK,false,MonsterPosition::NONE, false,CardType::MONSTER_CARD, CardLocation::HAND,"The ultimate wizard in terms of attack and defense.", ":/resources/pictures/DarkMagician.jpg", false );
        card.multiplyDefensePoints(0.5);
        int expected =1050;
        int output = card.getDefensePoints();
        REQUIRE(output == expected);
    }


}
