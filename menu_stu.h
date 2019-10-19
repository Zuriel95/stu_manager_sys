#ifndef MENU_STU_H
#define MENU_STU_H

#include <QWidget>

namespace Ui {
class menu_stu;
}

class menu_stu : public QWidget
{
    Q_OBJECT

public:
    explicit menu_stu(QWidget *parent = nullptr);
    ~menu_stu();

private:
    Ui::menu_stu *ui;
};

#endif // MENU_STU_H
