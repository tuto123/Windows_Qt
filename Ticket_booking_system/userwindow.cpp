#include "userwindow.h"
#include "ui_userwindow.h"

#include "mainwindow.h"

#include <QPainter>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QSqlQuery>

QString ac_user_tel;

UserWindow::UserWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    initUser_info();

    initUserwindow();

}

UserWindow::~UserWindow()
{
    delete ui;
}

//给用户界面添加可以缩放背景图片
void UserWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/image/images/userbackground1.jpg"));
}

//初始化用户界面
void UserWindow::initUserwindow()
{
    //order_cen_show();                                       //显示订单中心订单相关信息

    //my_home_show();                                         //显示个人中心机票相关信息

    ui->one_way_radioButton->setChecked(true);              //初始化为单程城市航班查询

    ui->flight_date_dateEdit->setCalendarPopup(true);       //设置dateedit显示日历
    QDate local(QDate::currentDate());
    ui->flight_date_dateEdit->setDate(local);               //设置日历为当前日期

    ui->flight_que_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->order_cen_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->my_home_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->flight_que_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->my_home_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->flight_num_lineEdit->setReadOnly(true);             //设置flight_num_edit不可编辑
    ui->flight_date_dateEdit->setReadOnly(true);            //设置dateedit不可编辑

    if(ui->ch_des_city_comboBox->currentText() == "热门")
    {
        ui->des_city_comboBox->insertItem(0,  "北京");
        ui->des_city_comboBox->insertItem(1,  "上海");
        ui->des_city_comboBox->insertItem(2,  "广州");
        ui->des_city_comboBox->insertItem(3,  "深圳");
        ui->des_city_comboBox->insertItem(4,  "成都");
        ui->des_city_comboBox->insertItem(5,  "杭州");
        ui->des_city_comboBox->insertItem(6,  "西安");
        ui->des_city_comboBox->insertItem(7,  "重庆");
        ui->des_city_comboBox->insertItem(8,  "青岛");
        ui->des_city_comboBox->insertItem(9,  "南京");
        ui->des_city_comboBox->insertItem(10, "厦门");
        ui->des_city_comboBox->insertItem(11, "昆明");
        ui->des_city_comboBox->insertItem(12, "大连");
        ui->des_city_comboBox->insertItem(13, "天津");
        ui->des_city_comboBox->insertItem(14, "郑州");
        ui->des_city_comboBox->insertItem(15, "三亚");
        ui->des_city_comboBox->insertItem(16, "济南");
        ui->des_city_comboBox->insertItem(17, "福州");
    }

    if(ui->ch_lev_city_comboBox->currentText() == "热门")
    {
        ui->lev_city_comboBox->insertItem(0,  "北京");
        ui->lev_city_comboBox->insertItem(1,  "上海");
        ui->lev_city_comboBox->insertItem(2,  "广州");
        ui->lev_city_comboBox->insertItem(3,  "深圳");
        ui->lev_city_comboBox->insertItem(4,  "成都");
        ui->lev_city_comboBox->insertItem(5,  "杭州");
        ui->lev_city_comboBox->insertItem(6,  "西安");
        ui->lev_city_comboBox->insertItem(7,  "重庆");
        ui->lev_city_comboBox->insertItem(8,  "青岛");
        ui->lev_city_comboBox->insertItem(9,  "南京");
        ui->lev_city_comboBox->insertItem(10, "厦门");
        ui->lev_city_comboBox->insertItem(11, "昆明");
        ui->lev_city_comboBox->insertItem(12, "大连");
        ui->lev_city_comboBox->insertItem(13, "天津");
        ui->lev_city_comboBox->insertItem(14, "郑州");
        ui->lev_city_comboBox->insertItem(15, "三亚");
        ui->lev_city_comboBox->insertItem(16, "济南");
        ui->lev_city_comboBox->insertItem(17, "福州");
    }
}

//初始化用户信息
void UserWindow::initUser_info()
{

    user_tel = ac_user_tel;
    QSqlTableModel user_info_model;
    user_info_model.setTable("user_info");
    user_info_model.setFilter(tr("u_tel = '%1'").arg(user_tel));
    user_info_model.select();
    int rowcount = user_info_model.rowCount();
    if( rowcount == 1)
    {
        user_name = user_info_model.data(user_info_model.index(0, 0)).toString();
    }
    qDebug() << user_name;
}

//清理flight_que_table
void UserWindow::clear_flight_que_table()
{
    ui->flight_que_tableWidget->clearContents();
    ui->flight_que_tableWidget->setRowCount(0);

    //ui->flight_que_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->flight_que_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}

//清理order_cen_table
void UserWindow::clear_order_cen_table()
{
    ui->order_cen_tableWidget->clearContents();
    ui->order_cen_tableWidget->setRowCount(0);

    //ui->order_cen_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}

//清理_my_home_table
void UserWindow::clear_my_home_table()
{
    ui->my_home_tableWidget->clearContents();
    ui->my_home_tableWidget->setRowCount(0);

    //ui->order_cen_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分
}


//菜单_个人中心
void UserWindow::on_menu_my_home_pushButton_clicked()
{
    my_home_show();
    ui->stackedWidget->setCurrentWidget(ui->my_home_page);
}

//菜单_订单中心
void UserWindow::on_menu_order_cen_pushButton_clicked()
{
    order_cen_show();
    ui->stackedWidget->setCurrentWidget(ui->order_cen_page);

}

//菜单_航班查询
void UserWindow::on_menu_flight_que_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->flight_que_page);
}

//退出登录功能
void UserWindow::on_logout_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认退出系统吗?", QMessageBox::Yes | QMessageBox::No);
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
/****************************************************************************************航班查询及下单功能****************************************************************************/
//单程城市查询_radioButton
void UserWindow::on_one_way_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("单程城市航班查询");

    ui->flight_num_lineEdit->setReadOnly(true);

    ui->flight_date_dateEdit->setReadOnly(true);

    ui->lev_city_comboBox->setEnabled(true);

    ui->des_city_comboBox->setEnabled(true);

    ui->flight_num_lineEdit->clear();

    clear_flight_que_table();
}

//双程城市查询_radioButton
void UserWindow::on_two_way_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("双程城市航班查询");

    ui->flight_num_lineEdit->setReadOnly(true);

    ui->flight_date_dateEdit->setReadOnly(true);

    ui->lev_city_comboBox->setEnabled(true);

    ui->des_city_comboBox->setEnabled(true);

    ui->flight_num_lineEdit->clear();

    clear_flight_que_table();
}

//按航班号查询_radioButton
void UserWindow::on_flight_num_que_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("航班号查询");

    ui->flight_num_lineEdit->setReadOnly(false);

    ui->flight_date_dateEdit->setReadOnly(true);

    ui->ch_lev_city_comboBox->setEnabled(false);

    ui->ch_des_city_comboBox->setEnabled(false);

    ui->lev_city_comboBox->setEnabled(false);

    ui->des_city_comboBox->setEnabled(false);

    ui->flight_num_lineEdit->clear();

    clear_flight_que_table();
}


//按航班日期查询_radioButton
void UserWindow::on_flight_date_que_radioButton_clicked()
{
    ui->flight_que_pushButton->setText("航班日期查询");

    ui->flight_num_lineEdit->setReadOnly(true);

    ui->flight_date_dateEdit->setReadOnly(false);

    ui->ch_lev_city_comboBox->setEnabled(false);

    ui->ch_des_city_comboBox->setEnabled(false);

    ui->lev_city_comboBox->setEnabled(false);

    ui->des_city_comboBox->setEnabled(false);

    ui->flight_num_lineEdit->clear();

    clear_flight_que_table();
}

// 单程_双程_航班号查询 || 航班号查询 || 航班日期查询_pushButton
void UserWindow::on_flight_que_pushButton_clicked()
{
    ui->flight_que_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //设置每行内容不可编辑
    ui->flight_que_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选择行为，以行为单位

    flight_city_que();

    flight_num_que();

    flight_date_que();
}

