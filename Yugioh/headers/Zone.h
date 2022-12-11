#ifndef ZONE_H
#define ZONE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include "Card.h"

class Zone : public QObject, public QGraphicsRectItem {

    Q_OBJECT
public:
    Zone(float x, float y);
    bool isEmpty();
    void putInZone(Card* card);
    float getWidth() const;
    float getHeight() const;
    void mousePressEvent(QGraphicsSceneMouseEvent*event) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    Card* m_pCard;
signals:
    void zoneRedAndClicked();

private:
    float m_height = 150;
    float m_width = 100;
    float m_x = 300;
    float m_y = 300;
};

#endif // ZONE_H
