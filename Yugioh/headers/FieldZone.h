#ifndef FIELDZONE_H
#define FIELDZONE_H

#include "Zone.h"

class FieldZone : public Zone {
public:
    FieldZone(float, float);
private:
    float m_x;
    float m_y;
};

#endif // FIELDZONE_H
