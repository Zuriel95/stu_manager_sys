#include "modify_score.h"
#include "ui_modify_score.h"

modify_score::modify_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_score)
{
    ui->setupUi(this);
}

modify_score::~modify_score()
{
    delete ui;
}
