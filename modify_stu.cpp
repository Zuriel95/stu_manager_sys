#include "modify_stu.h"
#include "ui_modify_stu.h"

modify_stu::modify_stu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_stu::~modify_stu()
{
    delete ui;
}

void modify_stu::slot_ret() {
    emit signal_ret();
    this->close();
}
