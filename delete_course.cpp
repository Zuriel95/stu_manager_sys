#include "delete_course.h"
#include "ui_delete_course.h"

delete_course::delete_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_course)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源


    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

delete_course::~delete_course()
{
    delete ui;
}

void delete_course::slot_ret() {
    emit signal_ret();
    this->close();
}
