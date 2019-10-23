#include "modify_stu.h"
#include "ui_modify_stu.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

modify_stu::modify_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)),this, SLOT(modify()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_stu::~modify_stu()
{
    delete ui;
}

void modify_stu::slot_ret() {
    emit signal_ret();
    this->close();
}

void modify_stu::initUI() {
    ui->le_stu_id->clear();
    ui->le_val->clear();
    ui->cmbox_col->setCurrentIndex(0);
}

void modify_stu::modify() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_stu_id->text() == "" || ui->le_val->text() == "") {
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
            int index = ui->cmbox_col->currentIndex();
            QString col, val;
            switch (index) {
            case 0:
                col = "name";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 1:
                col = "sex";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 2:
                col = "age";
                val = ui->le_val->text();
                break;
            case 3:
                col = "major";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 4:
                col = "classid";
                val = ui->le_val->text();
                break;
            case 5:
                col = "address";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 6:
                col = "phone_num";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 7:
                col = "dmty";
                val = ui->le_val->text();
                break;
            case 8:
                col = "bed_num";
                val = ui->le_val->text();
                break;
            case 9:
                col = "award";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
            case 10:
                col = "punishment";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            case 11:
                col = "password";
                val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
                break;
            default:
                break;
            }
            QString str = "update stu set " + col + " = " + val + " where stu_id = " + ui->le_stu_id->text();
            query.exec(str);
            QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
            initUI();
        }
    }
}
