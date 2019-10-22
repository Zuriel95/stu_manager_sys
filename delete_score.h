#ifndef DELETE_SCORE_H
#define DELETE_SCORE_H

#include <QDialog>

namespace Ui {
class delete_score;
}

class delete_score : public QDialog
{
    Q_OBJECT

public:
    explicit delete_score(QWidget *parent = nullptr);
    ~delete_score();

signals:
    void signal_ret();

private slots:
    void slot_ret();

private:
    Ui::delete_score *ui;
};

#endif // DELETE_SCORE_H
