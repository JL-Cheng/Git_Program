#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include <QRectF>
#include<QPainterPath>

class GameController;

class Wall : public QGraphicsItem
{
public:
    Wall();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void shapeTheWall();

private:
    QList<QPointF> wallbody;
    QPointF wallhead;
    int pos_x,pos_y;
};

#endif // WALL_H
