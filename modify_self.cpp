#include "modify_self.h"
#include "ui_modify_self.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

modify_self::modify_self(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_self)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    initUI();
    connect(ui->btn_confirm, SIGNAL(clicked(bool)),this, SLOT(modify()));
    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_self::~modify_self()
{
    delete ui;
}

void modify_self::get_stu_id(QString str) {
    stu_id = str;
}

void modify_self::slot_ret() {
    emit signal_ret();
    this->close();
}

void modify_self::initUI() {
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_val->clear();
}

void modify_self::modify() {
    QSqlDatabase db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    //判断是否填写
    if (ui->le_val->text() == "") {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请按格式填写,不能留有空白!"), QString::fromLocal8Bit("确认"));
    } else {

        int index = ui->cmbox_col->currentIndex();
        QString col, val;
        switch (index) {
        case 0:
            col = "name";
            val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
            break;
        case 1:
            col = "age";
            val = ui->le_val->text();
            break;
        case 2:
            col = "address";
            val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
            break;
        case 3:
            col = "phone_num";
            val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
            break;
        case 4:
            col = "password";
            val = QString::fromLocal8Bit("'") + ui->le_val->text() + QString::fromLocal8Bit("'");
            break;
        default:
            break;
        }
        QString str = "update stu set " + col + " = " + val + " where stu_id = " + stu_id;
        query.exec(str);
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("修改成功!"), QString::fromLocal8Bit("确认"));
        initUI();
    }
}