//单程 || 双程_航班号查询功能
void UserWindow::flight_city_que()
{
    clear_flight_que_table();

    if(ui->flight_que_pushButton->text() == "单程城市航班查询")
    {
        QString one_way_lev_city = ui->lev_city_comboBox->currentText();
        QString one_way_des_city = ui->des_city_comboBox->currentText();

        if(one_way_lev_city.isEmpty() || one_way_des_city.isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请选择始发地及目的城市城市!");
        }
        else
        {
            QSqlTableModel flight_one_way_city_model;
            flight_one_way_city_model.setTable("flight_info");
            flight_one_way_city_model.setFilter(tr("f_take_city = '%1' and f_ar_city = '%2'").arg(one_way_lev_city).arg(one_way_des_city));
            flight_one_way_city_model.select();
            int rowcount = flight_one_way_city_model.rowCount();

            if( rowcount >= 1)
            {
                for(int i = 0 ; i < rowcount; i++)
                {
                    f_num = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 0)).toString();
                    f_price = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 1)).toString();
                    f_to_date = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 2)).toString();
                    f_ar_date = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 3)).toString();
                    f_to_time = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 4)).toString();
                    f_dis = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 5)).toString();
                    f_type = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 6)).toString();
                    f_cro_city = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 7)).toString();
                    f_take_city = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 8)).toString();
                    f_ar_city = flight_one_way_city_model.data(flight_one_way_city_model.index(i, 9)).toString();


                    int table_row = ui->flight_que_tableWidget->rowCount();
                    ui->flight_que_tableWidget->insertRow(table_row);

                    QTableWidgetItem *check = new QTableWidgetItem();
                    check->setCheckState(Qt::Unchecked);
                    ui->flight_que_tableWidget->setItem(table_row,0,check); //插入复选框

                    ui->flight_que_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                    ui->flight_que_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                    ui->flight_que_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                    ui->flight_que_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                    ui->flight_que_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                    ui->flight_que_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                    ui->flight_que_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                    ui->flight_que_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                    ui->flight_que_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                    ui->flight_que_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));
                }
            }
            else
            {
                QMessageBox::about(NULL, "提示", "未查询到单程城市相关航班信息!");
                clear_flight_que_table();
            }
        }
    }

    if(ui->flight_que_pushButton->text() == "双程城市航班查询")
    {
        QString two_way_lev_city = ui->lev_city_comboBox->currentText();
        QString two_way_des_city = ui->des_city_comboBox->currentText();

        if(two_way_lev_city.isEmpty() || two_way_des_city.isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请选择始发地城市!");
        }
        else
        {
            QSqlTableModel flight_two_way_go_city_model;
            flight_two_way_go_city_model.setTable("flight_info");
            flight_two_way_go_city_model.setFilter(tr("f_take_city = '%1' and f_ar_city = '%2'").arg(two_way_lev_city).arg(two_way_des_city));
            flight_two_way_go_city_model.select();

            int take_rowcount = flight_two_way_go_city_model.rowCount();
            if( take_rowcount >= 1)
            {
                for(int i = 0 ; i < take_rowcount; i++)
                {
                    f_num = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 0)).toString();
                    f_price = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 1)).toString();
                    f_to_date = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 2)).toString();
                    f_ar_date = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 3)).toString();
                    f_to_time = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 4)).toString();
                    f_dis = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 5)).toString();
                    f_type = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 6)).toString();
                    f_cro_city = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 7)).toString();
                    f_take_city = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 8)).toString();
                    f_ar_city = flight_two_way_go_city_model.data(flight_two_way_go_city_model.index(i, 9)).toString();

                    int table_row = ui->flight_que_tableWidget->rowCount();
                    ui->flight_que_tableWidget->insertRow(table_row);

                    QTableWidgetItem *check = new QTableWidgetItem();
                    check->setCheckState(Qt::Unchecked);
                    ui->flight_que_tableWidget->setItem(table_row,0,check); //插入复选框

                    ui->flight_que_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                    ui->flight_que_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                    ui->flight_que_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                    ui->flight_que_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                    ui->flight_que_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                    ui->flight_que_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                    ui->flight_que_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                    ui->flight_que_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                    ui->flight_que_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                    ui->flight_que_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));
                }
            }

            QSqlTableModel flight_two_way_bc_city_model;
            flight_two_way_bc_city_model.setTable("flight_info");
            flight_two_way_bc_city_model.setFilter(tr("f_take_city = '%1' and f_ar_city = '%2'").arg(two_way_des_city).arg(two_way_lev_city));
            flight_two_way_bc_city_model.select();

            int ar_rowcount = flight_two_way_bc_city_model.rowCount();
            if( ar_rowcount >= 1)
            {
                for(int i = 0 ; i < ar_rowcount; i++)
                {
                    f_num = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 0)).toString();
                    f_price = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 1)).toString();
                    f_to_date = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 2)).toString();
                    f_ar_date = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 3)).toString();
                    f_to_time = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 4)).toString();
                    f_dis = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 5)).toString();
                    f_type = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 6)).toString();
                    f_cro_city = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 7)).toString();
                    f_take_city = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 8)).toString();
                    f_ar_city = flight_two_way_bc_city_model.data(flight_two_way_bc_city_model.index(i, 9)).toString();

                    int table_row = ui->flight_que_tableWidget->rowCount();
                    ui->flight_que_tableWidget->insertRow(table_row);

                    QTableWidgetItem *check = new QTableWidgetItem();
                    check->setCheckState(Qt::Unchecked);
                    ui->flight_que_tableWidget->setItem(table_row,0,check); //插入复选框

                    ui->flight_que_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                    ui->flight_que_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                    ui->flight_que_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                    ui->flight_que_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                    ui->flight_que_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                    ui->flight_que_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                    ui->flight_que_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                    ui->flight_que_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                    ui->flight_que_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                    ui->flight_que_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));
                }
            }
            else
            {
                QMessageBox::about(NULL, "提示", "未查询到双程城市相关航班信息!");
                clear_flight_que_table();
            }
        }
    }
}

//航班号查询功能
void UserWindow::flight_num_que()
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

                int table_row = ui->flight_que_tableWidget->rowCount();
                ui->flight_que_tableWidget->insertRow(table_row);

                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->flight_que_tableWidget->setItem(table_row,0,check); //插入复选框

                ui->flight_que_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                ui->flight_que_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                ui->flight_que_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                ui->flight_que_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                ui->flight_que_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                ui->flight_que_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                ui->flight_que_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                ui->flight_que_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                ui->flight_que_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                ui->flight_que_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));
            }
            else
            {
                QMessageBox::about(NULL, "提示", "未查询到该航班相关信息!");
                ui->flight_num_lineEdit->clear();
                ui->flight_num_lineEdit->setFocus();
                clear_flight_que_table();
            }
        }
    }
}


//航班日期查询
void UserWindow::flight_date_que()
{
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

                int table_row = ui->flight_que_tableWidget->rowCount();
                ui->flight_que_tableWidget->insertRow(table_row);

                QTableWidgetItem *check = new QTableWidgetItem();
                check->setCheckState(Qt::Unchecked);
                ui->flight_que_tableWidget->setItem(table_row,0,check); //插入复选框

                ui->flight_que_tableWidget->setItem(table_row, 1, new QTableWidgetItem(f_num));
                ui->flight_que_tableWidget->setItem(table_row, 2, new QTableWidgetItem(f_price));
                ui->flight_que_tableWidget->setItem(table_row, 3, new QTableWidgetItem(f_to_date));
                ui->flight_que_tableWidget->setItem(table_row, 4, new QTableWidgetItem(f_ar_date));
                ui->flight_que_tableWidget->setItem(table_row, 5, new QTableWidgetItem(f_to_time));
                ui->flight_que_tableWidget->setItem(table_row, 6, new QTableWidgetItem(f_dis));
                ui->flight_que_tableWidget->setItem(table_row, 7, new QTableWidgetItem(f_type));
                ui->flight_que_tableWidget->setItem(table_row, 8, new QTableWidgetItem(f_take_city));
                ui->flight_que_tableWidget->setItem(table_row, 9, new QTableWidgetItem(f_ar_city));
                ui->flight_que_tableWidget->setItem(table_row, 10, new QTableWidgetItem(f_cro_city));
            }
        }
        else
        {
            QMessageBox::about(NULL, "提示", "未查询到该日期相关航班信息!");
            clear_flight_que_table();
        }
    }
}

