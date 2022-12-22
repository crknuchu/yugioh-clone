#ifndef ZONE_H
#define ZONE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include "Card.h"

class Zone : public QObject, public QGraphicsRectItem {

    Q_OBJECT
public:
    Zone(bool);
    Zone(float x, float y);
    ~Zone();
    bool isEmpty();
    void putInZone(Card* card);
    float getWidth() const;
    float getHeight() const;
    void setCoordinates(float, float);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    Card* m_pCard;
signals:
    void zoneRedAndClicked(Zone*);

private:
    float m_height = 150;
    float m_width = 100;
    float m_x;
    float m_y;
    bool m_isFieldZone = false;
};

#endif // ZONE_H
