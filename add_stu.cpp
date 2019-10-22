#include "add_stu.h"
#include "ui_add_stu.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

add_stu::add_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

add_stu::~add_stu()
{
    delete ui;
}

void add_stu::slot_ret() {
    emit signal_ret();
    this->close();
}

void add_stu::add() {
    if (ui->le_classid->text() == "" || ui->le_name->text() == "" || ui->le_major->text() == ""
            || ui->le_address->text() == "" || ui->le_phone_num->text() == "" || ui->le_dmty_num->text() == ""
            || ui->le_password->text() == "")    //检查是否填写
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,并且除奖惩外不能留有空白!"), QString::fromLocal8Bit("确认"));
    else {          //正确填写则添加至数据库
        if (ui->le_award->text() == "")
            ui->le_award->setText("NULL");
        if (ui->le_punishment->text() == "")
            ui->le_punishment->setText("NULL");
        QSqlDatabase db = QSqlDatabase::database("mysql_connect");
        QSqlQuery query(db);
        QString str;
        str = "insert into stu values( " + ui->le_stu_id->text() + ", '" + ui->le_name->text() + "', '" + ui->sexGroup->checkedButton()->text() + "', '" + ui->le_major->text() + "', " + ui->le_classid->text()
                + ", '" + ui->le_address->text() + "', '" + ui->le_phone_num->text() + "', " + ui->le_dmty_num->text() + ", " + ui->spinBox_bed_num->text()
                + ", '" + ui->le_award->text() + "', '" + ui->le_punishment->text() + "', '" + ui->le_password->text() + "',  " + ui->spinBox_age->text() + ")";
        query.exec(str);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功!"), QString::fromLocal8Bit("确认"));
        initUI();
    }
}

void add_stu::initUI() {
    ui->le_stu_id->clear();
    ui->le_stu_id->setMaxLength(10);
    ui->le_name->clear();
    ui->le_name->setMaxLength(18);
    ui->rbtn_male->setChecked(true);
    ui->le_major->clear();
    ui->le_major->setMaxLength(30);
    ui->le_classid->clear();
    ui->le_classid->setMaxLength(8);
    ui->le_address->clear();
    ui->le_address->setMaxLength(200);
    ui->le_dmty_num->clear();
    ui->le_dmty_num->setMaxLength(4);
    ui->le_award->clear();
    ui->le_award->setMaxLength(200);
    ui->le_punishment->clear();
    ui->le_punishment->setMaxLength(200);
    ui->le_password->clear();
    ui->le_password->setMaxLength(16);

}
