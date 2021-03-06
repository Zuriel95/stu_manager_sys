﻿#ifndef MODIFY_STU_H
#define MODIFY_STU_H

#include <QDialog>

namespace Ui {
class modify_stu;
}

class modify_stu : public QDialog
{
    Q_OBJECT

public:
    explicit modify_stu(QWidget *parent = nullptr);
    ~modify_stu();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void modify();

private:
    Ui::modify_stu *ui;
};

#endif // MODIFY_STU_H
