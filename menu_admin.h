#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include <QWidget>
#include <ms_stu.h>
#include <ms_class.h>
#include <ms_course.h>
#include <ms_score.h>

namespace Ui {
class menu_admin;
}

class menu_admin : public QWidget
{
    Q_OBJECT

public:
    explicit menu_admin(QWidget *parent = nullptr);
    ~menu_admin();
    bool is_stu();

private slots:
    void slot_ret();
    void get_name(QString);
    void into_ms_stu();
    void into_ms_class();
    void into_ms_course();
    void into_ms_score();
    void reshow();

signals:
    void signal_ret();
    void send_isStu(bool);

private:
    Ui::menu_admin *ui;
    QString user_name;
    ms_stu *m_stu;
    ms_class *m_class;
    ms_course *m_course;
    ms_score *m_score;
};

#endif // MENU_ADMIN_H
