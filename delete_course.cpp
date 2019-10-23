#include "delete_course.h"
#include "ui_delete_course.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

delete_course::delete_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_course)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_course::~delete_course()
{
    delete ui;
}

void delete_course::slot_ret() {
    emit signal_ret();
    this->close();
}

void delete_course::initUI() {
    ui->le_classid->clear();
    ui->le_course_name->clear();
}

void delete_course::del() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_classid->text() == "" || ui->le_course_name->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {
        //判断待修改项是否存在
        QString condition = "classid = " + ui->le_classid->text() + " and course_name = '" + ui->le_course_name->text() + "'";
        bool exist;
        QString is_exist = "select count(classid) from course where " + condition;
        query.exec(is_exist);
        if(query.first()) {
            exist = query.value("count(classid)").toBool();
        }
        if(!exist) {  //待修改项不存在,提示错误
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("未找到待修改项,请确认后重试"), QString::fromLocal8Bit("确认"));
        } else {
            QString str = "delete from course where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}

