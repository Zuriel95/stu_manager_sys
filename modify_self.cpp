#include "modify_self.h"
#include "ui_modify_self.h"

modify_self::modify_self(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_self)
{
    ui->setupUi(this);
}

modify_self::~modify_self()
{
    delete ui;
}
