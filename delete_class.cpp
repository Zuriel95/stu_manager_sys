#include "delete_class.h"
#include "ui_delete_class.h"

delete_class::delete_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_class)
{
    ui->setupUi(this);
}

delete_class::~delete_class()
{
    delete ui;
}
