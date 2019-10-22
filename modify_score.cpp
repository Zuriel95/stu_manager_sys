#include "modify_score.h"
#include "ui_modify_score.h"

modify_score::modify_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_score)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));

}

modify_score::~modify_score()
{
    delete ui;
}

void modify_score::slot_ret() {
    emit signal_ret();
    this->close();
}