//订票功能
void UserWindow::on_ticket_book_pushButton_clicked()
{
    QList<int> order_list;
    for(int i = 0; i < ui->flight_que_tableWidget->rowCount(); i++)
    {
        if(ui->flight_que_tableWidget->item(i, 0)->checkState())
        {
           order_list << i;
        }
    }
    if(order_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择要订票的航班!");
    }
    for(int i = 0; i < order_list.length(); i++)
    {
       QDateTime local(QDateTime::currentDateTime());
       QString localtime = local.toString("hh:mm:ss");
       QString ordertime = local.toString("hhmmss");
       QString localdate = local.toString("yyyyMMdd");

       b_order_flight_num = ui->flight_que_tableWidget->item(order_list.at(i),1)->text().toUtf8();
       b_order_flight_date = ui->flight_que_tableWidget->item(order_list.at(i),3)->text().toUtf8();
       b_order_flight_time = ui->flight_que_tableWidget->item(order_list.at(i),5)->text().toUtf8();
       b_order_flight_price = ui->flight_que_tableWidget->item(order_list.at(i),6)->text().toUtf8();
       b_order_flight_to_city = ui->flight_que_tableWidget->item(order_list.at(i),8)->text().toUtf8();
       b_order_flight_ar_city = ui->flight_que_tableWidget->item(order_list.at(i),9)->text().toUtf8();
       b_order_name = user_name.toUtf8();
       b_order_u_tel = user_tel.toUtf8();
       b_order_pay_state = QString("未支付").toUtf8();
       b_order_time = localtime.toUtf8();
       b_order_num = (user_tel + localdate + ordertime).toUtf8();

       f_order_flight_num = b_order_flight_num.data();
       f_order_flight_price = b_order_flight_price.data();
       f_order_flight_date = b_order_flight_date.data();
       f_order_flight_time = b_order_flight_time.data();
       f_order_flight_to_city = b_order_flight_to_city.data();
       f_order_flight_ar_city = b_order_flight_ar_city.data();
       f_order_name = b_order_name.data();
       f_order_u_tel = b_order_u_tel.data();
       f_order_pay_state = b_order_pay_state.data();
       f_order_time = b_order_time.data();
       f_order_num = b_order_num.data();

       QString str = QString("insert into order_info(order_num, order_flight_num, order_u_tel, order_u_name, order_pay_state, order_flight_date, order_flight_time, order_flight_to_city, order_flight_ar_city, order_flight_price, order_time)   \
                             values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11')")                                                                  \
                             .arg(f_order_num).arg(f_order_flight_num).arg(f_order_u_tel).arg(f_order_name).arg(f_order_pay_state)
                             .arg(f_order_flight_date).arg(f_order_flight_time).arg(f_order_flight_to_city)
                             .arg(f_order_flight_ar_city).arg(f_order_flight_price).arg(f_order_time);
       QSqlQuery query;
       if(query.exec(str))
       {
           QMessageBox::about(NULL, "提示", QString("订单%1下单成功,可到订单中心查看订单!").arg(user_tel + localdate + ordertime));
           ui->flight_que_tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
       }
       else
       {
           QMessageBox::about(NULL, "提示", "下单失败!");
       }
    }

}

