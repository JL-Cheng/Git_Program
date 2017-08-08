#include <QPainter>

#include "constants.h"
#include "gamecontroller.h"
#include "snake.h"
#include<stdlib.h>
#include<time.h>

static const qreal SNAKE_SIZE = 10;

Snake::Snake(GameController &controller) :
    head(0, 0),
    growing(7),
    speed(3),
    moveDirection(NoMove),
    controller(controller)
{
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + SNAKE_SIZE,      // width
                          br.y() - tl.y() + SNAKE_SIZE       //height
                          );
    return bound;
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addEllipse(QPointF(SNAKE_SIZE/2,SNAKE_SIZE/2),SNAKE_SIZE/2,SNAKE_SIZE/2);

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addEllipse(QPointF(itemp.x()+SNAKE_SIZE/2,itemp.y()+SNAKE_SIZE/2),SNAKE_SIZE/2,SNAKE_SIZE/2);

    }
    return path;

}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int red,green,blue;
    srand((unsigned)time(NULL));
    red=(rand()+150)%255;
    srand((unsigned)time(NULL));
    blue=(rand()+50)%255;
    srand((unsigned)time(NULL));
    green=rand()%255;
    QBrush brush(QColor(red,green,blue), Qt::SolidPattern);
    painter->save();
    painter->fillPath(shape(), brush);

    painter->restore();
}

void Snake::setMoveDirection(Direction direction)
{
    moveDirection = direction;
}

void Snake::advance(int step)
{
    if (!step) {
        return;
    }
    if (tickCounter++ % speed != 0) {
        return;
    }
    if (moveDirection == NoMove) {
        return;
    }

    if (growing > 0) {
		QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;
    }

    switch (moveDirection) {
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
    }

    setPos(head);
    handleCollisions();
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100) {
        head.rx() = 100;
    }
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.rx() > 100) {
        head.rx() = -100;
    }
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if (head.ry() < -100) {
        head.ry() = 100;
    }
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.ry() > 100) {
        head.ry() = -100;
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    // Check collisions with other objects on screen
    foreach (QGraphicsItem *collidingItem, collisions)
    {
        if (collidingItem->data(GD_Type) == GO_Food)
        {
            // Let GameController handle the event by putting another apple
            controller.snakeAteFood(this, (Food *)collidingItem);
            growing += 1;
        }
        else if(collidingItem->data(GD_Type)==GO_Wall)
        {
            controller.snakeHitWall(this,(Wall*)collidingItem);
        }
    }

    // Check snake eating itself
    if (tail.contains(head)) {
        controller.snakeAteItself(this);
    }
}
