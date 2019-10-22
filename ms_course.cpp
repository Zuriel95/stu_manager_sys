#include "ms_course.h"
#include "ui_ms_course.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QMessageBox>

ms_course::ms_course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_course)
{
    ui->setupUi(this);

    init_UI();
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_search, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(ui->btn_add, SIGNAL(clicked(bool)), this, SLOT(into_add_course()));
    connect(ui->btn_delete, SIGNAL(clicked(bool)), this, SLOT(into_delete_course()));
    connect(ui->btn_modify, SIGNAL(clicked(bool)), this, SLOT(into_modify_course()));
    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

ms_course::~ms_course()
{
    delete ui;
}

void ms_course::get_isStu(bool flag) {
    is_stu = flag;
    if(is_stu) {    //学生端禁用 添加,删除, 修改按钮
        ui->btn_add->setEnabled(false);
        ui->btn_delete->setEnabled(false);
        ui->btn_modify->setEnabled(false);
    }
}

void ms_course::get_stu_id(QString str) {
    stu_id = str;
}


void ms_course::slot_ret() {
    emit signal_ret();
    this->close();
}

void ms_course::into_add_course() {
    add_crs = new add_course;
    this->hide();

    connect(add_crs, SIGNAL(signal_ret()), this, SLOT(reshow()));
    add_crs->show();

}

void ms_course::into_delete_course() {
    delete_crs = new delete_course;
    this->hide();

    connect(delete_crs, SIGNAL(signal_ret()), this, SLOT(reshow()));
    delete_crs->show();

}

void ms_course::into_modify_course() {
    modify_crs = new modify_course;
    this->hide();

    connect(modify_crs, SIGNAL(signal_ret()), this, SLOT(reshow()));
    modify_crs->show();

}


void ms_course::search() {
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
                str1 = "classid";
                str2 = ui->le_keyword->text();
                break;
            case 2:
                str1 = "course_name";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;

            case 3:
                str1 = "term";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            case 4:
                str1 = "teacher";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            case 5:
                str1 = "classroom";
                str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                break;
            case 6:
                str1 = "period";
                str2 = ui->le_keyword->text();
                break;
            case 7:
                str1 = "credit";
                str2 = ui->le_keyword->text();
                break;
            default:
                break;
            }

            col = 7;
            int row;
            QString get_row = "select count(classid) from course where "+ str1 + QString::fromLocal8Bit(" = ") + str2;   //获取行数
            query.exec(get_row);
            if(query.first()){
                row = query.value(QString::fromLocal8Bit("count(classid)")).toInt();
                ui->tableWidget->setRowCount(row);
            }
            if (row != 0) {     //如果查询结果不为空
                ui->tableWidget->setColumnCount(col);
                QStringList header; //表头写入表格
                header << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("课程名称") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("教师")
                       << QString::fromLocal8Bit("教室") << QString::fromLocal8Bit("学时") << QString::fromLocal8Bit("学分");
                ui->tableWidget->setHorizontalHeaderLabels(header);
                ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

                QString str = "select * from course where "
                        + str1 + QString::fromLocal8Bit(" = ") + str2;
                query.exec(str);

                for (int i = 0; query.next(); i++) {
                    for (int j = 0; j < col; j++) {
                        ui->tableWidget->setItem( i, j, new QTableWidgetItem(query.value(j).toString()));
                    }
                }
            } else
                QMessageBox::information(this, QString::fromLocal8Bit("查询结果"), QString::fromLocal8Bit("未找到相关信息!请更换查询内容后再次尝试!"), QString::fromLocal8Bit("确认"));
        } else {        //学生操作-----查询本人课程信息
            if (ui->cmbox_col->currentIndex() == 1) //不可查询班级号,限制为本班查询
                QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不可查询班级号, 请重新选择!"), QString::fromLocal8Bit("确认"));
            else {                                  //选择正确
                QString get_classid = "select classid from stu where stu_id = " + stu_id;
                query.exec(get_classid);
                QString class_id;
                if (query.first())
                    class_id = query.value("classid").toString();


                int index = ui->cmbox_col->currentIndex();
                QString str1, str2;
                switch (index) {
                case 1: break;
                case 2:
                    str1 = "course_name";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;

                case 3:
                    str1 = "term";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                case 4:
                    str1 = "teacher";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                case 5:
                    str1 = "classroom";
                    str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
                    break;
                case 6:
                    str1 = "period";
                    str2 = ui->le_keyword->text();
                    break;
                case 7:
                    str1 = "credit";
                    str2 = ui->le_keyword->text();
                    break;
                default:
                    break;
                }

                col = 7;
                int row;
                QString get_row = "select count(classid) from course where "+ str1 + QString::fromLocal8Bit(" = ") + str2 + " and classid = " + class_id;   //获取行数
                query.exec(get_row);
                if(query.first()){
                    row = query.value(QString::fromLocal8Bit("count(classid)")).toInt();
                    ui->tableWidget->setRowCount(row);
                }
                if (row != 0) {     //如果查询结果不为空
                    ui->tableWidget->setColumnCount(col);
                    QStringList header; //表头写入表格
                    header << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("课程名称") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("教师")
                           << QString::fromLocal8Bit("教室") << QString::fromLocal8Bit("学时") << QString::fromLocal8Bit("学分");
                    ui->tableWidget->setHorizontalHeaderLabels(header);
                    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

                    QString str = "select * from course where "
                            + str1 + QString::fromLocal8Bit(" = ") + str2 + " and classid = " + class_id;
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

void ms_course::init_UI() {
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_keyword->clear();
    ui->btn_add->setEnabled(true);
    ui->btn_delete->setEnabled(true);
    ui->btn_modify->setEnabled(true);

    int col = 7, row = 0;
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    QStringList header; //表头写入表格
    header << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("课程名称") << QString::fromLocal8Bit("学期") << QString::fromLocal8Bit("教师")
           << QString::fromLocal8Bit("教室") << QString::fromLocal8Bit("学时") << QString::fromLocal8Bit("学分");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

}

void ms_course::reshow() {
    this->show();
}
