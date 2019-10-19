#include "delete_stu.h"
#include "ui_delete_stu.h"

delete_stu::delete_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_stu)
{
    ui->setupUi(this);
}

delete_stu::~delete_stu()
{
    delete ui;
}
