#pragma once
#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include<QWidget>
#include<QPushButton>

class selectWindow :public QWidget
{
	Q_OBJECT

public:
	selectWindow(QWidget *parent=0);
	~selectWindow();

public slots:
	void my_close();

private:
	QPushButton *button1;
	QPushButton *button2;

	QWidget *my_parent;
	
};

#endif // !SELECTWINDOW_H
