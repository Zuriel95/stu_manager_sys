#include "add_course.h"
#include "ui_add_course.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

add_course::add_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_course)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

add_course::~add_course()
{
    delete ui;
}

void add_course::slot_ret() {
    emit signal_ret();
    this->close();
}

void add_course::add() {
    if(ui->le_classid->text() == "" || ui->le_course_name->text() == "" || ui->le_teacher->text() == "" || ui->le_classrom->text() == ""
            || ui->le_period->text() == "" || ui->le_credit->text() == "")    //检查是否填写
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    else {
        QSqlDatabase db = QSqlDatabase::database("mysql_connect");
        QSqlQuery query(db);
        QString str;
        str = "insert into course values( " + ui->le_classid->text() + ", '" + ui->le_course_name->text() + "', '" + ui->cmbox_term->currentText() +
                "', '" + ui->le_teacher->text() + "', '" + ui->le_classrom->text() + "', " + ui->le_period->text() + ", " + ui->le_credit->text() +")";
        query.exec(str);
        qDebug() << str;
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功!"), QString::fromLocal8Bit("确认"));
        initUI();
    }
}

void add_course::initUI() {
    ui->le_classid->clear();
    ui->le_classid->setMaxLength(8);
    ui->le_course_name->clear();
    ui->le_course_name->setMaxLength(40);
    ui->cmbox_term->setCurrentIndex(0);
    ui->le_teacher->clear();
    ui->le_teacher->setMaxLength(18);
    ui->le_classrom->clear();
    ui->le_classrom->setMaxLength(40);
    ui->le_period->clear();
    ui->le_period->setMaxLength(3);
    ui->le_credit->clear();
    ui->le_credit->setMaxLength(2);

}
