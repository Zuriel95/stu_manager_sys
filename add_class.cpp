#include "add_class.h"
#include "ui_add_class.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

add_class::add_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_class)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

add_class::~add_class()
{
    delete ui;
}

void add_class::slot_ret() {
    emit signal_ret();
    this->close();
}

void add_class::add() {
    if(ui->le_classid->text() == "" || ui->le_major->text() == "" || ui->le_classname->text() == "" || ui->le_memb_num->text() == ""
            || ui->le_headteacher->text() == "" )    //检查是否填写
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    else {
        QSqlDatabase db = QSqlDatabase::database("mysql_connect");
        QSqlQuery query(db);
        QString str;
        str = "insert into class values( " + ui->le_classid->text() + ", '" + ui->le_major->text() + "', '" + ui->le_classname->text() +
                "', " + ui->le_memb_num->text() + ", '" + ui->le_headteacher->text() + "')";
        query.exec(str);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功!"), QString::fromLocal8Bit("确认"));
        initUI();
    }
}

void add_class::initUI() {
    ui->le_classid->clear();
    ui->le_classid->setMaxLength(8);
    ui->le_major->clear();
    ui->le_major->setMaxLength(30);
    ui->le_classname->clear();
    ui->le_classname->setMaxLength(30);
    ui->le_memb_num->clear();
    ui->le_memb_num->setMaxLength(2);
    ui->le_headteacher->clear();
    ui->le_headteacher->setMaxLength(18);

}
