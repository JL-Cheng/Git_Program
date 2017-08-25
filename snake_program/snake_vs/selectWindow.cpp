#include"selectWindow.h"
#include"gamecontroller.h"

selectWindow::selectWindow(QWidget *parent)
	: button1(new QPushButton(this)),
	button2(new QPushButton(this))/*,
	QWidget(parent)*/
{
	resize(300, 300);

	button1->setText("Play");
	button1->setGeometry(50, 50, 100, 50);
	button2->setText("Exit");
	button2->setGeometry(50, 150, 100, 50);

	my_parent = parent;

	connect(button1, SIGNAL(clicked()), parent,SLOT(initSceneBackground()));
	connect(button2, SIGNAL(clicked()),this, SLOT(my_close()));


}

selectWindow::~selectWindow()
{
	delete button1;
	delete button2;
}

void selectWindow::my_close()
{
	my_parent->close();
	this->close();
}