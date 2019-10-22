#include "ms_class.h"
#include "ui_ms_class.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

ms_class::ms_class(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ms_class)
{
    ui->setupUi(this);
    init_UI();
    this->setAttribute(Qt::WA_DeleteOnClose,1); //窗口设置为关闭时,会回收资源

    connect(ui->btn_search,SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(ui->btn_add, SIGNAL(clicked(bool)), this, SLOT(into_add_class()));
    connect(ui->btn_delete, SIGNAL(clicked(bool)), this, SLOT(into_delete_class()));
    connect(ui->btn_modify, SIGNAL(clicked(bool)), this, SLOT(into_modify_class()));
    connect(ui->btn_return, SIGNAL(clicked(bool)), this, SLOT(slot_ret()));
}

ms_class::~ms_class()
{
    delete ui;
}

void ms_class::slot_ret() {
    emit signal_ret();
    this->close();
}

void ms_class::into_add_class() {
    add_c = new add_class;
    this->hide();

    connect(add_c, SIGNAL(signal_ret()), this, SLOT(reshow()));
    add_c->show();
}

void ms_class::into_delete_class() {
    delete_c = new delete_class;
    this->hide();

    connect(delete_c, SIGNAL(signal_ret()), this, SLOT(reshow()));
    delete_c->show();
}

void ms_class::into_modify_class() {
    modify_c = new modify_class;
    this->hide();

    connect(modify_c, SIGNAL(signal_ret()), this, SLOT(reshow()));
    modify_c->show();
}

void ms_class::search() {
    QSqlDatabase db;
    db = QSqlDatabase::database("mysql_connect");
    QSqlQuery query(db);

    if(ui->cmbox_col->currentIndex() == 0) {
        QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请选择查询类型!"), QString::fromLocal8Bit("确认"));
    } else {
        int index = ui->cmbox_col->currentIndex();
        QString str1, str2;
        switch (index) {
        case 1:
            str1 = "classid";
            str2 = ui->le_keyword->text();
            break;
        case 2:
            str1 = "major";
            str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
            break;

        case 3:
            str1 = "classname";
            str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
            break;
        case 4:
            str1 = "memb_num";
            str2 = ui->le_keyword->text();
            break;
        case 5:
            str1 = "headteacher";
            str2 = QString::fromLocal8Bit("'") + ui->le_keyword->text() + QString::fromLocal8Bit("'");
            break;
        default:
            break;
        }

        col = 5;
        int row;
        QString get_row = "select count(classid) from class where "+ str1 + QString::fromLocal8Bit(" = ") + str2;   //获取行数
        query.exec(get_row);
        if(query.first()){
            row = query.value(QString::fromLocal8Bit("count(classid)")).toInt();
            ui->tableWidget->setRowCount(row);
        }
        if (row != 0) {     //如果查询结果不为空
            ui->tableWidget->setColumnCount(col);
            QStringList header; //表头写入表格
            header << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("专业") << QString::fromLocal8Bit("班级名称") << QString::fromLocal8Bit("人数")
                   << QString::fromLocal8Bit("班主任");
            ui->tableWidget->setHorizontalHeaderLabels(header);
            ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度

            QString str = "select * from class where "
                    + str1 + QString::fromLocal8Bit(" = ") + str2;
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

void ms_class::init_UI() {
    ui->cmbox_col->setCurrentIndex(0);
    ui->le_keyword->clear();
    ui->btn_add->setEnabled(true);
    ui->btn_delete->setEnabled(true);
    ui->btn_modify->setEnabled(true);

    col = 5;
    int row = 0;
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    QStringList header; //表头写入表格
    header << QString::fromLocal8Bit("班级号") << QString::fromLocal8Bit("专业") << QString::fromLocal8Bit("班级名称") << QString::fromLocal8Bit("人数")
           << QString::fromLocal8Bit("班主任");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);   //自动调整宽度
}

void ms_class::reshow() {
    this->show();
}
