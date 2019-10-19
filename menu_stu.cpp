#include "menu_stu.h"
#include "ui_menu_stu.h"

menu_stu::menu_stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu_stu)
{
    ui->setupUi(this);
}

menu_stu::~menu_stu()
{
    delete ui;
}
