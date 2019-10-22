#include "delete_class.h"
#include "ui_delete_class.h"

delete_class::delete_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_class)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_class::~delete_class()
{
    delete ui;
}

void delete_class::slot_ret() {
    emit signal_ret();
    this->close();
}
