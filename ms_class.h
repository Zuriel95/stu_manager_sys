#ifndef MS_CLASS_H
#define MS_CLASS_H

#include <QDialog>
#include <add_class.h>
#include <delete_class.h>
#include <modify_class.h>
#include <QTableWidgetItem>

namespace Ui {
class ms_class;
}

class ms_class : public QDialog
{
    Q_OBJECT

public:
    explicit ms_class(QWidget *parent = nullptr);
    ~ms_class();
    void init_UI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void search();
    void into_add_class();
    void into_delete_class();
    void into_modify_class();
    void reshow();

private:
    Ui::ms_class *ui;
    add_class *add_c;
    delete_class *delete_c;
    modify_class *modify_c;
    int col;
};

#endif // MS_CLASS_H
