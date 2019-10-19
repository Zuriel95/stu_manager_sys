#include "add_stu.h"
#include "ui_add_stu.h"

add_stu::add_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_stu)
{
    ui->setupUi(this);
}

add_stu::~add_stu()
{
    delete ui;
}
