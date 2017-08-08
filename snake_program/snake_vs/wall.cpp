#include "wall.h"
#include"constants.h"
#include"gamecontroller.h"
#include<time.h>

#include<QPainter>


static const qreal WALL_SIZE = 10;

Wall::Wall():
    wallhead(0,0)
{
    setData(GD_Type,GO_Wall);

    shapeTheWall();
}

void Wall::shapeTheWall()
{
    int i =0;
    for(pos_x=-99,pos_y=-99;pos_x<=100;pos_x+=WALL_SIZE)
    {
        QPointF brick(pos_x,pos_y);
        wallbody<<brick;
    }
    for(pos_x=-99,pos_y=91;pos_x<=100;pos_x+=WALL_SIZE)
    {
        QPointF brick(pos_x,pos_y);
        wallbody<<brick;
    }
    for(pos_x=-99,pos_y=-99;pos_y<=100;pos_y+=WALL_SIZE)
    {
        QPointF brick(pos_x,pos_y);
        wallbody<<brick;
    }
    for(pos_x=91,pos_y=-99;pos_y<=100;pos_y+=WALL_SIZE)
    {
        QPointF brick(pos_x,pos_y);
        wallbody<<brick;
    }
}

QRectF Wall::boundingRect() const
{
    return QRectF(-100,-100,200,200);
}

QPainterPath Wall::shape() const
{

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    foreach (QPointF p, wallbody)
    {
        QPointF itemp = mapFromScene(p);
        path.addRect(itemp.x(),itemp.y(),WALL_SIZE-1,WALL_SIZE-1);
     }

    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(),Qt::darkYellow);
    painter->restore();
}
