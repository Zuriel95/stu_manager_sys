#include "ms_stu.h"
#include "ui_ms_stu.h"

ms_stu::ms_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_stu)
{
    ui->setupUi(this);
}

ms_stu::~ms_stu()
{
    delete ui;
}
