#include "modify_course.h"
#include "ui_modify_course.h"

modify_course::modify_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_course)
{
    ui->setupUi(this);
}

modify_course::~modify_course()
{
    delete ui;
}
