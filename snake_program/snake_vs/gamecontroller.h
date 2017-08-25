#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QPushButton>
#include "selectWindow.h"
#include"MainWindow.h"

class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, MainWindow *parent = 0);
    ~GameController();

    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);

public slots:
    void pause();
    void resume();
    void gameOver();
	void gameStart();

protected:
     bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();

    QTimer timer;
    QGraphicsScene &scene;
    Snake *snake;
    Wall *wall;
	MainWindow *my_parent;
	selectWindow *swd;

    bool game_pause;
};

#endif // GAMECONTROLLER_H
