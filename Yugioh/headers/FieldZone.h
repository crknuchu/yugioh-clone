#ifndef FIELDZONE_H
#define FIELDZONE_H

#include "Zone.h"

class FieldZone : public Zone {
public:
  FieldZone();
  ~FieldZone();
  void setFieldZone(float, float);

private:
  Zone* m_fieldZone;
  float m_x;
  float m_y;
};

#endif // FIELDZONE_H
