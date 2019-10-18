#include "mainwindow.h"
#include <QMessageBox>

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//连接数据库
	db = mysql_init(NULL); //初始化
	if (db == NULL)
		QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化失败!"), QString::fromLocal8Bit("确认"));
	MYSQL* conn = mysql_real_connect(db, "localhost", "root", "passwordmysql", "stu_db", 0, NULL, 0); //建立连接
	if (conn == NULL)
		QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库连接失败!"), QString::fromLocal8Bit("确认"));
	/*
	else
		QMessageBox::information(this, QString::fromLocal8Bit("信息"), QString::fromLocal8Bit("数据库连接成功!"), QString::fromLocal8Bit("确认"));
	*/




}

mainwindow::~mainwindow()
{
	mysql_close(db); //关闭连接
}
