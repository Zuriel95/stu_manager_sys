#ifndef MODIFY_SELF_H
#define MODIFY_SELF_H

#include <QDialog>

namespace Ui {
class modify_self;
}

class modify_self : public QDialog
{
    Q_OBJECT

public:
    explicit modify_self(QWidget *parent = nullptr);
    ~modify_self();

private:
    Ui::modify_self *ui;
};

#endif // MODIFY_SELF_H
