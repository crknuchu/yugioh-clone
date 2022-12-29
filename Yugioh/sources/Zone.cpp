#include "headers/Zone.h"

Zone::Zone(bool isFieldZone)
    : m_isFieldZone(isFieldZone){}

Zone::Zone(float x, float y)
    : m_x(x), m_y(y){
    m_pCard = nullptr;
    setPen(QPen(Qt::white, 2));
    setBrush(Qt::NoBrush);
    this->setZValue(-10);
}

Zone::~Zone(){}

void Zone::putInZone(Card *card)
{
    m_pCard = card;
    card->move(this->m_x, this->m_y);
}

bool Zone::isEmpty() {
    return m_pCard == nullptr;
}

float Zone::getWidth() const {
    return m_width;
}

float Zone::getHeight() const {
    return m_height;
}

void Zone::setCoordinates(float x, float y) {
    m_x = x;
    m_y = y;
}

#include <iostream>

void Zone::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    QColor zoneColor = this->brush().color();
    QColor red50(Qt::red);
    red50.setAlphaF(0.5);
    QColor green50(Qt::green);
    green50.setAlphaF(0.5);
    QColor blue50(Qt::blue);
    blue50.setAlphaF(0.5);
    if(zoneColor == red50) {
        emit zoneRedAndClicked(this);
    }
    else if(zoneColor == green50) {
        emit zoneGreenAndClicked(this);
    }
    else if(zoneColor == blue50) {
        emit zoneBlueAndClicked(this);
    }
}

QRectF Zone::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

QPainterPath Zone::shape() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRect(rect);

    return path;
}

void Zone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage fieldBackGround(":/resources/pictures/fieldZoneSymbol.png");
    QRectF rect = boundingRect();
    painter->setPen(pen());
    painter->setBrush(brush());
    if(m_isFieldZone)
        painter->drawImage(QRectF(QPointF(m_x + m_width/5, m_y + m_height/4),
                                  QPointF(m_x + 4*m_width/5, m_y + 3*m_height/4)), fieldBackGround);

    painter->drawRect(rect);
};

