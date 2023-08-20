#include "headers/Graveyard.h"
#include <iostream>
#include <algorithm>
#include <optional>

Graveyard::Graveyard()
    :m_x(0), m_y(0){}

void Graveyard::setGraveyard(float x, float y)
{
    m_x = x;
    m_y = y;
    setPen(QPen(Qt::white, 2));
    setBrush(QColor(211,211,211,30));
}



Graveyard::Graveyard(std::vector<Card*> &initialGraveyard)
    :CardList(initialGraveyard)
{
    for(auto x : m_cardList) {
        std::cout << x->getCardName() << " ";
    }
}
Graveyard::~Graveyard()= default;

void Graveyard::sendToGraveyard(Card &card) {
    m_cardList.push_back(&card);
    card.setCardLocation(CardLocation::GRAVEYARD);
    card.move(this->m_x, this->m_y);
}

auto Graveyard::getGraveyard() const -> std::vector<Card*>{
    return m_cardList;
}

auto Graveyard::removeFromGraveyard(Card &card) -> Card*
{
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &card);
    m_cardList.erase(it);
    return &card;
}

auto Graveyard::boundingRect() const -> QRectF
{
    return {m_x, m_y, m_width, m_height};
}

auto Graveyard::shape() const -> QPainterPath
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRect(rect);

    return path;
}

void Graveyard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rect = boundingRect();
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawRect(rect);
};


