#include "delete_class.h"
#include "ui_delete_class.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

delete_class::delete_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_class)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_class::~delete_class()
{
    delete ui;
}

void delete_class::slot_ret() {
    emit signal_ret();
    this->close();
}

void delete_class::initUI() {
    ui->le_classid->clear();
}

void delete_class::del() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_classid->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {
        //判断班级号是否存在
        bool exist;
        QString is_exist = "select count(classid) from class where classid = " + ui->le_classid->text();
        query.exec(is_exist);
        if(query.first()) {
            exist = query.value("count(classid)").toBool();
        }
        if(!exist) {  //班级号不存在,提示错误
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("未找到该班级号,请确认后重试"), QString::fromLocal8Bit("确认"));
        } else {
            QString condition = "classid = " + ui->le_classid->text();
            QString str = "delete from class where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}
