#include "add_course.h"
#include "ui_add_course.h"

add_course::add_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_course)
{
    ui->setupUi(this);
}

add_course::~add_course()
{
    delete ui;
}
