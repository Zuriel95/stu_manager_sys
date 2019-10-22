#include "ms_score.h"
#include "ui_ms_score.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QMessageBox>

ms_score::ms_score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_score)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    init_UI();
    connect(ui->btn_search, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(ui->btn_add, SIGNAL(clicked(bool)), this, SLOT(into_add_score()));
    connect(ui->btn_delete, SIGNAL(clicked(bool)), this, SLOT(into_delete_score()));
    connect(ui->btn_modify, SIGNAL(clicked(bool)), this, SLOT(into_modify_score()));
    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

ms_score::~ms_score()
{
    delete ui;
}

void ms_score::get_isStu(bool flag) {
    is_stu = flag;
    if(is_stu) {    //学生端禁用 添加,删除, 修改按钮
        ui->btn_add->setEnabled(false);
        ui->btn_delete->setEnabled(false);
        ui->btn_modify->setEnabled(false);
    }
}

void ms_score::get_stu_id(QString str) {
    stu_id = str;
}


void ms_score::slot_ret() {
    emit signal_ret();
    this->close();
}

void ms_score::into_add_score() {
    add_sc = new add_score;
    this->hide();

    connect(add_sc, SIGNAL(signal_ret()), this, SLOT(reshow()));
    add_sc->show();

}

void ms_score::into_delete_score() {
    delete_sc = new delete_score;
    this->hide();

    connect(delete_sc, SIGNAL(signal_ret()), this, SLOT(reshow()));
    delete_sc->show();

}

void ms_score::into_modify_score() {
    modify_sc = new modify_score;
    this->hide();

    connect(modify_sc, SIGNAL(signal_ret()), this, SLOT(reshow()));
    modify_sc->show();

}

void ms_score::search() {
    QSqlDatabase db;
    db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    if(ui->cmbox_col->currentIndex() == 0) {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请选择查询类型!"), QString::fromLocal8Bit("确认"));
    } else {
        if (!is_stu) {      //管理员操作
            int index = ui->cmbox_col->currentIndex();
            QString str1, str2;
            switch (index) {
            case 1:
                str1 = "stu_id";
                str2 = ui->le_keyword->text();
                break;
            case 2:
                str1 = "name";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;

            case 3:
                str1 = "term";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            case 4:
                str1 = "course_name";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            case 5:
                str1 = "score";
                str2 = ui->le_keyword->text();
                break;
            case 6:
                str1 = "classid";
                str2 = ui->le_keyword->text();
                break;
            case 7:
                str1 = "teacher";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            default:
                break;
            }

            col = 7;
            int row;
            QString get_row = "select count(stu_id) from score where "+ str1 + QString::fromLocal8Bit(" = ") + str2;   //获取行数
            query.exec(get_row);
            if(query.first()){
                row = query.value(QString::fromLocal8Bit("count(stu_id)")).toInt();
                ui->tableWidget->setRowCount(row);
            }
            if (row != 0) {     //如果查询结果不为空
                ui->tableWidget->setColumnCount(col);
                QStringList header; //表头写入表格
                header << QString::fromLocal8Bit("学号") << QString::fromLocal8Bit("姓名") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("课程名称")
                       << QString::fromLocal8Bit("分数") << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("教师");
                ui->tableWidget->setHorizontalHeaderLabels(header);
                ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

                QString str = "select stu_id, name, term, course_name, score, classid, teacher from score where "
                        + str1 + QString::fromLocal8Bit(" = ") + str2;
                query.exec(str);

                for (int i = 0; query.next(); i++) {
                    for (int j = 0; j < col; j++) {
                        ui->tableWidget->setItem( i, j, new QTableWidgetItem(query.value(j).toString()));
                    }
                }
            } else
                QMessageBox::information(this, QString::fromLocal8Bit("查询结果"), QString::fromLocal8Bit("未找到相关信息!请更换查询内容后再次尝试!"), QString::fromLocal8Bit("确认"));
        } else {        //学生操作-----查询本人信息
            if (ui->cmbox_col->currentIndex() == 1 || ui->cmbox_col->currentIndex() == 6) {//不可查询班级号和学号, 限制为查询本人分数信息
                QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不可查询班级号和学号, 请重新选择!"), QString::fromLocal8Bit("确认"));
            } else {

                int index = ui->cmbox_col->currentIndex();
                QString str1, str2;
                switch (index) {
                case 1:
                    str1 = "stu_id";
                    str2 = ui->le_keyword->text();
                    break;
                case 2:
                    str1 = "name";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;

                case 3:
                    str1 = "term";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                case 4:
                    str1 = "course_name";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                case 5:
                    str1 = "score";
                    str2 = ui->le_keyword->text();
                    break;
                case 6:
                    str1 = "classid";
                    str2 = ui->le_keyword->text();
                    break;
                case 7:
                    str1 = "teacher";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                default:
                    break;
                }

                col = 7;
                int row;
                QString get_row = "select count(stu_id) from score where "+ str1 + QString::fromLocal8Bit(" = ") + str2 + " and stu_id = " + stu_id;   //获取行数
                query.exec(get_row);
                if(query.first()){
                    row = query.value(QString::fromLocal8Bit("count(stu_id)")).toInt();
                    ui->tableWidget->setRowCount(row);
                }
                if (row != 0) {     //如果查询结果不为空
                    ui->tableWidget->setColumnCount(col);
                    QStringList header; //表头写入表格
                    header << QString::fromLocal8Bit("学号") << QString::fromLocal8Bit("姓名") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("课程名称")
                           << QString::fromLocal8Bit("分数") << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("教师");
                    ui->tableWidget->setHorizontalHeaderLabels(header);
                    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

                    QString str = "select stu_id, name, term, course_name, score, classid, teacher from score where "
                            + str1 + QString::fromLocal8Bit(" = ") + str2 + " and stu_id = " + stu_id;
                    query.exec(str);

                    for (int i = 0; query.next(); i++) {
                        for (int j = 0; j < col; j++) {
                            ui->tableWidget->setItem( i, j, new QTableWidgetItem(query.value(j).toString()));
                        }
                    }
                } else
                    QMessageBox::information(this, QString::fromLocal8Bit("查询结果"), QString::fromLocal8Bit("未找到相关信息!请更换查询内容后再次尝试!"), QString::fromLocal8Bit("确认"));
            }
        }
    }
}

void ms_score::init_UI() {
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_keyword->clear();
    ui->btn_add->setEnabled(true);
    ui->btn_delete->setEnabled(true);
    ui->btn_modify->setEnabled(true);

    int col = 7, row = 0;
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    QStringList header; //表头写入表格
    header << QString::fromLocal8Bit("学号") << QString::fromLocal8Bit("姓名") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("课程名称")
           << QString::fromLocal8Bit("分数") << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("教师");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度
}

void ms_score::reshow() {
    this->show();
}
