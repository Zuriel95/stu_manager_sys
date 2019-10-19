#ifndef MS_CLASS_H
#define MS_CLASS_H

#include <QDialog>

namespace Ui {
class ms_class;
}

class ms_class : public QDialog
{
    Q_OBJECT

public:
    explicit ms_class(QWidget *parent = nullptr);
    ~ms_class();

private:
    Ui::ms_class *ui;
};

#endif // MS_CLASS_H
