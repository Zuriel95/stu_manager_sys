#ifndef DELETE_STU_H
#define DELETE_STU_H

#include <QDialog>

namespace Ui {
class delete_stu;
}

class delete_stu : public QDialog
{
    Q_OBJECT

public:
    explicit delete_stu(QWidget *parent = nullptr);
    ~delete_stu();

private:
    Ui::delete_stu *ui;
};

#endif // DELETE_STU_H
