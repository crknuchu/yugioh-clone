#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>


class Card: public QGraphicsPixmapItem {
    public:
        Card(QGraphicsItem *parent = 0);

        void menuPopUp(QGraphicsSceneHoverEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent*event);
        void setName(std::string name);
        float getHeight();
        float getWidth();
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    private:
        std::string cardName = "";
        std::string owner = "";
        float height;
        float width;
};

#endif // CARD_H