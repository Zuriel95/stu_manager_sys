#include "ms_score.h"
#include "ui_ms_score.h"

ms_score::ms_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_score)
{
    ui->setupUi(this);
}

ms_score::~ms_score()
{
    delete ui;
}
