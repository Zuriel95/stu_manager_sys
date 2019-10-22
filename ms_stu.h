#ifndef MS_STU_H
#define MS_STU_H

#include <QDialog>
#include <add_stu.h>
#include <delete_stu.h>
#include <modify_stu.h>
#include <QTableWidgetItem>

namespace Ui {
class ms_stu;
}

class ms_stu : public QDialog
{
    Q_OBJECT

public:
    explicit ms_stu(QWidget *parent = nullptr);
    ~ms_stu();
    void init_UI();

signals:
    void signal_ret();

private slots:
    void get_isStu(bool);
    void get_stu_id(QString);
    void slot_ret();
    void search();
    void into_add_stu();
    void into_delete_stu();
    void into_modify_stu();
    void reshow();

private:
    Ui::ms_stu *ui;
    bool is_stu;
    QString stu_id;
    add_stu *add_s;
    delete_stu *delete_s;
    modify_stu *modify_s;
    int col;
};

#endif // MS_STU_H
