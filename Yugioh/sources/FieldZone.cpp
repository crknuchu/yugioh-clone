#include "headers/FieldZone.h"

FieldZone::FieldZone(float x, float y)
    : Zone(x,y) {
    setPen(QPen(Qt::blue, 2));
}
