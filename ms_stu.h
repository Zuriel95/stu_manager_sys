#ifndef MS_STU_H
#define MS_STU_H

#include <QDialog>

namespace Ui {
class ms_stu;
}

class ms_stu : public QDialog
{
    Q_OBJECT

public:
    explicit ms_stu(QWidget *parent = nullptr);
    ~ms_stu();

private:
    Ui::ms_stu *ui;
};

#endif // MS_STU_H
