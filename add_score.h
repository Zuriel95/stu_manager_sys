#ifndef ADD_SCORE_H
#define ADD_SCORE_H

#include <QDialog>

namespace Ui {
class add_score;
}

class add_score : public QDialog
{
    Q_OBJECT

public:
    explicit add_score(QWidget *parent = nullptr);
    ~add_score();
    void initUI();

signals:
    void signal_ret();

private slots:
    void slot_ret();
    void add();


private:
    Ui::add_score *ui;
};

#endif // ADD_SCORE_H
