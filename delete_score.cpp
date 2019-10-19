#include "delete_score.h"
#include "ui_delete_score.h"

delete_score::delete_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_score)
{
    ui->setupUi(this);
}

delete_score::~delete_score()
{
    delete ui;
}