//按条件ch_查询始发城市_comboBox
void UserWindow::on_ch_lev_city_comboBox_activated(const QString &arg1)
{
    ui->lev_city_comboBox->clear();

    if(arg1 == "热门")
    {
        ui->lev_city_comboBox->insertItem(0,  "北京");
        ui->lev_city_comboBox->insertItem(1,  "上海");
        ui->lev_city_comboBox->insertItem(2,  "广州");
        ui->lev_city_comboBox->insertItem(3,  "深圳");
        ui->lev_city_comboBox->insertItem(4,  "成都");
        ui->lev_city_comboBox->insertItem(5,  "杭州");
        ui->lev_city_comboBox->insertItem(6,  "西安");
        ui->lev_city_comboBox->insertItem(7,  "重庆");
        ui->lev_city_comboBox->insertItem(8,  "青岛");
        ui->lev_city_comboBox->insertItem(9,  "南京");
        ui->lev_city_comboBox->insertItem(10, "厦门");
        ui->lev_city_comboBox->insertItem(11, "昆明");
        ui->lev_city_comboBox->insertItem(12, "大连");
        ui->lev_city_comboBox->insertItem(13, "天津");
        ui->lev_city_comboBox->insertItem(14, "郑州");
        ui->lev_city_comboBox->insertItem(15, "三亚");
        ui->lev_city_comboBox->insertItem(16, "济南");
        ui->lev_city_comboBox->insertItem(17, "福州");
    }
    else if(arg1 == "ABCDE")
    {
        ui->lev_city_comboBox->insertItem(0,  "阿尔山");
        ui->lev_city_comboBox->insertItem(1,  "阿克苏");
        ui->lev_city_comboBox->insertItem(2,  "阿拉善右旗");
        ui->lev_city_comboBox->insertItem(3,  "阿拉善左旗");
        ui->lev_city_comboBox->insertItem(4,  "阿勒泰");
        ui->lev_city_comboBox->insertItem(5,  "阿里");
        ui->lev_city_comboBox->insertItem(6,  "澳门");
        ui->lev_city_comboBox->insertItem(7,  "安庆");
        ui->lev_city_comboBox->insertItem(8,  "安顺");
        ui->lev_city_comboBox->insertItem(9,  "鞍山");
        ui->lev_city_comboBox->insertItem(10, "巴彦淖尔");
        ui->lev_city_comboBox->insertItem(11, "百色");
        ui->lev_city_comboBox->insertItem(12, "包头");
        ui->lev_city_comboBox->insertItem(13, "保山");
        ui->lev_city_comboBox->insertItem(14, "北海");
        ui->lev_city_comboBox->insertItem(15, "北京");
        ui->lev_city_comboBox->insertItem(16, "白城");
        ui->lev_city_comboBox->insertItem(17, "白山");
        ui->lev_city_comboBox->insertItem(18, "毕节");
        ui->lev_city_comboBox->insertItem(19, "博乐");
        ui->lev_city_comboBox->insertItem(20, "重庆");
        ui->lev_city_comboBox->insertItem(21, "昌都");
        ui->lev_city_comboBox->insertItem(22, "常德");
        ui->lev_city_comboBox->insertItem(23, "常州");
        ui->lev_city_comboBox->insertItem(24, "朝阳");
        ui->lev_city_comboBox->insertItem(25, "成都");
        ui->lev_city_comboBox->insertItem(26, "池州");
        ui->lev_city_comboBox->insertItem(27, "赤峰");
        ui->lev_city_comboBox->insertItem(28, "揭阳");
        ui->lev_city_comboBox->insertItem(29, "长春");
        ui->lev_city_comboBox->insertItem(30, "长沙");
        ui->lev_city_comboBox->insertItem(31, "长治");
        ui->lev_city_comboBox->insertItem(32, "承德");
        ui->lev_city_comboBox->insertItem(33, "沧源");
        ui->lev_city_comboBox->insertItem(34, "达县");
        ui->lev_city_comboBox->insertItem(35, "大理");
        ui->lev_city_comboBox->insertItem(36, "大连");
        ui->lev_city_comboBox->insertItem(37, "大庆");
        ui->lev_city_comboBox->insertItem(38, "大同");
        ui->lev_city_comboBox->insertItem(39, "丹东");
        ui->lev_city_comboBox->insertItem(40, "稻城");
        ui->lev_city_comboBox->insertItem(41, "东营");
        ui->lev_city_comboBox->insertItem(42, "敦煌");
        ui->lev_city_comboBox->insertItem(43, "芒市");
        ui->lev_city_comboBox->insertItem(44, "额济纳旗");
        ui->lev_city_comboBox->insertItem(45, "鄂尔多斯");
        ui->lev_city_comboBox->insertItem(46, "恩施");
        ui->lev_city_comboBox->insertItem(47, "二连浩特");
    }
    else if(arg1 == "FGHIJ")
    {
        ui->lev_city_comboBox->insertItem(0,  "佛山");
        ui->lev_city_comboBox->insertItem(1,  "福州");
        ui->lev_city_comboBox->insertItem(2,  "抚远");
        ui->lev_city_comboBox->insertItem(3,  "阜阳");
        ui->lev_city_comboBox->insertItem(4,  "赣州");
        ui->lev_city_comboBox->insertItem(5,  "格尔木");
        ui->lev_city_comboBox->insertItem(6,  "固原");
        ui->lev_city_comboBox->insertItem(7,  "广元");
        ui->lev_city_comboBox->insertItem(8,  "广州");
        ui->lev_city_comboBox->insertItem(9,  "贵阳");
        ui->lev_city_comboBox->insertItem(10, "桂林");
        ui->lev_city_comboBox->insertItem(11, "哈尔滨");
        ui->lev_city_comboBox->insertItem(12, "哈密");
        ui->lev_city_comboBox->insertItem(13, "海口");
        ui->lev_city_comboBox->insertItem(14, "海拉尔");
        ui->lev_city_comboBox->insertItem(15, "邯郸");
        ui->lev_city_comboBox->insertItem(16, "汉中");
        ui->lev_city_comboBox->insertItem(17, "杭州");
        ui->lev_city_comboBox->insertItem(18, "合肥");
        ui->lev_city_comboBox->insertItem(19, "和田");
        ui->lev_city_comboBox->insertItem(20, "黑河");
        ui->lev_city_comboBox->insertItem(21, "呼和浩特");
        ui->lev_city_comboBox->insertItem(22, "淮安");
        ui->lev_city_comboBox->insertItem(23, "怀化");
        ui->lev_city_comboBox->insertItem(24, "黄山");
        ui->lev_city_comboBox->insertItem(25, "惠州");
        ui->lev_city_comboBox->insertItem(26, "鸡西");
        ui->lev_city_comboBox->insertItem(27, "济南");
        ui->lev_city_comboBox->insertItem(28, "济宁");
        ui->lev_city_comboBox->insertItem(29, "加格达奇");
        ui->lev_city_comboBox->insertItem(30, "佳木斯");
        ui->lev_city_comboBox->insertItem(31, "嘉峪关");
        ui->lev_city_comboBox->insertItem(32, "金昌");
        ui->lev_city_comboBox->insertItem(33, "金门");
        ui->lev_city_comboBox->insertItem(34, "锦州");
        ui->lev_city_comboBox->insertItem(35, "嘉义");
        ui->lev_city_comboBox->insertItem(36, "西双版纳");
        ui->lev_city_comboBox->insertItem(37, "建三江");
        ui->lev_city_comboBox->insertItem(38, "晋江");
        ui->lev_city_comboBox->insertItem(39, "井冈山");
        ui->lev_city_comboBox->insertItem(40, "景德镇");
        ui->lev_city_comboBox->insertItem(41, "九江");
        ui->lev_city_comboBox->insertItem(42, "九寨沟");
    }
    else if(arg1 == "KLMNP")
    {
        ui->lev_city_comboBox->insertItem(0,  "喀什");
        ui->lev_city_comboBox->insertItem(1,  "凯里");
        ui->lev_city_comboBox->insertItem(2,  "康定");
        ui->lev_city_comboBox->insertItem(3,  "克拉玛依");
        ui->lev_city_comboBox->insertItem(4,  "库车");
        ui->lev_city_comboBox->insertItem(5,  "库尔勒");
        ui->lev_city_comboBox->insertItem(6,  "昆明");
        ui->lev_city_comboBox->insertItem(7,  "拉萨");
        ui->lev_city_comboBox->insertItem(8,  "兰州");
        ui->lev_city_comboBox->insertItem(9,  "黎平");
        ui->lev_city_comboBox->insertItem(10, "丽江");
        ui->lev_city_comboBox->insertItem(11, "荔波");
        ui->lev_city_comboBox->insertItem(12, "连云港");
        ui->lev_city_comboBox->insertItem(13, "六盘水");
        ui->lev_city_comboBox->insertItem(14, "临汾");
        ui->lev_city_comboBox->insertItem(15, "林芝");
        ui->lev_city_comboBox->insertItem(16, "临沧");
        ui->lev_city_comboBox->insertItem(17, "临沂");
        ui->lev_city_comboBox->insertItem(18, "柳州");
        ui->lev_city_comboBox->insertItem(19, "泸州");
        ui->lev_city_comboBox->insertItem(20, "洛阳");
        ui->lev_city_comboBox->insertItem(21, "吕梁");
        ui->lev_city_comboBox->insertItem(22, "澜沧");
        ui->lev_city_comboBox->insertItem(23, "龙岩");
        ui->lev_city_comboBox->insertItem(24, "满洲里");
        ui->lev_city_comboBox->insertItem(25, "梅州");
        ui->lev_city_comboBox->insertItem(26, "绵阳");
        ui->lev_city_comboBox->insertItem(27, "漠河");
        ui->lev_city_comboBox->insertItem(28, "牡丹江");
        ui->lev_city_comboBox->insertItem(29, "马祖");
        ui->lev_city_comboBox->insertItem(30, "南昌");
        ui->lev_city_comboBox->insertItem(31, "南充");
        ui->lev_city_comboBox->insertItem(32, "南京");
        ui->lev_city_comboBox->insertItem(33, "南宁");
        ui->lev_city_comboBox->insertItem(34, "南通");
        ui->lev_city_comboBox->insertItem(35, "南阳");
        ui->lev_city_comboBox->insertItem(36, "宁波");
        ui->lev_city_comboBox->insertItem(37, "宁蒗");
        ui->lev_city_comboBox->insertItem(38, "攀枝花");
        ui->lev_city_comboBox->insertItem(39, "普洱");
    }
    else if(arg1 == "QRSTUVW")
    {
        ui->lev_city_comboBox->insertItem(0,  "齐齐哈尔");
        ui->lev_city_comboBox->insertItem(1,  "黔江");
        ui->lev_city_comboBox->insertItem(2,  "且末");
        ui->lev_city_comboBox->insertItem(3,  "秦皇岛");
        ui->lev_city_comboBox->insertItem(4,  "青岛");
        ui->lev_city_comboBox->insertItem(5,  "庆阳");
        ui->lev_city_comboBox->insertItem(6,  "衢州");
        ui->lev_city_comboBox->insertItem(7,  "日喀则");
        ui->lev_city_comboBox->insertItem(8,  "日照");
        ui->lev_city_comboBox->insertItem(9,  "三亚");
        ui->lev_city_comboBox->insertItem(10, "厦门");
        ui->lev_city_comboBox->insertItem(11, "上海");
        ui->lev_city_comboBox->insertItem(12, "深圳");
        ui->lev_city_comboBox->insertItem(13, "神农架");
        ui->lev_city_comboBox->insertItem(14, "沈阳");
        ui->lev_city_comboBox->insertItem(15, "石家庄");
        ui->lev_city_comboBox->insertItem(16, "塔城");
        ui->lev_city_comboBox->insertItem(17, "台州");
        ui->lev_city_comboBox->insertItem(18, "太原");
        ui->lev_city_comboBox->insertItem(19, "扬州");
        ui->lev_city_comboBox->insertItem(20, "唐山");
        ui->lev_city_comboBox->insertItem(21, "腾冲");
        ui->lev_city_comboBox->insertItem(22, "天津");
        ui->lev_city_comboBox->insertItem(23, "天水");
        ui->lev_city_comboBox->insertItem(24, "通辽");
        ui->lev_city_comboBox->insertItem(25, "铜仁");
        ui->lev_city_comboBox->insertItem(26, "吐鲁番");
        ui->lev_city_comboBox->insertItem(27, "万州");
        ui->lev_city_comboBox->insertItem(28, "威海");
        ui->lev_city_comboBox->insertItem(29, "潍坊");
        ui->lev_city_comboBox->insertItem(30, "温州");
        ui->lev_city_comboBox->insertItem(31, "文山");
        ui->lev_city_comboBox->insertItem(32, "乌海");
        ui->lev_city_comboBox->insertItem(33, "乌兰浩特");
        ui->lev_city_comboBox->insertItem(34, "乌鲁木齐");
        ui->lev_city_comboBox->insertItem(35, "无锡");
        ui->lev_city_comboBox->insertItem(36, "梧州");
        ui->lev_city_comboBox->insertItem(37, "武汉");
        ui->lev_city_comboBox->insertItem(38, "武夷山");
    }
    else if(arg1 == "XYZ")
    {
        ui->lev_city_comboBox->insertItem(0,  "西安");
        ui->lev_city_comboBox->insertItem(1,  "西昌");
        ui->lev_city_comboBox->insertItem(2,  "西宁");
        ui->lev_city_comboBox->insertItem(3,  "锡林浩特");
        ui->lev_city_comboBox->insertItem(4,  "香格里拉");
        ui->lev_city_comboBox->insertItem(5,  "襄阳");
        ui->lev_city_comboBox->insertItem(6,  "兴义");
        ui->lev_city_comboBox->insertItem(7,  "徐州");
        ui->lev_city_comboBox->insertItem(8,  "香港");
        ui->lev_city_comboBox->insertItem(9,  "烟台");
        ui->lev_city_comboBox->insertItem(10, "延安");
        ui->lev_city_comboBox->insertItem(11, "延吉");
        ui->lev_city_comboBox->insertItem(12, "盐城");
        ui->lev_city_comboBox->insertItem(13, "伊春");
        ui->lev_city_comboBox->insertItem(14, "伊宁");
        ui->lev_city_comboBox->insertItem(15, "宜宾");
        ui->lev_city_comboBox->insertItem(16, "宜昌");
        ui->lev_city_comboBox->insertItem(17, "宜春");
        ui->lev_city_comboBox->insertItem(18, "义乌");
        ui->lev_city_comboBox->insertItem(19, "银川");
        ui->lev_city_comboBox->insertItem(20, "永州");
        ui->lev_city_comboBox->insertItem(21, "榆林");
        ui->lev_city_comboBox->insertItem(22, "玉树");
        ui->lev_city_comboBox->insertItem(23, "运城");
        ui->lev_city_comboBox->insertItem(24, "湛江");
        ui->lev_city_comboBox->insertItem(25, "张家界");
        ui->lev_city_comboBox->insertItem(26, "张家口");
        ui->lev_city_comboBox->insertItem(27, "张掖");
        ui->lev_city_comboBox->insertItem(28, "昭通");
        ui->lev_city_comboBox->insertItem(29, "郑州");
        ui->lev_city_comboBox->insertItem(30, "中卫");
        ui->lev_city_comboBox->insertItem(31, "舟山");
        ui->lev_city_comboBox->insertItem(32, "珠海");
        ui->lev_city_comboBox->insertItem(33, "遵义");
    }
}

