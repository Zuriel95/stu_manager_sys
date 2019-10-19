#ifndef MS_SCORE_H
#define MS_SCORE_H

#include <QDialog>

namespace Ui {
class ms_score;
}

class ms_score : public QDialog
{
    Q_OBJECT

public:
    explicit ms_score(QWidget *parent = nullptr);
    ~ms_score();

private:
    Ui::ms_score *ui;
};

#endif // MS_SCORE_H
