#ifndef MS_COURSE_H
#define MS_COURSE_H

#include <QDialog>
#include <add_course.h>
#include <delete_course.h>
#include <modify_course.h>
#include <QTableWidgetItem>

namespace Ui {
class ms_course;
}

class ms_course : public QDialog
{
    Q_OBJECT

public:
    explicit ms_course(QWidget *parent = nullptr);
    ~ms_course();
    void init_UI();

signals:
    void signal_ret();

private slots:
    void get_isStu(bool);
    void get_stu_id(QString);
    void slot_ret();
    void search();
    void into_add_course();
    void into_delete_course();
    void into_modify_course();
    void reshow();

private:
    Ui::ms_course *ui;
    bool is_stu;
    QString stu_id;
    add_course *add_crs;
    delete_course *delete_crs;
    modify_course *modify_crs;
    int col;
};

#endif // MS_COURSE_H
