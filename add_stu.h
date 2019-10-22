#ifndef ADD_STU_H
#define ADD_STU_H

#include <QDialog>

namespace Ui {
class add_stu;
}

class add_stu : public QDialog
{
    Q_OBJECT

public:
    explicit add_stu(QWidget *parent = nullptr);
    ~add_stu();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void add();

private:
    Ui::add_stu *ui;
};

#endif // ADD_STU_H
