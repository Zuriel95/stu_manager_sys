#include "menu_stu.h"
#include "ui_menu_stu.h"
#include <QDebug>

menu_stu::menu_stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu_stu)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源
    //个人信息修改----------------------------待实现
    //    connect(ui->btn_modify_info, SIGNAL(clicked(bool)), this, SLOT(into_ms_stu()));
    connect(ui->btn_ms_stu, SIGNAL(clicked(bool)), this, SLOT(into_ms_stu()));
    connect(ui->btn_ms_course, SIGNAL(clicked(bool)), this, SLOT(into_ms_course()));
    connect(ui->btn_ms_score, SIGNAL(clicked(bool)), this, SLOT(into_ms_score()));
    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));

}

menu_stu::~menu_stu()
{
    delete ui;
}

void menu_stu::slot_ret() {
    emit signal_ret();
    this->close();
}

void menu_stu::get_name(QString str) {
    stu_name = str;
    QString string = stu_name + QString::fromLocal8Bit( "同学, 欢迎您!");
    ui->lb_welcome->setText(string);
}

void menu_stu::get_stu_id(QString str) { //接受父窗口传来的数据
    stu_id = str;
}

bool is_stu() {
    return true;
}

void menu_stu::into_ms_stu() { //跳转至ms_stu 查询本班同学信息
    this->hide();
    m_stu = new ms_stu;
    connect(m_stu, SIGNAL(signal_ret()), this, SLOT(reshow()));

    connect(this, SIGNAL(send_isStu(bool)), m_stu, SLOT(get_isStu(bool)));
    emit send_isStu(true);
    connect(this, SIGNAL(send_stu_id(QString)), m_stu, SLOT(get_stu_id(QString)));
    emit send_stu_id(stu_id);

    m_stu->show();
}



void menu_stu::into_ms_course() { //跳转至ms_course  查询本人课程信息
    this->hide();
    m_course = new ms_course;
    connect(m_course, SIGNAL(signal_ret()), this, SLOT(reshow()));

    connect(this, SIGNAL(send_isStu(bool)), m_course, SLOT(get_isStu(bool)));
    emit send_isStu(true);
    connect(this, SIGNAL(send_stu_id(QString)), m_course, SLOT(get_stu_id(QString)));
    emit send_stu_id(stu_id);

    m_course->show();
}

void menu_stu::into_ms_score() {  //跳转至ms_score  查询本人分数信息
    this->hide();
    m_score = new ms_score;
    connect(m_score, SIGNAL(signal_ret()), this, SLOT(reshow()));

    connect(this, SIGNAL(send_isStu(bool)), m_score, SLOT(get_isStu(bool)));
    emit send_isStu(true);
    connect(this, SIGNAL(send_stu_id(QString)), m_score, SLOT(get_stu_id(QString)));
    emit send_stu_id(stu_id);

    m_score->show();
}

void menu_stu::reshow() {
    this->show();
}
