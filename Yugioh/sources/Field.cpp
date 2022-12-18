#include "headers/Field.h"

Field::Field()
    : graveyard(new Graveyard()){}

void Field::setField(int playerNumber,int windowWidth ,int windowHeight) {
    int zoneHeight = 150;
    int zoneWidth = 100;
    int gapBetweenZones = 20;
    int gapBetweenFields = 100;
    if(playerNumber == 1) {
        m_width = windowWidth / 4;
        float y = (windowHeight / 2);
        monsterZone.setMonsterZone(m_width, y);
        spellTrapZone.setSpellTrapZone(m_width, y + gapBetweenZones + zoneHeight);
        m_width = monsterZone.getWidth();
        graveyard->setGraveyard(m_width, y);
        m_width = spellTrapZone.getWidth();
        deck.setDeck(m_width, y + gapBetweenZones + zoneHeight, playerNumber);
    }
    else if(playerNumber == 2) {
        m_width = windowWidth / 4;
        float y = (windowHeight / 2) - (zoneHeight + gapBetweenFields);
        monsterZone.setMonsterZone(m_width, y);
        spellTrapZone.setSpellTrapZone(m_width, y - gapBetweenZones - zoneHeight);
        graveyard->setGraveyard(m_width - zoneWidth - gapBetweenZones, y);
        deck.setDeck(m_width - zoneWidth - gapBetweenZones, y - gapBetweenZones - zoneHeight, playerNumber);
    }
}
