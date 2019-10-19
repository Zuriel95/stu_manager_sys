#ifndef MODIFY_COURSE_H
#define MODIFY_COURSE_H

#include <QDialog>

namespace Ui {
class modify_course;
}

class modify_course : public QDialog
{
    Q_OBJECT

public:
    explicit modify_course(QWidget *parent = nullptr);
    ~modify_course();

private:
    Ui::modify_course *ui;
};

#endif // MODIFY_COURSE_H
