#include "menu_admin.h"
#include "ui_menu_admin.h"
#include <QDebug>

menu_admin::menu_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu_admin)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_ms_stu, SIGNAL(clicked(bool)), this, SLOT(into_ms_stu()));
    connect(ui->btn_ms_class, SIGNAL(clicked(bool)), this, SLOT(into_ms_class()));
    connect(ui->btn_ms_course, SIGNAL(clicked(bool)), this, SLOT(into_ms_course()));
    connect(ui->btn_ms_score, SIGNAL(clicked(bool)), this, SLOT(into_ms_score()));
    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

menu_admin::~menu_admin()
{
    delete ui;
}

void menu_admin::slot_ret() {
    emit signal_ret();
    this->close();
}

void menu_admin::get_name(QString str) {
    user_name = str;
    QString string = user_name + QString::fromLocal8Bit(", 欢迎您!");
    ui->lb_welcome->setText(string);
}

bool menu_admin::is_stu() {
    return false;
}

void menu_admin::into_ms_stu() {    //跳转至ms_stu
    this->hide();
    m_stu = new ms_stu;
    connect(m_stu, SIGNAL(signal_ret()), this, SLOT(reshow()));
    connect(this, SIGNAL(send_isStu(bool)), m_stu, SLOT(get_isStu(bool)));
    emit send_isStu(false);
    m_stu->show();
}

void menu_admin::into_ms_class() {  //跳转至ms_class
    this->hide();
    m_class = new ms_class;
    connect(m_class, SIGNAL(signal_ret()), this, SLOT(reshow()));
    m_class->show();
}

void menu_admin::into_ms_course() { //跳转至ms_course
    this->hide();
    m_course = new ms_course;
    connect(m_course, SIGNAL(signal_ret()), this, SLOT(reshow()));
    connect(this, SIGNAL(send_isStu(bool)), m_course, SLOT(get_isStu(bool)));
    emit send_isStu(false);
    m_course->show();
}

void menu_admin::into_ms_score() {  //跳转至ms_score
    this->hide();
    m_score = new ms_score;
    connect(m_score, SIGNAL(signal_ret()), this, SLOT(reshow()));
    connect(this, SIGNAL(send_isStu(bool)), m_score, SLOT(get_isStu(bool)));
    emit send_isStu(false);
    m_score->show();
}

void menu_admin::reshow() {
    this->show();
}
