#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>


class Card: public QGraphicsPixmapItem {
    public:
        Card(QGraphicsItem *parent = 0);

        void pickCard();
        void mousePressEvent(QGraphicsSceneMouseEvent*event);
        void setName(std::string name);
        float getHeight();
        float getWidth();
    private:
        std::string cardName = "";
        std::string owner = "";
        float height;
        float width;
};

#endif // CARD_H