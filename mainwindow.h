#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <mysql.h>



class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = Q_NULLPTR);
	~mainwindow();
private:
	Ui::mainwindowClass ui;
	MYSQL* db;
};