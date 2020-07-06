#include "adminwindow.h"
#include "ui_adminwindow.h"

#include "mainwindow.h"

#include <QPainter>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QSqlQuery>

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    initAdminwindow();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

//给用户界面添加可以缩放背景图片
void AdminWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/image/images/adminbackground.jpg"));
}

void AdminWindow::on_logout_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认退出管理员吗?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        this->close();
        MainWindow *mw = new MainWindow();
        mw->setWindowTitle("航空机票预订系统");
        mw->show();
    }
    else
    {

    }
}

//初始化管理员界面
void AdminWindow::initAdminwindow()
{
    //order_cen_show();                                       //显示订单中心订单相关信息

    //my_home_show();                                         //显示个人中心机票相关信息

    ui->flight_date_que_radioButton->setChecked(true);              //初始化为单程城市航班查询

    ui->flight_date_dateEdit->setCalendarPopup(true);       //设置dateedit显示日历
    QDate local(QDate::currentDate());
    ui->flight_date_dateEdit->setDate(local);               //设置日历为当前日期

    ui->flight_info_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->order_info_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->pasnger_info_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->flight_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->order_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pasnger_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->flight_num_lineEdit->setReadOnly(true);             //设置flight_num_edit不可编辑
}

void AdminWindow::on_menu_order_info_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->order_info_page);
}

void AdminWindow::on_menu_pasnger_info_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pasnger_info_page);
}

void AdminWindow::on_menu_flight_info_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->flight_info_page);
}

//清理flight_que_table
void AdminWindow::clear_flight_info_table()
{
    ui->flight_info_tableWidget->clearContents();
    ui->flight_info_tableWidget->setRowCount(0);

    //ui->flight_info_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->flight_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}

//清理order_info_table
void AdminWindow::clear_order_info_table()
{
    ui->order_info_tableWidget->clearContents();
    ui->order_info_tableWidget->setRowCount(0);

    //ui->flight_info_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->flight_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}

//清理pasnger_info_table
void AdminWindow::clear_pasnger_info_table()
{
    ui->pasnger_info_tableWidget->clearContents();
    ui->pasnger_info_tableWidget->setRowCount(0);

    //ui->flight_info_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->flight_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}

/****************************************************************************************航班信息功能****************************************************************************/
//按航班日期查询_radioButton
void AdminWindow::on_flight_date_que_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("航班日期查询");

    ui->flight_num_lineEdit->setReadOnly(true);

    ui->flight_date_dateEdit->setReadOnly(false);

    ui->flight_num_lineEdit->clear();

    clear_flight_info_table();
}

//按航班号查询_radioButton
void AdminWindow::on_flight_num_que_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("航班号查询");

    ui->flight_num_lineEdit->setReadOnly(false);

    ui->flight_date_dateEdit->setReadOnly(true);

    ui->flight_num_lineEdit->clear();

    clear_flight_info_table();
}

//航班号查询 || 航班日期查询_pushButton
void AdminWindow::on_flight_que_pushButton_clicked()
{
    flight_date_que();

    flight_num_que();
}

//航班日期查询
void AdminWindow::flight_date_que()
{
    clear_flight_info_table();

    if(ui->flight_que_pushButton->text() == "航班日期查询")
    {
        QString flight_to_date = ui->flight_date_dateEdit->date().toString("yyyy-MM-dd");

        QSqlTableModel flight_date_model;
        flight_date_model.setTable("flight_info");
        flight_date_model.setFilter(tr("f_to_date = '%1'").arg(flight_to_date));
        flight_date_model.select();
        int rowcount = flight_date_model.rowCount();
        if( rowcount >= 1)
        {
            for(int i = 0 ; i < rowcount; i++)
            {
                f_num = flight_date_model.data(flight_date_model.index(i, 0)).toString();
                f_price = flight_date_model.data(flight_date_model.index(i, 1)).toString();
                f_to_date = flight_date_model.data(flight_date_model.index(i, 2)).toString();
                f_ar_date = flight_date_model.data(flight_date_model.index(i, 3)).toString();
                f_to_time = flight_date_model.data(flight_date_model.index(i, 4)).toString();
                f_dis = flight_date_model.data(flight_date_model.index(i, 5)).toString();
                f_type = flight_date_model.data(flight_date_model.index(i, 6)).toString();
                f_cro_city = flight_date_model.data(flight_date_model.index(i, 7)).toString();
                f_take_city = flight_date_model.data(flight_date_model.index(i, 8)).toString();
                f_ar_city = flight_date_model.data(flight_date_model.index(i, 9)).toString();

                int table_row = ui->flight_info_tableWidget->rowCount();
                ui->flight_info_tableWidget->insertRow(table_row);

                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->flight_info_tableWidget->setItem(table_row,0,check); //插入复选框

                ui->flight_info_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                ui->flight_info_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                ui->flight_info_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                ui->flight_info_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                ui->flight_info_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                ui->flight_info_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                ui->flight_info_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                ui->flight_info_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                ui->flight_info_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                ui->flight_info_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));

                ui->flight_info_tableWidget->item(i,1)->setFlags(ui->flight_info_tableWidget->item(i,1)->flags() & (~Qt::ItemIsEditable)); //设置第一列内容不可编辑
            }
        }
        else
        {
            QMessageBox::about(NULL, "提示", "未查询到该日期相关航班信息!");
            clear_flight_info_table();
        }
    }
}

