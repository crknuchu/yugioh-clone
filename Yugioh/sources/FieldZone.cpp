#include "headers/FieldZone.h"
#include <iostream>

FieldZone::FieldZone() : Zone(true) {}

void FieldZone::setFieldZone(float x, float y) {
  setCoordinates(x, y);
  setPen(QPen(Qt::white, 2));
}

FieldZone::~FieldZone() = default;
