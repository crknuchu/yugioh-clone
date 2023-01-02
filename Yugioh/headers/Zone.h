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

    void setCoordinatesHW(float, float);
    // Placeholder
    float m_x;
    float m_y;

signals:
    void zoneRedAndClicked(Zone*);
    void zoneGreenAndClicked(Zone*);
    void zoneBlueAndClicked(Zone*);

private:
    float m_height = 150;
    float m_width = 100;
    bool m_isFieldZone = false;
};

#endif // ZONE_H
