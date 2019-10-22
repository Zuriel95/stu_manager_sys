#include "modify_class.h"
#include "ui_modify_class.h"

modify_class::modify_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_class)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_class::~modify_class()
{
    delete ui;
}

void modify_class::slot_ret() {
    emit signal_ret();
    this->close();
}
