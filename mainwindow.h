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
    void clearUI();

signals:
    void send_name(QString);
    void send_stu_id(QString);

private slots:
	void login();
    void reshow();

private:
    Ui::MainWindow *ui;
    menu_admin *m_a;
    menu_stu *m_s;
	QString user_type;
    QString user_name;

};

#endif // MAINWINDOW_H
