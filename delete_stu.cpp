#include "delete_stu.h"
#include "ui_delete_stu.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>


delete_stu::delete_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_stu::~delete_stu()
{
    delete ui;
}

void delete_stu::slot_ret(){
    emit signal_ret();
    this->close();
}

void delete_stu::initUI() {
    ui->le_stu_id->clear();
}

void delete_stu::del() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_stu_id->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {
        //判断学号是否存在
        bool has_stu;
        QString is_exist = "select count(stu_id) from stu where stu_id = " + ui->le_stu_id->text();
        query.exec(is_exist);
        if(query.first()) {
            has_stu = query.value("count(stu_id)").toBool();
        }
        if(!has_stu) {  //学号不存在,提示错误
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("未找到该学号,请确认后重试"), QString::fromLocal8Bit("确认"));
        } else {
            QString condition = "stu_id = " + ui->le_stu_id->text();
            QString str = "delete from stu where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }

}
