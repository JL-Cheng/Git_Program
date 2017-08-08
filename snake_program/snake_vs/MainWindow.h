#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>


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

private slots:
    void initScene();
    void initSceneBackground();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;
    QPushButton *button1;
	QPushButton *button2;


};

#endif // MAINWINDOW_H
