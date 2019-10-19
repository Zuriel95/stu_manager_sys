#include "ms_course.h"
#include "ui_ms_course.h"

ms_course::ms_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_course)
{
    ui->setupUi(this);
}

ms_course::~ms_course()
{
    delete ui;
}
