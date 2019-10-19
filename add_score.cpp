#include "add_score.h"
#include "ui_add_score.h"

add_score::add_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_score)
{
    ui->setupUi(this);
}

add_score::~add_score()
{
    delete ui;
}
