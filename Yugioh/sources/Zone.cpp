#include "headers/Zone.h"
#include "headers/MonsterZone.h"

Zone::Zone(float x, float y)
    : m_x(x), m_y(y){
    m_pCard = nullptr;
    setPen(QPen(Qt::blue, 2));
    setBrush(Qt::NoBrush);
}

void Zone::putInZone(Card *card)
{
    m_pCard = card;
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

void Zone::mousePressEvent(QGraphicsSceneMouseEvent*event) {
    if(this->brush().color() != Qt::red)
            return;

    emit zoneRedAndClicked();
}

QRectF Zone::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_height);
}

void Zone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rect = boundingRect();
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect);
};
