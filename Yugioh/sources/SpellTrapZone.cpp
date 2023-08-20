#include "headers/SpellTrapZone.h"
#include <iostream>

SpellTrapZone::SpellTrapZone() = default;

SpellTrapZone::~SpellTrapZone() {
  for (Zone *zone : m_spellTrapZone) {
    delete zone;
  }

  m_spellTrapZone.clear();
};

void SpellTrapZone::setSpellTrapZone(float x, float y) {
  float gap = 40;
  for (int i = 0; i < 5; i++) {
    Zone *zone = new Zone(x, y);
    zone->setBrush(QColor(0, 200, 0, 30));
    m_spellTrapZone.push_back(zone);
    x += zone->getWidth() + gap;
  }

  m_width = x;
}

auto SpellTrapZone::removeFromSpellTrapZone(Zone *targetedZone) -> Card * {
  Card *card = targetedZone->m_pCard;
  targetedZone->m_pCard = nullptr;
  return card;
}

void SpellTrapZone::removeFromSpellTrapZone(int zoneNumber) {
  Zone *zone = m_spellTrapZone[zoneNumber];
  removeFromSpellTrapZone(zone);
}

void SpellTrapZone::placeInSpellTrapZone(Card *card, Zone *zone) {
  if (!zone->isEmpty()) {
    std::cout << "Spot is occupied" << std::endl;
    return;
  }

  auto *spellCard = dynamic_cast<SpellCard *>(card);
  auto *trapCard = dynamic_cast<TrapCard *>(card);
  if (spellCard) {
    zone->putInZone(spellCard);
  } else if (trapCard) {
    zone->putInZone(trapCard);
  } else {
    std::cout << "Only spell or trap cards can be put in spell/trap zone"
              << std::endl;
    return;
  }
}

void SpellTrapZone::placeInSpellTrapZone(Card *card, int zoneNumber) {
  if (zoneNumber < 1 || zoneNumber > 5) {
    std::cout << "Invalid zone number" << std::endl;
    return;
  }

  Zone *zone = m_spellTrapZone[zoneNumber - 1];
  placeInSpellTrapZone(card, zone);
}

void SpellTrapZone::colorFreeZones() {
  for (Zone *zone : m_spellTrapZone) {
    if (zone->isEmpty()) {
      QColor red50(Qt::red);
      red50.setAlphaF(0.5);
      zone->setBrush(red50);
      zone->update();
    }
  }
}

void SpellTrapZone::colorOccupiedZones() {
  for (Zone *zone : m_spellTrapZone) {
    if (!zone->isEmpty()) {
      QColor green50(Qt::green);
      green50.setAlphaF(0.5);
      zone->setBrush(green50);
      zone->update();
    }
  }
}

void SpellTrapZone::refresh() {
  for (Zone *zone : m_spellTrapZone) {
    zone->setBrush(QColor(0, 200, 0, 30));
    zone->update();
  }
}

auto SpellTrapZone::isFull() const -> bool {
  for (Zone *zone : m_spellTrapZone) {
    if (zone->isEmpty())
      return false;
  }
  return true;
}

auto SpellTrapZone::getWidth() const -> float { return m_width; }
