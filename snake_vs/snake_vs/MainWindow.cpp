#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "gamecontroller.h"
#include "MainWindow.h"
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	scene(new QGraphicsScene(this)),
	view(new QGraphicsView(scene, this)),
	button1(new QPushButton(this)),
	button2(new QPushButton(this))
{	
    setCentralWidget(view);
    resize(600, 600);
	initScene();
	QTimer::singleShot(0, this, SLOT(adjustViewSize()));

    button1->setText("Play");
	button1->setGeometry(250, 250, 100, 50);
	connect(button1, SIGNAL(clicked()), this, SLOT(initSceneBackground()));

	button2->setText("Exit");
	button2->setGeometry(250, 350, 100, 50);
	connect(button2, SIGNAL(clicked()), this, SLOT(close()));
    
    //initSceneBackground();
	
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
		game = new GameController(*scene, this);
        QPixmap bg(TILE_SIZE, TILE_SIZE);
        QPainter p(&bg);
        p.setPen(QPen(Qt::white));
        p.setBrush(QBrush(Qt::gray));
        p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

        view->setBackgroundBrush(QBrush(bg));
		delete button1;
}
