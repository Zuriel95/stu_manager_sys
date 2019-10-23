#ifndef MENU_STU_H
#define MENU_STU_H

#include <QWidget>
#include <ms_stu.h>
#include <ms_class.h>
#include <ms_course.h>
#include <ms_score.h>
#include <modify_self.h>

namespace Ui {
class menu_stu;
}

class menu_stu : public QWidget
{
    Q_OBJECT

public:
    explicit menu_stu(QWidget *parent = nullptr);
    ~menu_stu();
    bool is_stu();

private slots:
    void slot_ret();
    void get_name(QString);
    void get_stu_id(QString);
    void into_ms_stu();
    void into_ms_course();
    void into_ms_score();
    void reshow();
    void mdf_self();

signals:
    void signal_ret();
    void send_isStu(bool);
    void send_stu_id(QString);

private:
    Ui::menu_stu *ui;
    QString stu_id;
    QString stu_name;
    ms_stu *m_stu;
    ms_course *m_course;
    ms_score *m_score;
    modify_self *m_self;
};

#endif // MENU_STU_H
