#ifndef MODIFY_CLASS_H
#define MODIFY_CLASS_H

#include <QDialog>

namespace Ui {
class modify_class;
}

class modify_class : public QDialog
{
    Q_OBJECT

public:
    explicit modify_class(QWidget *parent = nullptr);
    ~modify_class();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void modify();
private:
    Ui::modify_class *ui;
};

#endif // MODIFY_CLASS_H