//按条件ch_查询目的城市_comboBox
void UserWindow::on_ch_des_city_comboBox_activated(const QString &arg1)
{
    ui->des_city_comboBox->clear();

    if(arg1 == "热门")
    {
        ui->des_city_comboBox->insertItem(0,  "北京");
        ui->des_city_comboBox->insertItem(1,  "上海");
        ui->des_city_comboBox->insertItem(2,  "广州");
        ui->des_city_comboBox->insertItem(3,  "深圳");
        ui->des_city_comboBox->insertItem(4,  "成都");
        ui->des_city_comboBox->insertItem(5,  "杭州");
        ui->des_city_comboBox->insertItem(6,  "西安");
        ui->des_city_comboBox->insertItem(7,  "重庆");
        ui->des_city_comboBox->insertItem(8,  "青岛");
        ui->des_city_comboBox->insertItem(9,  "南京");
        ui->des_city_comboBox->insertItem(10, "厦门");
        ui->des_city_comboBox->insertItem(11, "昆明");
        ui->des_city_comboBox->insertItem(12, "大连");
        ui->des_city_comboBox->insertItem(13, "天津");
        ui->des_city_comboBox->insertItem(14, "郑州");
        ui->des_city_comboBox->insertItem(15, "三亚");
        ui->des_city_comboBox->insertItem(16, "济南");
        ui->des_city_comboBox->insertItem(17, "福州");
    }
    else if(arg1 == "ABCDE")
    {
        ui->des_city_comboBox->insertItem(0,  "阿尔山");
        ui->des_city_comboBox->insertItem(1,  "阿克苏");
        ui->des_city_comboBox->insertItem(2,  "阿拉善右旗");
        ui->des_city_comboBox->insertItem(3,  "阿拉善左旗");
        ui->des_city_comboBox->insertItem(4,  "阿勒泰");
        ui->des_city_comboBox->insertItem(5,  "阿里");
        ui->des_city_comboBox->insertItem(6,  "澳门");
        ui->des_city_comboBox->insertItem(7,  "安庆");
        ui->des_city_comboBox->insertItem(8,  "安顺");
        ui->des_city_comboBox->insertItem(9,  "鞍山");
        ui->des_city_comboBox->insertItem(10, "巴彦淖尔");
        ui->des_city_comboBox->insertItem(11, "百色");
        ui->des_city_comboBox->insertItem(12, "包头");
        ui->des_city_comboBox->insertItem(13, "保山");
        ui->des_city_comboBox->insertItem(14, "北海");
        ui->des_city_comboBox->insertItem(15, "北京");
        ui->des_city_comboBox->insertItem(16, "白城");
        ui->des_city_comboBox->insertItem(17, "白山");
        ui->des_city_comboBox->insertItem(18, "毕节");
        ui->des_city_comboBox->insertItem(19, "博乐");
        ui->des_city_comboBox->insertItem(20, "重庆");
        ui->des_city_comboBox->insertItem(21, "昌都");
        ui->des_city_comboBox->insertItem(22, "常德");
        ui->des_city_comboBox->insertItem(23, "常州");
        ui->des_city_comboBox->insertItem(24, "朝阳");
        ui->des_city_comboBox->insertItem(25, "成都");
        ui->des_city_comboBox->insertItem(26, "池州");
        ui->des_city_comboBox->insertItem(27, "赤峰");
        ui->des_city_comboBox->insertItem(28, "揭阳");
        ui->des_city_comboBox->insertItem(29, "长春");
        ui->des_city_comboBox->insertItem(30, "长沙");
        ui->des_city_comboBox->insertItem(31, "长治");
        ui->des_city_comboBox->insertItem(32, "承德");
        ui->des_city_comboBox->insertItem(33, "沧源");
        ui->des_city_comboBox->insertItem(34, "达县");
        ui->des_city_comboBox->insertItem(35, "大理");
        ui->des_city_comboBox->insertItem(36, "大连");
        ui->des_city_comboBox->insertItem(37, "大庆");
        ui->des_city_comboBox->insertItem(38, "大同");
        ui->des_city_comboBox->insertItem(39, "丹东");
        ui->des_city_comboBox->insertItem(40, "稻城");
        ui->des_city_comboBox->insertItem(41, "东营");
        ui->des_city_comboBox->insertItem(42, "敦煌");
        ui->des_city_comboBox->insertItem(43, "芒市");
        ui->des_city_comboBox->insertItem(44, "额济纳旗");
        ui->des_city_comboBox->insertItem(45, "鄂尔多斯");
        ui->des_city_comboBox->insertItem(46, "恩施");
        ui->des_city_comboBox->insertItem(47, "二连浩特");
    }
    else if(arg1 == "FGHIJ")
    {
        ui->des_city_comboBox->insertItem(0,  "佛山");
        ui->des_city_comboBox->insertItem(1,  "福州");
        ui->des_city_comboBox->insertItem(2,  "抚远");
        ui->des_city_comboBox->insertItem(3,  "阜阳");
        ui->des_city_comboBox->insertItem(4,  "赣州");
        ui->des_city_comboBox->insertItem(5,  "格尔木");
        ui->des_city_comboBox->insertItem(6,  "固原");
        ui->des_city_comboBox->insertItem(7,  "广元");
        ui->des_city_comboBox->insertItem(8,  "广州");
        ui->des_city_comboBox->insertItem(9,  "贵阳");
        ui->des_city_comboBox->insertItem(10, "桂林");
        ui->des_city_comboBox->insertItem(11, "哈尔滨");
        ui->des_city_comboBox->insertItem(12, "哈密");
        ui->des_city_comboBox->insertItem(13, "海口");
        ui->des_city_comboBox->insertItem(14, "海拉尔");
        ui->des_city_comboBox->insertItem(15, "邯郸");
        ui->des_city_comboBox->insertItem(16, "汉中");
        ui->des_city_comboBox->insertItem(17, "杭州");
        ui->des_city_comboBox->insertItem(18, "合肥");
        ui->des_city_comboBox->insertItem(19, "和田");
        ui->des_city_comboBox->insertItem(20, "黑河");
        ui->des_city_comboBox->insertItem(21, "呼和浩特");
        ui->des_city_comboBox->insertItem(22, "淮安");
        ui->des_city_comboBox->insertItem(23, "怀化");
        ui->des_city_comboBox->insertItem(24, "黄山");
        ui->des_city_comboBox->insertItem(25, "惠州");
        ui->des_city_comboBox->insertItem(26, "鸡西");
        ui->des_city_comboBox->insertItem(27, "济南");
        ui->des_city_comboBox->insertItem(28, "济宁");
        ui->des_city_comboBox->insertItem(29, "加格达奇");
        ui->des_city_comboBox->insertItem(30, "佳木斯");
        ui->des_city_comboBox->insertItem(31, "嘉峪关");
        ui->des_city_comboBox->insertItem(32, "金昌");
        ui->des_city_comboBox->insertItem(33, "金门");
        ui->des_city_comboBox->insertItem(34, "锦州");
        ui->des_city_comboBox->insertItem(35, "嘉义");
        ui->des_city_comboBox->insertItem(36, "西双版纳");
        ui->des_city_comboBox->insertItem(37, "建三江");
        ui->des_city_comboBox->insertItem(38, "晋江");
        ui->des_city_comboBox->insertItem(39, "井冈山");
        ui->des_city_comboBox->insertItem(40, "景德镇");
        ui->des_city_comboBox->insertItem(41, "九江");
        ui->des_city_comboBox->insertItem(42, "九寨沟");
    }
    else if(arg1 == "KLMNP")
    {
        ui->des_city_comboBox->insertItem(0,  "喀什");
        ui->des_city_comboBox->insertItem(1,  "凯里");
        ui->des_city_comboBox->insertItem(2,  "康定");
        ui->des_city_comboBox->insertItem(3,  "克拉玛依");
        ui->des_city_comboBox->insertItem(4,  "库车");
        ui->des_city_comboBox->insertItem(5,  "库尔勒");
        ui->des_city_comboBox->insertItem(6,  "昆明");
        ui->des_city_comboBox->insertItem(7,  "拉萨");
        ui->des_city_comboBox->insertItem(8,  "兰州");
        ui->des_city_comboBox->insertItem(9,  "黎平");
        ui->des_city_comboBox->insertItem(10, "丽江");
        ui->des_city_comboBox->insertItem(11, "荔波");
        ui->des_city_comboBox->insertItem(12, "连云港");
        ui->des_city_comboBox->insertItem(13, "六盘水");
        ui->des_city_comboBox->insertItem(14, "临汾");
        ui->des_city_comboBox->insertItem(15, "林芝");
        ui->des_city_comboBox->insertItem(16, "临沧");
        ui->des_city_comboBox->insertItem(17, "临沂");
        ui->des_city_comboBox->insertItem(18, "柳州");
        ui->des_city_comboBox->insertItem(19, "泸州");
        ui->des_city_comboBox->insertItem(20, "洛阳");
        ui->des_city_comboBox->insertItem(21, "吕梁");
        ui->des_city_comboBox->insertItem(22, "澜沧");
        ui->des_city_comboBox->insertItem(23, "龙岩");
        ui->des_city_comboBox->insertItem(24, "满洲里");
        ui->des_city_comboBox->insertItem(25, "梅州");
        ui->des_city_comboBox->insertItem(26, "绵阳");
        ui->des_city_comboBox->insertItem(27, "漠河");
        ui->des_city_comboBox->insertItem(28, "牡丹江");
        ui->des_city_comboBox->insertItem(29, "马祖");
        ui->des_city_comboBox->insertItem(30, "南昌");
        ui->des_city_comboBox->insertItem(31, "南充");
        ui->des_city_comboBox->insertItem(32, "南京");
        ui->des_city_comboBox->insertItem(33, "南宁");
        ui->des_city_comboBox->insertItem(34, "南通");
        ui->des_city_comboBox->insertItem(35, "南阳");
        ui->des_city_comboBox->insertItem(36, "宁波");
        ui->des_city_comboBox->insertItem(37, "宁蒗");
        ui->des_city_comboBox->insertItem(38, "攀枝花");
        ui->des_city_comboBox->insertItem(39, "普洱");
    }
    else if(arg1 == "QRSTUVW")
    {
        ui->des_city_comboBox->insertItem(0,  "齐齐哈尔");
        ui->des_city_comboBox->insertItem(1,  "黔江");
        ui->des_city_comboBox->insertItem(2,  "且末");
        ui->des_city_comboBox->insertItem(3,  "秦皇岛");
        ui->des_city_comboBox->insertItem(4,  "青岛");
        ui->des_city_comboBox->insertItem(5,  "庆阳");
        ui->des_city_comboBox->insertItem(6,  "衢州");
        ui->des_city_comboBox->insertItem(7,  "日喀则");
        ui->des_city_comboBox->insertItem(8,  "日照");
        ui->des_city_comboBox->insertItem(9,  "三亚");
        ui->des_city_comboBox->insertItem(10, "厦门");
        ui->des_city_comboBox->insertItem(11, "上海");
        ui->des_city_comboBox->insertItem(12, "深圳");
        ui->des_city_comboBox->insertItem(13, "神农架");
        ui->des_city_comboBox->insertItem(14, "沈阳");
        ui->des_city_comboBox->insertItem(15, "石家庄");
        ui->des_city_comboBox->insertItem(16, "塔城");
        ui->des_city_comboBox->insertItem(17, "台州");
        ui->des_city_comboBox->insertItem(18, "太原");
        ui->des_city_comboBox->insertItem(19, "扬州");
        ui->des_city_comboBox->insertItem(20, "唐山");
        ui->des_city_comboBox->insertItem(21, "腾冲");
        ui->des_city_comboBox->insertItem(22, "天津");
        ui->des_city_comboBox->insertItem(23, "天水");
        ui->des_city_comboBox->insertItem(24, "通辽");
        ui->des_city_comboBox->insertItem(25, "铜仁");
        ui->des_city_comboBox->insertItem(26, "吐鲁番");
        ui->des_city_comboBox->insertItem(27, "万州");
        ui->des_city_comboBox->insertItem(28, "威海");
        ui->des_city_comboBox->insertItem(29, "潍坊");
        ui->des_city_comboBox->insertItem(30, "温州");
        ui->des_city_comboBox->insertItem(31, "文山");
        ui->des_city_comboBox->insertItem(32, "乌海");
        ui->des_city_comboBox->insertItem(33, "乌兰浩特");
        ui->des_city_comboBox->insertItem(34, "乌鲁木齐");
        ui->des_city_comboBox->insertItem(35, "无锡");
        ui->des_city_comboBox->insertItem(36, "梧州");
        ui->des_city_comboBox->insertItem(37, "武汉");
        ui->des_city_comboBox->insertItem(38, "武夷山");
    }
    else if(arg1 == "XYZ")
    {
        ui->des_city_comboBox->insertItem(0,  "西安");
        ui->des_city_comboBox->insertItem(1,  "西昌");
        ui->des_city_comboBox->insertItem(2,  "西宁");
        ui->des_city_comboBox->insertItem(3,  "锡林浩特");
        ui->des_city_comboBox->insertItem(4,  "香格里拉");
        ui->des_city_comboBox->insertItem(5,  "襄阳");
        ui->des_city_comboBox->insertItem(6,  "兴义");
        ui->des_city_comboBox->insertItem(7,  "徐州");
        ui->des_city_comboBox->insertItem(8,  "香港");
        ui->des_city_comboBox->insertItem(9,  "烟台");
        ui->des_city_comboBox->insertItem(10, "延安");
        ui->des_city_comboBox->insertItem(11, "延吉");
        ui->des_city_comboBox->insertItem(12, "盐城");
        ui->des_city_comboBox->insertItem(13, "伊春");
        ui->des_city_comboBox->insertItem(14, "伊宁");
        ui->des_city_comboBox->insertItem(15, "宜宾");
        ui->des_city_comboBox->insertItem(16, "宜昌");
        ui->des_city_comboBox->insertItem(17, "宜春");
        ui->des_city_comboBox->insertItem(18, "义乌");
        ui->des_city_comboBox->insertItem(19, "银川");
        ui->des_city_comboBox->insertItem(20, "永州");
        ui->des_city_comboBox->insertItem(21, "榆林");
        ui->des_city_comboBox->insertItem(22, "玉树");
        ui->des_city_comboBox->insertItem(23, "运城");
        ui->des_city_comboBox->insertItem(24, "湛江");
        ui->des_city_comboBox->insertItem(25, "张家界");
        ui->des_city_comboBox->insertItem(26, "张家口");
        ui->des_city_comboBox->insertItem(27, "张掖");
        ui->des_city_comboBox->insertItem(28, "昭通");
        ui->des_city_comboBox->insertItem(29, "郑州");
        ui->des_city_comboBox->insertItem(30, "中卫");
        ui->des_city_comboBox->insertItem(31, "舟山");
        ui->des_city_comboBox->insertItem(32, "珠海");
        ui->lev_city_comboBox->insertItem(33, "遵义");
    }
}
/****************************************************************************************航班查询及下单功能****************************************************************************/


