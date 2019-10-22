#include "modify_course.h"
#include "ui_modify_course.h"

modify_course::modify_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_course)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源


    connect(ui->btn_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

modify_course::~modify_course()
{
    delete ui;
}

void modify_course::slot_ret() {
    emit signal_ret();
    this->close();
}
