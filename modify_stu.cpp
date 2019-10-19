#include "modify_stu.h"
#include "ui_modify_stu.h"

modify_stu::modify_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_stu)
{
    ui->setupUi(this);
}

modify_stu::~modify_stu()
{
    delete ui;
}