/*******************************************************************************************订单中心功能******************************************************************************/
//订单中心显示
void UserWindow::order_cen_show()
{

    clear_order_cen_table();

    //ui->order_cen_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分

    ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->order_cen_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //设置每行内容不可编辑
    ui->order_cen_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选择行为，以行为单位

    QSqlTableModel order_cen_model;
    order_cen_model.setTable("order_info");
    order_cen_model.setFilter(tr("order_u_name = '%1'").arg(user_name));
    order_cen_model.select();
    int rowcount = order_cen_model.rowCount();
    if(order_cen_model.rowCount() >= 1)
    {
        for(int i = 0 ; i < rowcount; i++)
        {
            order_num = order_cen_model.data(order_cen_model.index(i, 0)).toString();
            order_flight_num = order_cen_model.data(order_cen_model.index(i, 1)).toString();
            order_u_tel = order_cen_model.data(order_cen_model.index(i, 2)).toString();
            order_u_name = order_cen_model.data(order_cen_model.index(i, 3)).toString();
            order_pay_state = order_cen_model.data(order_cen_model.index(i, 4)).toString();
            order_flight_date = order_cen_model.data(order_cen_model.index(i, 5)).toString();
            order_flight_time = order_cen_model.data(order_cen_model.index(i, 6)).toString();
            order_flight_to_city = order_cen_model.data(order_cen_model.index(i, 7)).toString();
            order_flight_ar_city = order_cen_model.data(order_cen_model.index(i, 8)).toString();
            order_flight_price = order_cen_model.data(order_cen_model.index(i, 9)).toString();
            order_time = order_cen_model.data(order_cen_model.index(i, 10)).toString();
            order_pay_time = order_cen_model.data(order_cen_model.index(i, 11)).toString();

            int table_row = ui->order_cen_tableWidget->rowCount();
            ui->order_cen_tableWidget->insertRow(table_row);

            QTableWidgetItem *check = new QTableWidgetItem();
            check->setCheckState(Qt::Unchecked);
            ui->order_cen_tableWidget->setItem(table_row,0,check); //插入复选框

            ui->order_cen_tableWidget->setItem(table_row, 1, new QTableWidgetItem(order_num));
            ui->order_cen_tableWidget->setItem(table_row, 2, new QTableWidgetItem(order_flight_num));
            ui->order_cen_tableWidget->setItem(table_row, 3, new QTableWidgetItem(order_u_tel));
            ui->order_cen_tableWidget->setItem(table_row, 4, new QTableWidgetItem(order_u_name));
            ui->order_cen_tableWidget->setItem(table_row, 5, new QTableWidgetItem(order_pay_state));
            ui->order_cen_tableWidget->setItem(table_row, 6, new QTableWidgetItem(order_flight_date));
            ui->order_cen_tableWidget->setItem(table_row, 7, new QTableWidgetItem(order_flight_time));
            ui->order_cen_tableWidget->setItem(table_row, 8, new QTableWidgetItem(order_flight_to_city));
            ui->order_cen_tableWidget->setItem(table_row, 9, new QTableWidgetItem(order_flight_ar_city));
            ui->order_cen_tableWidget->setItem(table_row, 10, new QTableWidgetItem(order_flight_price));
            ui->order_cen_tableWidget->setItem(table_row, 11, new QTableWidgetItem(order_time));
            ui->order_cen_tableWidget->setItem(table_row, 12, new QTableWidgetItem(order_pay_time));
        }
    }
    else
    {
        QMessageBox::about(NULL, "提示", "未查询到您的相关订单!");
    }
}

