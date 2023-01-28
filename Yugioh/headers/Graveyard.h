#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include "CardList.h"
#include <QGraphicsRectItem>
#include <QPainter>
#include <optional>

class Graveyard : public CardList, public QGraphicsRectItem {
public:
  Graveyard();

  void setGraveyard(float x, float y);
  Graveyard(std::vector<Card*>& initialGraveyard);
  ~Graveyard();
  void sendToGraveyard(Card& card);
  std::vector<Card*> getGraveyard() const;
  Card* removeFromGraveyard(Card& card);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

private:
  float m_height = 150;
  float m_width = 100;
  float m_x;
  float m_y;
};

#endif // GRAVEYARD_H
