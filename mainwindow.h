#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QString>
#include "menu_admin.h"
#include "menu_stu.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connect_mysql();
    bool is_stu();

private slots:
	void login();
private:
    Ui::MainWindow *ui;
    menu_stu *m_s;
    menu_admin *m_a;
	QString user_type;

};

#endif // MAINWINDOW_H
