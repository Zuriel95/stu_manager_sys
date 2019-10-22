#include "delete_score.h"
#include "ui_delete_score.h"

delete_score::delete_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_score)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_score::~delete_score()
{
    delete ui;
}

void delete_score::slot_ret() {
    emit signal_ret();
    this->close();
}
