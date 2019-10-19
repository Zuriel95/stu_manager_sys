#include "ms_class.h"
#include "ui_ms_class.h"

ms_class::ms_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_class)
{
    ui->setupUi(this);
}

ms_class::~ms_class()
{
    delete ui;
}
