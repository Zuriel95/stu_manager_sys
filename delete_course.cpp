#include "delete_course.h"
#include "ui_delete_course.h"

delete_course::delete_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_course)
{
    ui->setupUi(this);
}

delete_course::~delete_course()
{
    delete ui;
}
