#include "modify_class.h"
#include "ui_modify_class.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

modify_class::modify_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_class)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)),this, SLOT(modify()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_class::~modify_class()
{
    delete ui;
}

void modify_class::slot_ret() {
    emit signal_ret();
    this->close();
}

void modify_class::initUI() {
    ui->le_classid->clear();
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_val->clear();
}

void modify_class::modify() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_classid->text() == "" || ui->le_val->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {
        //判断班级号是否存在
        QString condition = "classid = " + ui->le_classid->text();
        bool exist;
        QString is_exist = "select count(classid) from class where " + condition;
        query.exec(is_exist);
        if(query.first()) {
            exist = query.value("count(classid)").toBool();
        }
        if(!exist) {  //班级号不存在,提示错误
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("未找到该班级号,请确认后重试"), QString::fromLocal8Bit("确认"));
        } else {
            int index = ui->cmbox_col->currentIndex();
            QString col, val;
            switch (index) {
            case 0:
                col = "major";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
               case 1:
                col = "classname";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 2:
                col = "memb_num";
                val = ui->le_val->text();
                break;
            case 3:
                col = "headteacher";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            default:
                break;
            }
            QString str = "update class set " + col + " = " + val + " where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}
