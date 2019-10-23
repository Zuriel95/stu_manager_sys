#include "modify_score.h"
#include "ui_modify_score.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

modify_score::modify_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_score)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)),this, SLOT(modify()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));

}

modify_score::~modify_score()
{
    delete ui;
}

void modify_score::slot_ret() {
    emit signal_ret();
    this->close();
}

void modify_score::initUI() {
    ui->le_stu_id->clear();
    ui->le_course_name->clear();
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_val->clear();
}

void modify_score::modify() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_stu_id->text() == "" || ui->le_course_name->text() == "" || ui->le_val->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {
        //判断待修改项是否存在
        QString condition = "stu_id = " + ui->le_stu_id->text() + " and course_name = '" + ui->le_course_name->text() + "'";
        bool exist;
        QString is_exist = "select count(stu_id) from score where " + condition;
        query.exec(is_exist);
        if(query.first()) {
            exist = query.value("count(stu_id)").toBool();
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
                col = "score";
                val = ui->le_val->text();
                break;
            case 2:
                col = "classid";
                val = ui->le_val->text();
                break;
            case 3:
                col = "teacher";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            default:
                break;
            }
            QString str = "update score set " + col + " = " + val + " where " + condition;
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}
