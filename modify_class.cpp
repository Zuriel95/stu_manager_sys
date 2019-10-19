#include "modify_class.h"
#include "ui_modify_class.h"

modify_class::modify_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_class)
{
    ui->setupUi(this);
}

modify_class::~modify_class()
{
    delete ui;
}
