#ifndef MS_COURSE_H
#define MS_COURSE_H

#include <QDialog>

namespace Ui {
class ms_course;
}

class ms_course : public QDialog
{
    Q_OBJECT

public:
    explicit ms_course(QWidget *parent = nullptr);
    ~ms_course();

private:
    Ui::ms_course *ui;
};

#endif // MS_COURSE_H
