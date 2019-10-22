#include "delete_stu.h"
#include "ui_delete_stu.h"

delete_stu::delete_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_stu::~delete_stu()
{
    delete ui;
}

void delete_stu::slot_ret(){
    emit signal_ret();
    this->close();
}
