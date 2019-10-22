#ifndef ADD_CLASS_H
#define ADD_CLASS_H

#include <QDialog>

namespace Ui {
class add_class;
}

class add_class : public QDialog
{
    Q_OBJECT

public:
    explicit add_class(QWidget *parent = nullptr);
    ~add_class();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void add();

private:
    Ui::add_class *ui;
};

#endif // ADD_CLASS_H
