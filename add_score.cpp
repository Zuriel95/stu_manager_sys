#include "add_score.h"
#include "ui_add_score.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

add_score::add_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_score)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

add_score::~add_score()
{
    delete ui;
}

void add_score::slot_ret() {
    emit signal_ret();
    this->close();
}

void add_score::add() {
    if(ui->le_stu_id->text() == "" || ui->le_course_name->text() == "" || ui->le_score->text() == "" || ui->le_classid->text() == ""
            || ui->le_teacher->text() == "" || ui->le_name->text() == "")    //检查是否填写
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    else {
        QSqlDatabase db = QSqlDatabase::database("mysql_connect");
        QSqlQuery query(db);
        QString str;
        str = "insert into score values( " + ui->le_stu_id->text() + ", '" + ui->cmbox_term->currentText() +
                "', '" +  ui->le_course_name->text() + "', '"+ ui->le_score->text() + "', " + ui->le_classid->text() + ", '"
                + ui->le_teacher->text() + "', '" + ui->le_name->text() +"')";
        query.exec(str);
        qDebug() << str;
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("添加成功!"), QString::fromLocal8Bit("确认"));
        initUI();
    }
}

void add_score::initUI() {
    ui->le_stu_id->clear();
    ui->le_stu_id->setMaxLength(10);
    ui->cmbox_term->setCurrentIndex(0);
    ui->le_course_name->clear();
    ui->le_course_name->setMaxLength(40);
    ui->le_score->clear();
    ui->le_score->setMaxLength(3);
    ui->le_classid->clear();
    ui->le_classid->setMaxLength(8);
    ui->le_teacher->clear();
    ui->le_teacher->setMaxLength(18);
    ui->le_name->clear();
    ui->le_name->setMaxLength(18);

}
