#include "modify_course.h"
#include "ui_modify_course.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

modify_course::modify_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_course)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)),this, SLOT(modify()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_course::~modify_course()
{
    delete ui;
}

void modify_course::slot_ret() {
    emit signal_ret();
    this->close();
}

void modify_course::initUI() {
    ui->le_classid->clear();
    ui->le_course_name->clear();
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_val->clear();
}

void modify_course::modify() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_classid->text() == "" || ui->le_course_name->text() == "" || ui->le_val->text() == "") {
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
            int index = ui->cmbox_col->currentIndex();
            QString col, val;
            switch (index) {
            case 0:
                col = "term";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
               case 1:
                col = "teacher";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 2:
                col = "classroom";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 3:
                col = "period";
                val = ui->le_val->text();
                break;
            case 4:
                col = "credit";
                val = ui->le_val->text();
                break;
            default:
                break;
            }
            QString str = "update course set " + col + " = " + val + " where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}
