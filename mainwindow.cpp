#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_mysql();
	connect(ui->btn_login, SIGNAL(clicked(bool)), this, SLOT(login()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_mysql()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("mysql_connect")) {
        db = QSqlDatabase::database("mysql_connect");
    } else {
	//连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL", "mysql_connect"); //数据库类型
    db.setHostName("localhost");    //设置为本地主机
    db.setDatabaseName("stu_db");   //选择数据库名称
    db.setUserName("root");         //设置用户名
    db.setPassword("passwordmysql");//设置密码
    if(!db.open())
		QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库连接失败!"), QString::fromLocal8Bit("确认"));
//	else
//		QMessageBox::information(this, QString::fromLocal8Bit("信息"), QString::fromLocal8Bit("数据库连接成功!"), QString::fromLocal8Bit("确认"));
    }

}

bool MainWindow::is_stu() {
    return (user_type == "stu" ? 1 : 0);
}

void MainWindow::login()
{
	//获取登录信息
    QString user_t = ui->typeGroup->checkedButton()->text();
	QString id = ui->le_user->text();
	QString password = ui->le_password->text();
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);
//    db.exec("SET NAMES 'GBK'");
    user_type = (user_t == "学生") ? "stu" : "admin";

    //验证登录信息
    if(user_type == "admin") { //管理员信息验证
        query.exec("select id, password from admin");
        bool flag = false;
        while(query.next()) {
            QString id_temp = query.value(0).toString();
            QString password_temp = query.value(1).toString();
            if (id == id_temp && password == password_temp) {
                flag = true;
            }
        }
        if(flag) {  //用户密码正确, 则进入menu_admin
            this->hide();
            m_a = new menu_admin;
            m_a->show();
        } else {
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("账户密码错误,请重新输入!"), QString::fromLocal8Bit("确认"));
            ui->le_user->clear();
            ui->le_password->clear();
        }
    } else {                    //学生信息验证
        query.exec("select stu_id, password from stu");
        bool flag = false;
        while(query.next()) {
            QString stu_id_temp = query.value(0).toString();
            QString password_temp = query.value(1).toString();
            if (id == stu_id_temp && password == password_temp) {
                flag = true;
            }
        }
        if(flag) {  //用户密码正确, 则进入menu_stu
            this->hide();
            m_s = new menu_stu;
            m_s->show();
        } else {
            QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("账户密码错误,请重新输入!"), QString::fromLocal8Bit("确认"));
            ui->le_user->clear();
            ui->le_password->clear();
        }
    }
}