//航班号查询功能
void AdminWindow::flight_num_que()
{
    if(ui->flight_que_pushButton->text() == "航班号查询")
    {
        QString flight_num = ui->flight_num_lineEdit->text();
        if(flight_num.isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请输入航班号!");
        }
        else
        {
            QSqlTableModel flight_num_model;
            flight_num_model.setTable("flight_info");
            flight_num_model.setFilter(tr("f_num = '%1'").arg(flight_num));
            flight_num_model.select();
            int rowcount = flight_num_model.rowCount();
            if( rowcount == 1)
            {
                f_num = flight_num_model.data(flight_num_model.index(0, 0)).toString();
                f_price = flight_num_model.data(flight_num_model.index(0, 1)).toString();
                f_to_date = flight_num_model.data(flight_num_model.index(0, 2)).toString();
                f_ar_date = flight_num_model.data(flight_num_model.index(0, 3)).toString();
                f_to_time = flight_num_model.data(flight_num_model.index(0, 4)).toString();
                f_dis = flight_num_model.data(flight_num_model.index(0, 5)).toString();
                f_type = flight_num_model.data(flight_num_model.index(0, 6)).toString();
                f_cro_city = flight_num_model.data(flight_num_model.index(0, 7)).toString();
                f_take_city = flight_num_model.data(flight_num_model.index(0, 8)).toString();
                f_ar_city = flight_num_model.data(flight_num_model.index(0, 9)).toString();

                int table_row = ui->flight_info_tableWidget->rowCount();
                ui->flight_info_tableWidget->insertRow(table_row);

                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->flight_info_tableWidget->setItem(table_row,0,check); //插入复选框

                ui->flight_info_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                ui->flight_info_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                ui->flight_info_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                ui->flight_info_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                ui->flight_info_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                ui->flight_info_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                ui->flight_info_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                ui->flight_info_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                ui->flight_info_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                ui->flight_info_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));

                ui->flight_info_tableWidget->item(0,1)->setFlags(ui->flight_info_tableWidget->item(0,1)->flags() & (~Qt::ItemIsEditable)); //设置一列内容不可编辑
            }
            else
            {
                QMessageBox::about(NULL, "提示", "未查询到该航班相关信息!");
                ui->flight_num_lineEdit->clear();
                ui->flight_num_lineEdit->setFocus();
                clear_flight_info_table();
            }
        }
    }
}