//订单支付
void UserWindow::on_order_pay_pushButton_clicked()
{
    QList<int> pay_list;

    for(int i = 0; i < ui->order_cen_tableWidget->rowCount(); i++)
    {
        if(ui->order_cen_tableWidget->item(i, 0)->checkState())
        {
           pay_list << i;
        }
    }

    if(pay_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要支付的订单!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认支付该订单吗?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < pay_list.length(); i++)
            {
                b_order_num = ui->order_cen_tableWidget->item(pay_list.at(i), 1)->text().toUtf8();
                order_num = b_order_num.data();

                QSqlTableModel order_info_model;
                order_info_model.setTable("order_info");
                order_info_model.setFilter(tr("order_num = '%1'").arg(ui->order_cen_tableWidget->item(pay_list.at(i), 1)->text()));
                order_info_model.select();
                int rowcount = order_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString pay_state = order_info_model.data(order_info_model.index(0, 4)).toString();             //检查该订单号是否已支付
                    if(pay_state == "未支付")
                    {
                        QDateTime local(QDateTime::currentDateTime());
                        order_pay_time = local.toString("hh:mm:ss");

                        QString localdate = local.toString("yyyyMMdd");
                        QString eletime = local.toString("hhmmss");

                        b_order_pay = QString("已支付").toUtf8();
                        order_pay = b_order_pay.data();

                        b_e_ticket_num = (ui->order_cen_tableWidget->item(pay_list.at(i),2)->text() + localdate + eletime).toUtf8();
                        b_e_order_num = ui->order_cen_tableWidget->item(pay_list.at(i),1)->text().toUtf8();
                        b_e_ticket_u_name = ui->order_cen_tableWidget->item(pay_list.at(i),4)->text().toUtf8();
                        b_e_flight_num = ui->order_cen_tableWidget->item(pay_list.at(i),2)->text().toUtf8();
                        b_e_flight_to_city = ui->order_cen_tableWidget->item(pay_list.at(i),8)->text().toUtf8();
                        b_e_flight_ar_city = ui->order_cen_tableWidget->item(pay_list.at(i),9)->text().toUtf8();
                        b_e_flight_date = ui->order_cen_tableWidget->item(pay_list.at(i),6)->text().toUtf8();
                        b_e_flight_time = ui->order_cen_tableWidget->item(pay_list.at(i),7)->text().toUtf8();
                        b_e_flight_price = ui->order_cen_tableWidget->item(pay_list.at(i),10)->text().toUtf8();
                        b_order_pay_time = order_pay_time.toUtf8();

                        e_ticket_num = b_e_ticket_num.data();
                        e_order_num = b_e_order_num.data();
                        e_ticket_u_name = b_e_ticket_u_name.data();
                        e_flight_num = b_e_flight_num.data();
                        e_flight_to_city = b_e_flight_to_city.data();
                        e_flight_ar_city = b_e_flight_ar_city.data();
                        e_flight_date = b_e_flight_date.data();
                        e_flight_time = b_e_flight_time.data();
                        e_flight_price = b_e_flight_price.data();
                        order_pay_time = b_order_pay_time.data();

                        QString pay_str = QString("update order_info set order_pay_state='%1', order_pay_time='%2' where order_num='%3'").arg(order_pay).arg(order_pay_time).arg(order_num);
                        QString ele_str = QString("insert into ele_ticket(e_ticket_num, e_order_num, e_ticket_u_name, e_flight_num, e_filght_to_city, e_flight_ar_city, e_flight_date, e_flight_to_time, e_flight_price)   \
                                                    values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')")
                                                  .arg(e_ticket_num).arg(e_order_num).arg(e_ticket_u_name).arg(e_flight_num).arg(e_flight_to_city)
                                                  .arg(e_flight_ar_city).arg(e_flight_date).arg(e_flight_time).arg(e_flight_price);
                        QSqlQuery pay_query;
                        QSqlQuery ele_query;
                        if(pay_query.exec(pay_str) && ele_query.exec(ele_str))
                        {
                            QMessageBox::about(NULL, "提示", QString("您的订单%1支付成功!").arg(ui->order_cen_tableWidget->item(pay_list.at(i), 1)->text()));
                            order_cen_show();
                        }
                        else
                        {
                            QMessageBox::about(NULL, "提示", "支付失败!");
                            order_cen_show();
                        }
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("您的订单号%1已支付!").arg(ui->order_cen_tableWidget->item(pay_list.at(i), 1)->text()));
                        order_cen_show();
                    }

                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消订单支付!");
            order_cen_show();
        }
    }
}

