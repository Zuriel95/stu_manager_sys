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
    void initUI();

signals:
    void signal_ret();

private slots:
    void get_stu_id(QString);
    void slot_ret();
    void modify();

private:
    Ui::modify_self *ui;
    QString stu_id;
};

#endif // MODIFY_SELF_H
