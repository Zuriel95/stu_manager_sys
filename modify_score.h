#ifndef MODIFY_SCORE_H
#define MODIFY_SCORE_H

#include <QDialog>

namespace Ui {
class modify_score;
}

class modify_score : public QDialog
{
    Q_OBJECT

public:
    explicit modify_score(QWidget *parent = nullptr);
    ~modify_score();

signals:
    void signal_ret();

private slots:
    void slot_ret();

private:
    Ui::modify_score *ui;
};

#endif // MODIFY_SCORE_H
