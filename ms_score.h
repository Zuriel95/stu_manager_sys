#ifndef MS_SCORE_H
#define MS_SCORE_H

#include <QDialog>
#include <add_score.h>
#include <delete_score.h>
#include <modify_score.h>
#include <QTableWidgetItem>

namespace Ui {
class ms_score;
}

class ms_score : public QDialog
{
    Q_OBJECT

public:
    explicit ms_score(QWidget *parent = nullptr);
    ~ms_score();
    void init_UI();

signals:
    void signal_ret();

private slots:
    void get_isStu(bool);
    void get_stu_id(QString);
    void slot_ret();
    void search();
    void into_add_score();
    void into_delete_score();
    void into_modify_score();
    void reshow();


private:
    Ui::ms_score *ui;
    bool is_stu;
    QString stu_id;
    add_score *add_sc;
    delete_score *delete_sc;
    modify_score *modify_sc;
    int col;
};

#endif // MS_SCORE_H