//航班信息修改功能
void AdminWindow::on_flight_change_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->flight_info_tableWidget->rowCount(); i++)
    {
        if(ui->flight_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要修改的航班!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认修改该航班信息吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                b_f_flight_num = ui->flight_info_tableWidget->item(info_list.at(i), 1)->text().toUtf8();
                f_flight_num = b_f_flight_num.data();

                QSqlTableModel flight_info_model;
                flight_info_model.setTable("flight_info");
                flight_info_model.setFilter(tr("f_num = '%1'").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                flight_info_model.select();
                int rowcount = flight_info_model.rowCount();
                if( rowcount == 1)
                {
                    b_f_flight_price = ui->flight_info_tableWidget->item(info_list.at(i),2)->text().toUtf8();
                    b_f_flight_to_date = ui->flight_info_tableWidget->item(info_list.at(i),3)->text().toUtf8();
                    b_f_flight_ar_date= ui->flight_info_tableWidget->item(info_list.at(i),4)->text().toUtf8();
                    b_f_flight_to_time = ui->flight_info_tableWidget->item(info_list.at(i),5)->text().toUtf8();
                    b_f_flight_dis = ui->flight_info_tableWidget->item(info_list.at(i),6)->text().toUtf8();
                    b_f_flight_type = ui->flight_info_tableWidget->item(info_list.at(i),7)->text().toUtf8();
                    b_f_flight_cro_city = ui->flight_info_tableWidget->item(info_list.at(i),10)->text().toUtf8();
                    b_f_flight_to_city = ui->flight_info_tableWidget->item(info_list.at(i),8)->text().toUtf8();
                    b_f_flight_ar_city = ui->flight_info_tableWidget->item(info_list.at(i),9)->text().toUtf8();


                    f_flight_price = b_f_flight_price.data();
                    f_flight_to_date = b_f_flight_to_date.data();
                    f_flight_ar_date = b_f_flight_ar_date.data();
                    f_flight_to_time = b_f_flight_to_time.data();
                    f_flight_dis = b_f_flight_dis.data();
                    f_flight_type = b_f_flight_type.data();
                    f_flight_cro_city = b_f_flight_cro_city.data();
                    f_flight_to_city = b_f_flight_to_city.data();
                    f_flight_ar_city = b_f_flight_ar_city.data();

                    QString str = QString("update flight_info set f_price='%1', f_to_date='%2', f_ar_date='%3', f_to_time='%4', f_dis='%5', f_type='%6', f_cro_city='%7', f_take_city='%8', f_ar_city='%9' where f_num='%10'")
                                                  .arg(f_flight_price).arg(f_flight_to_date).arg(f_flight_ar_date).arg(f_flight_to_time).arg(f_flight_dis).arg(f_flight_type).arg(f_flight_cro_city)
                                                    .arg(f_flight_to_city).arg(f_flight_ar_city).arg(f_flight_num);

                    QSqlQuery query;
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("修改航班%1成功!").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                        ui->flight_info_tableWidget->item(info_list.at(i), 0)->setCheckState(Qt::Unchecked);
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("修改航班%1失败!").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消航班修改!");
        }
    }
    flight_date_que();
    flight_num_que();
}

//航班信息删除功能
void AdminWindow::on_flight_delete_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->flight_info_tableWidget->rowCount(); i++)
    {
        if(ui->flight_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要删除的航班!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认删除该航班吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                b_f_flight_num = ui->flight_info_tableWidget->item(info_list.at(i), 1)->text().toUtf8();
                f_flight_num = b_f_flight_num.data();

                QSqlTableModel flight_info_model;
                flight_info_model.setTable("flight_info");
                flight_info_model.setFilter(tr("f_num = '%1'").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                flight_info_model.select();
                int rowcount = flight_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString str = QString("delete from flight_info where f_num='%1'").arg(f_flight_num);

                    QSqlQuery query;
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("删除航班%1成功!").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                        ui->flight_info_tableWidget->item(info_list.at(i), 0)->setCheckState(Qt::Unchecked);
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("删除航班%1失败!").arg(ui->flight_info_tableWidget->item(info_list.at(i), 1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消航班删除!");
        }
    }
    flight_date_que();
    flight_num_que();
}
/****************************************************************************************航班信息功能****************************************************************************/

/****************************************************************************************订单信息功能****************************************************************************/
//订单查询功能
void AdminWindow::on_order_que_pushButton_clicked()
{
    clear_order_info_table();

    //ui->order_info_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分

    ui->order_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->order_info_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //设置每行内容不可编辑
    //ui->order_info_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选择行为，以行为单位

    order_num = ui->order_num_lineEdit->text();
    QSqlTableModel order_info_model;
    order_info_model.setTable("order_info");
    order_info_model.setFilter(tr("order_num = '%1'").arg(order_num));
    order_info_model.select();

    if(order_info_model.rowCount() == 1)
    {
        order_flight_num = order_info_model.data(order_info_model.index(0, 1)).toString();
        order_u_tel = order_info_model.data(order_info_model.index(0, 2)).toString();
        order_u_name = order_info_model.data(order_info_model.index(0, 3)).toString();
        order_pay_state = order_info_model.data(order_info_model.index(0, 4)).toString();
        order_flight_date = order_info_model.data(order_info_model.index(0, 5)).toString();
        order_flight_time = order_info_model.data(order_info_model.index(0, 6)).toString();
        order_flight_to_city = order_info_model.data(order_info_model.index(0, 7)).toString();
        order_flight_ar_city = order_info_model.data(order_info_model.index(0, 8)).toString();
        order_flight_price = order_info_model.data(order_info_model.index(0, 9)).toString();
        order_time = order_info_model.data(order_info_model.index(0, 10)).toString();
        order_pay_time = order_info_model.data(order_info_model.index(0, 11)).toString();

        int table_row = ui->order_info_tableWidget->rowCount();
        ui->order_info_tableWidget->insertRow(table_row);

        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->order_info_tableWidget->setItem(table_row,0,check); //插入复选框

        ui->order_info_tableWidget->setItem(table_row, 1, new QTableWidgetItem(order_num));
        ui->order_info_tableWidget->setItem(table_row, 2, new QTableWidgetItem(order_flight_num));
        ui->order_info_tableWidget->setItem(table_row, 3, new QTableWidgetItem(order_u_tel));
        ui->order_info_tableWidget->setItem(table_row, 4, new QTableWidgetItem(order_u_name));
        ui->order_info_tableWidget->setItem(table_row, 5, new QTableWidgetItem(order_pay_state));
        ui->order_info_tableWidget->setItem(table_row, 6, new QTableWidgetItem(order_flight_date));
        ui->order_info_tableWidget->setItem(table_row, 7, new QTableWidgetItem(order_flight_time));
        ui->order_info_tableWidget->setItem(table_row, 8, new QTableWidgetItem(order_flight_to_city));
        ui->order_info_tableWidget->setItem(table_row, 9, new QTableWidgetItem(order_flight_ar_city));
        ui->order_info_tableWidget->setItem(table_row, 10, new QTableWidgetItem(order_flight_price));
        ui->order_info_tableWidget->setItem(table_row, 11, new QTableWidgetItem(order_time));
        ui->order_info_tableWidget->setItem(table_row, 12, new QTableWidgetItem(order_pay_time));

        ui->order_info_tableWidget->item(0,1)->setFlags(ui->order_info_tableWidget->item(0,1)->flags() & (~Qt::ItemIsEditable)); //设置订单号列内容不可编辑
        ui->order_info_tableWidget->item(0,5)->setFlags(ui->order_info_tableWidget->item(0,5)->flags() & (~Qt::ItemIsEditable)); //设置付款状态列内容不可编辑
    }
    else
    {
        QMessageBox::about(NULL, "提示", "未查询到该订单!");
    }
}

//订单修改功能
void AdminWindow::on_order_change_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->order_info_tableWidget->rowCount(); i++)
    {
        if(ui->order_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要修改的订单!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认修改该订单吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                b_order_num = ui->order_info_tableWidget->item(info_list.at(i), 1)->text().toUtf8();
                c_order_num = b_order_num.data();

                QSqlTableModel order_info_model;
                order_info_model.setTable("order_info");
                order_info_model.setFilter(tr("order_num = '%1'").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                order_info_model.select();
                int rowcount = order_info_model.rowCount();
                if( rowcount == 1)
                {
                    b_order_flight_num = ui->order_info_tableWidget->item(info_list.at(i),2)->text().toUtf8();
                    b_order_u_tel = ui->order_info_tableWidget->item(info_list.at(i),3)->text().toUtf8();
                    b_order_u_name = ui->order_info_tableWidget->item(info_list.at(i),4)->text().toUtf8();
                    b_order_pay_state = ui->order_info_tableWidget->item(info_list.at(i),5)->text().toUtf8();
                    b_order_flight_date = ui->order_info_tableWidget->item(info_list.at(i),6)->text().toUtf8();
                    b_order_flight_time = ui->order_info_tableWidget->item(info_list.at(i),7)->text().toUtf8();
                    b_order_flight_to_city = ui->order_info_tableWidget->item(info_list.at(i),8)->text().toUtf8();
                    b_order_flight_ar_city = ui->order_info_tableWidget->item(info_list.at(i),9)->text().toUtf8();
                    b_order_flight_price = ui->order_info_tableWidget->item(info_list.at(i),10)->text().toUtf8();
                    b_order_time = ui->order_info_tableWidget->item(info_list.at(i),11)->text().toUtf8();
                    b_order_pay_time = ui->order_info_tableWidget->item(info_list.at(i),12)->text().toUtf8();

                    c_order_flight_num = b_order_flight_num.data();
                    c_order_u_tel = b_order_u_tel.data();
                    c_order_u_name = b_order_u_name.data();
                    c_order_pay_state = b_order_pay_state.data();
                    c_order_flight_date = b_order_flight_date.data();
                    c_order_flight_time = b_order_flight_time.data();
                    c_order_flight_to_city = b_order_flight_to_city.data();
                    c_order_flight_ar_city = b_order_flight_ar_city.data();
                    c_order_flight_price = b_order_flight_price.data();
                    c_order_time = b_order_time.data();
                    c_order_pay_time = b_order_pay_time.data();

                    QString str = QString("update order_info set order_flight_num='%1', order_u_tel='%2', order_u_name='%3', order_pay_state='%4', order_flight_date='%5', order_flight_time='%6', order_flight_to_city='%7', order_flight_ar_city='%8', order_flight_price='%9', order_time='%10', order_pay_time='%11' where order_num='%12'")
                                                  .arg(c_order_flight_num).arg(c_order_u_tel).arg(c_order_u_name).arg(c_order_pay_state)
                                                  .arg(c_order_flight_date).arg(c_order_flight_time).arg(c_order_flight_to_city)
                                                  .arg(c_order_flight_ar_city).arg(c_order_flight_price).arg(c_order_time)
                                                  .arg(c_order_pay_time).arg(c_order_num);

                    QSqlQuery query;
                    qDebug() << query.exec(str);
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("修改订单%1成功!").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                        ui->order_info_tableWidget->item(info_list.at(i), 0)->setCheckState(Qt::Unchecked);
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("修改订单%1失败!").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消订单修改!");
        }
    }
    on_order_que_pushButton_clicked();
}

//删除订单功能
void AdminWindow::on_order_del_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->order_info_tableWidget->rowCount(); i++)
    {
        if(ui->order_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要删除的订单!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认删除该订单吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                b_order_num = ui->order_info_tableWidget->item(info_list.at(i), 1)->text().toUtf8();
                c_order_num = b_order_num.data();

                QSqlTableModel order_info_model;
                order_info_model.setTable("order_info");
                order_info_model.setFilter(tr("order_num = '%1'").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                order_info_model.select();
                int rowcount = order_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString str = QString("delete from order_info where order_num='%1'").arg(c_order_num);

                    QSqlQuery query;
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("删除订单%1成功!").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                        clear_order_info_table();
                        ui->order_num_lineEdit->clear();
                        ui->order_num_lineEdit->setFocus();

                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("删除订单%1失败!").arg(ui->order_info_tableWidget->item(info_list.at(i), 1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消订单删除!");
        }
    }
}


/****************************************************************************************订单信息功能****************************************************************************/

/****************************************************************************************旅客信息功能****************************************************************************/
//查询旅客信息功能
void AdminWindow::on_pasnger_info_que_pushButton_clicked()
{
    clear_pasnger_info_table();

    //ui->order_info_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分

    ui->pasnger_info_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->order_info_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //设置每行内容不可编辑
    //ui->order_info_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选择行为，以行为单位

    user_tel = ui->tel_num_lineEdit->text();
    QSqlTableModel user_info_model;
    user_info_model.setTable("user_info");
    user_info_model.setFilter(tr("u_tel = '%1'").arg(user_tel));
    user_info_model.select();

    if(user_info_model.rowCount() == 1)
    {
        user_name = user_info_model.data(user_info_model.index(0, 0)).toString();
        user_IDcard = user_info_model.data(user_info_model.index(0, 1)).toString();
        user_pwd = user_info_model.data(user_info_model.index(0, 3)).toString();

        int table_row = ui->pasnger_info_tableWidget->rowCount();
        ui->pasnger_info_tableWidget->insertRow(table_row);

        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->pasnger_info_tableWidget->setItem(table_row,0,check); //插入复选框

        ui->pasnger_info_tableWidget->setItem(table_row, 1, new QTableWidgetItem(user_name));
        ui->pasnger_info_tableWidget->setItem(table_row, 2, new QTableWidgetItem(user_IDcard));
        ui->pasnger_info_tableWidget->setItem(table_row, 3, new QTableWidgetItem(user_tel));
        ui->pasnger_info_tableWidget->setItem(table_row, 4, new QTableWidgetItem(user_pwd));

        ui->pasnger_info_tableWidget->item(0,3)->setFlags(ui->pasnger_info_tableWidget->item(0,3)->flags() & (~Qt::ItemIsEditable)); //设置旅客手机号列内容不可编辑

    }
    else
    {
        QMessageBox::about(NULL, "提示", "未查询到该用户信息!");
    }
}

//修改旅客信息功能
void AdminWindow::on_pasnger_info_change_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->pasnger_info_tableWidget->rowCount(); i++)
    {
        if(ui->pasnger_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要修改的旅客!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认修改该旅客吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                QSqlTableModel user_info_model;
                user_info_model.setTable("user_info");
                user_info_model.setFilter(tr("u_tel = '%1'").arg(ui->pasnger_info_tableWidget->item(info_list.at(i), 3)->text()));
                user_info_model.select();
                int rowcount = user_info_model.rowCount();
                if( rowcount == 1)
                {
                    b_user_name = ui->pasnger_info_tableWidget->item(info_list.at(i),1)->text().toUtf8();
                    b_user_IDcard = ui->pasnger_info_tableWidget->item(info_list.at(i),2)->text().toUtf8();
                    b_user_tel = ui->pasnger_info_tableWidget->item(info_list.at(i), 3)->text().toUtf8();
                    b_user_pwd = ui->pasnger_info_tableWidget->item(info_list.at(i),4)->text().toUtf8();

                    c_user_name = b_user_name.data();
                    c_user_IDcard = b_user_IDcard.data();
                    c_user_tel = b_user_tel.data();
                    c_user_pwd = b_user_pwd.data();

                    QString str = QString("update user_info set u_name='%1', u_IDCard='%2', u_pwd='%3' where u_tel='%4'")
                                            .arg(c_user_name).arg(c_user_IDcard)
                                            .arg(c_user_pwd).arg(c_user_tel);

                    QSqlQuery query;
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("修改旅客%1成功!").arg(ui->pasnger_info_tableWidget->item(info_list.at(i),1)->text()));
                        ui->pasnger_info_tableWidget->item(info_list.at(i), 0)->setCheckState(Qt::Unchecked);
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("修改旅客%1失败!").arg(ui->pasnger_info_tableWidget->item(info_list.at(i),1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消旅客修改!");
        }
    }
    on_pasnger_info_que_pushButton_clicked();
}

//旅客信息删除
void AdminWindow::on_pasnger_info_del_pushButton_clicked()
{
    QList<int> info_list;

    for(int i = 0; i < ui->pasnger_info_tableWidget->rowCount(); i++)
    {
        if(ui->pasnger_info_tableWidget->item(i, 0)->checkState())
        {
           info_list << i;
        }
    }
    if(info_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要删除的旅客!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认删除该旅客吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < info_list.length(); i++)
            {
                b_user_tel = ui->pasnger_info_tableWidget->item(info_list.at(i), 3)->text().toUtf8();
                c_user_tel = b_user_tel.data();

                QSqlTableModel user_info_model;
                user_info_model.setTable("user_info");
                user_info_model.setFilter(tr("u_tel = '%1'").arg( ui->pasnger_info_tableWidget->item(info_list.at(i), 3)->text()));
                user_info_model.select();
                int rowcount = user_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString str = QString("delete from user_info where u_tel='%1'").arg(c_user_tel);

                    QSqlQuery query;
                    if(query.exec(str))
                    {
                        QMessageBox::about(NULL, "提示", QString("删除旅客%1成功!").arg(ui->pasnger_info_tableWidget->item(info_list.at(i), 1)->text()));
                        clear_pasnger_info_table();
                        ui->tel_num_lineEdit->clear();
                        ui->tel_num_lineEdit->setFocus();
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("删除旅客%1失败!").arg(ui->pasnger_info_tableWidget->item(info_list.at(i), 1)->text()));
                    }
                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消删除旅客!");
        }
    }
}
/****************************************************************************************旅客信息功能****************************************************************************/

