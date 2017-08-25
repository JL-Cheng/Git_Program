#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "wall.h"
#include"selectWindow.h"

GameController::GameController(QGraphicsScene &scene, MainWindow *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    game_pause(false),
	my_parent(parent)
{
    timer.start( 1000/33 );


    /*Food *a1 = new Food(0, -50);
    scene.addItem(a1);
    wall = new Wall();
    scene.addItem(wall);

    scene.addItem(snake);*/

	gameStart();

    scene.installEventFilter(this);


    resume();
}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;

    addNewFood();
}

void GameController::snakeHitWall(Snake *snake, Wall *wall)
{
    QTimer::singleShot(0,this,SLOT(gameOver()));
}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
        if(snake->showMoveDirection()!=snake->MoveRight)
        {
            snake->setMoveDirection(Snake::MoveLeft);
        }
            break;
        case Qt::Key_Right:
        if(snake->showMoveDirection()!=snake->MoveLeft)
        {
            snake->setMoveDirection(Snake::MoveRight);
        }
            break;
        case Qt::Key_Up:
        if(snake->showMoveDirection()!=snake->MoveDown)
        {
            snake->setMoveDirection(Snake::MoveUp);
        }
            break;
        case Qt::Key_Down:
        if(snake->showMoveDirection()!=snake->MoveUp)
        {
            snake->setMoveDirection(Snake::MoveDown);
        }
            break;
        case Qt::Key_Space:
        if(!game_pause)
        {
            pause();
            game_pause=true;
        }
        else
        {
            resume();
            game_pause=false;
        }
            break;
    }
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int) (qrand() % 100) / 10;
        y = (int) (qrand() % 100) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5)))||wall->shape().contains(wall->mapFromScene(x+5,y+5)));

    Food *food = new Food(x , y);
    scene.addItem(food);
}

void GameController::gameOver()
{
	scene.clear();
	my_parent->swd = new selectWindow(my_parent);
	my_parent->swd->show();
}

void GameController::gameStart()
{

	snake = new Snake(*this);
	wall = new Wall();
	scene.addItem(wall);
	scene.addItem(snake);
	addNewFood();
	delete my_parent->swd;
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
