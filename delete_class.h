#ifndef DELETE_CLASS_H
#define DELETE_CLASS_H

#include <QDialog>

namespace Ui {
class delete_class;
}

class delete_class : public QDialog
{
    Q_OBJECT

public:
    explicit delete_class(QWidget *parent = nullptr);
    ~delete_class();

private:
    Ui::delete_class *ui;
};

#endif // DELETE_CLASS_H
