#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include"selectWindow.h"


class QGraphicsScene;
class QGraphicsView;

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();
    void initScene();
    void initSceneBackground();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;

public:
	selectWindow *swd;


};

#endif // MAINWINDOW_H