//订单退单
void UserWindow::on_order_back_pushButton_clicked()
{
    QList<int> orderback_list;

    for(int i = 0; i < ui->order_cen_tableWidget->rowCount(); i++)
    {
        if(ui->order_cen_tableWidget->item(i, 0)->checkState())
        {
           orderback_list << i;
        }
    }

    if(orderback_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要退订的订单!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认退订该订单?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < orderback_list.length(); i++)
            {
                QSqlTableModel order_info_model;
                order_info_model.setTable("order_info");
                order_info_model.setFilter(tr("order_num = '%1'").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                order_info_model.select();
                int rowcount = order_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString pay_state = order_info_model.data(order_info_model.index(0, 4)).toString();             //检查该订单号是否已支付
                    if(pay_state == "已支付")
                    {
                        b_orderback_pay = QString("未支付").toUtf8();
                        b_orderback_time = QString("").toUtf8();
                        orderback_pay = b_orderback_pay.data();
                        orderback_time = b_orderback_time.data();
                        b_order_num = ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text().toUtf8();
                        order_num = b_order_num.data();

                        QString payback_str = QString("update order_info set order_pay_state='%1', order_pay_time='%2' where order_num='%3'").arg(orderback_pay).arg(orderback_time).arg(order_num);
                        QString eleback_str = QString("delete from ele_ticket where e_order_num='%1'").arg(order_num);

                        QSqlQuery payback_query;
                        QSqlQuery eleback_query;
                        if(payback_query.exec(payback_str) && eleback_query.exec(eleback_str))
                        {
                            QMessageBox::about(NULL, "提示", QString("您的订单%1退订成功!").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                            order_cen_show();
                        }
                        else
                        {
                            QMessageBox::about(NULL, "提示", "订单退订失败!");
                            order_cen_show();
                        }
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("您的订单号%1未支付!").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                        order_cen_show();
                    }

                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消退订订单!");
            order_cen_show();
        }
    }
}

//订单删除功能
void UserWindow::on_order_del_pushButton_clicked()
{
    QList<int> orderback_list;

    for(int i = 0; i < ui->order_cen_tableWidget->rowCount(); i++)
    {
        if(ui->order_cen_tableWidget->item(i, 0)->checkState())
        {
           orderback_list << i;
        }
    }

    if(orderback_list.isEmpty())
    {
        QMessageBox::about(NULL, "提示", "请选择需要退订的订单!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "提示", "确认删除该订单?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            for(int i = 0; i < orderback_list.length(); i++)
            {
                QSqlTableModel order_info_model;
                order_info_model.setTable("order_info");
                order_info_model.setFilter(tr("order_num = '%1'").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                order_info_model.select();
                int rowcount = order_info_model.rowCount();
                if( rowcount == 1)
                {
                    QString pay_state = order_info_model.data(order_info_model.index(0, 4)).toString();             //检查该订单号是否已支付
                    if(pay_state == "未支付")
                    {
                        b_order_num = ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text().toUtf8();
                        order_num = b_order_num.data();

                        QString str = QString("delete from order_info where order_num='%1'").arg(order_num);
                        QSqlQuery query;

                        if(query.exec(str))
                        {
                            QMessageBox::about(NULL, "提示", QString("您的订单%1删除成功!").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                            order_cen_show();
                        }
                        else
                        {
                            QMessageBox::about(NULL, "提示", "订单删除失败!");
                            order_cen_show();
                        }
                    }
                    else
                    {
                        QMessageBox::about(NULL, "提示", QString("您的订单号%1已支付,无法删除,请先退订订单!").arg(ui->order_cen_tableWidget->item(orderback_list.at(i), 1)->text()));
                        order_cen_show();
                    }

                }
            }
        }
        if (reply == QMessageBox::No)
        {
            QMessageBox::about(NULL, "提示", "您已取消删除订单!");
            order_cen_show();
        }
    }
}

/*******************************************************************************************订单中心功能******************************************************************************/

/*******************************************************************************************个人中心功能******************************************************************************/
void UserWindow::my_home_show()
{
    clear_my_home_table();

    //ui->order_cen_tableWidget->horizontalHeader()->setStretchLastSection(true);                    //使行列头自适应宽度，最后一列将会填充空白部分
    //ui->order_cen_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //使行列头自适应宽度，所有列平均分来填充空白部分

    ui->my_home_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->my_home_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //设置每行内容不可编辑
    ui->my_home_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //设置选择行为，以行为单位

    QSqlTableModel my_home_model;
    my_home_model.setTable("ele_ticket");
    my_home_model.setFilter(tr("e_ticket_u_name = '%1'").arg(user_name));
    my_home_model.select();
    int rowcount = my_home_model.rowCount();

    if(my_home_model.rowCount() >= 1)
    {
        for(int i = 0 ; i < rowcount; i++)
        {
            home_ticket_num = my_home_model.data(my_home_model.index(i, 0)).toString();
            home_u_name = my_home_model.data(my_home_model.index(i, 2)).toString();
            home_flight_num_ = my_home_model.data(my_home_model.index(i, 3)).toString();
            home_to_city = my_home_model.data(my_home_model.index(i, 4)).toString();
            home_ar_city = my_home_model.data(my_home_model.index(i, 5)).toString();
            home_to_date = my_home_model.data(my_home_model.index(i, 6)).toString();
            home_to_time = my_home_model.data(my_home_model.index(i, 7)).toString();
            home_flight_price = my_home_model.data(my_home_model.index(i, 8)).toString();

            int table_row = ui->my_home_tableWidget->rowCount();
            ui->my_home_tableWidget->insertRow(table_row);

            ui->my_home_tableWidget->setItem(table_row, 0, new QTableWidgetItem(home_ticket_num));
            ui->my_home_tableWidget->setItem(table_row, 1, new QTableWidgetItem(home_u_name));
            ui->my_home_tableWidget->setItem(table_row, 2, new QTableWidgetItem(home_flight_num_));
            ui->my_home_tableWidget->setItem(table_row, 3, new QTableWidgetItem(home_to_city));
            ui->my_home_tableWidget->setItem(table_row, 4, new QTableWidgetItem(home_ar_city));
            ui->my_home_tableWidget->setItem(table_row, 5, new QTableWidgetItem(home_to_date));
            ui->my_home_tableWidget->setItem(table_row, 6, new QTableWidgetItem(home_to_time));
            ui->my_home_tableWidget->setItem(table_row, 7, new QTableWidgetItem(home_flight_price));
        }
    }
    else
    {
        QMessageBox::about(NULL, "提示", "未查询到您的相关机票信息!");
    }
}





/*******************************************************************************************个人中心功能******************************************************************************/

