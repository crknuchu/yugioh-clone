#include "headers/Zone.h"
#include <iostream>

Zone::Zone(float x, float y)
    : m_x(x), m_y(y){
    m_pCard = nullptr;
    setPen(QPen(Qt::white, 2));
    setBrush(Qt::NoBrush);
}

Zone::~Zone(){
    std::cerr << "We are in Zone destructor!" << std::endl;
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

void Zone::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    auto zoneColor = this->brush().color();
    if(zoneColor == Qt::red) {
        emit zoneRedAndClicked(this);
    }
    else if(zoneColor == Qt::green) {
        emit zoneGreenAndClicked(this);
    }

//    QGraphicsRectItem::mousePressEvent(event);
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
    QRectF rect = boundingRect();
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect);
};
