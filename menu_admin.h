#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include <QWidget>

namespace Ui {
class menu_admin;
}

class menu_admin : public QWidget
{
    Q_OBJECT

public:
    explicit menu_admin(QWidget *parent = nullptr);
    ~menu_admin();

private:
    Ui::menu_admin *ui;
};

#endif // MENU_ADMIN_H
