#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = 0);
    ~UserWindow();

private:
    Ui::UserWindow *ui;

    QString user_tel;

    QString f_num;          //航班号
    QString f_price;        //票价
    QString f_to_date;      //起飞日期
    QString f_ar_date;      //到达日期
    QString f_to_time;      //起飞时间
    QString f_dis;          //飞行距离
    QString f_type;         //机型
    QString f_cro_city;     //途经城市
    QString f_take_city;    //起飞城市
    QString f_ar_city;      //目的地

    QString order_num;
    QString order_flight_num;
    QString order_u_tel;
    QString order_u_name;
    QString order_pay_state;
    QString order_flight_date;
    QString order_flight_time;
    QString order_flight_to_city;
    QString order_flight_ar_city;
    QString order_flight_price;
    QString order_time;
    QString order_pay_time;

    QByteArray b_order_num;
    QByteArray b_order_flight_num;
    QByteArray b_order_u_tel;
    QByteArray b_order_name;
    QByteArray b_order_pay_state;
    QByteArray b_order_flight_date;
    QByteArray b_order_flight_time;
    QByteArray b_order_flight_to_city;
    QByteArray b_order_flight_ar_city;
    QByteArray b_order_flight_price;
    QByteArray b_order_time;
    QByteArray b_order_pay_time;

    QByteArray b_order_pay;                 //确认支付成功
    char *order_pay;                       //确认支付成功
    QByteArray b_orderback_pay;                //确认退订订单
    char *orderback_pay;                       //确认退订订单



    char *f_order_num;
    char *f_order_flight_num;
    char *f_order_u_tel;
    char *f_order_name;
    char *f_order_pay_state;
    char *f_order_flight_date;
    char *f_order_flight_time;
    char *f_order_flight_to_city;
    char *f_order_flight_ar_city;
    char *f_order_flight_price;
    char *f_order_time;
    char *f_order_pay_time;

    QString user_name;


private slots:
     void initUserwindow();                 //初始化User界面

     void initUser_info();                  //初始化用户信息

     void order_cen_show();                 //显示订单中心的订单信息

     void clear_flight_que_table();         //清除flight_que_table

     void clear_order_cen_table();          //清除order_cen_table

     void paintEvent(QPaintEvent *event);   //添加可调节背景图功能函数

     void flight_city_que();

     void flight_num_que();

     void flight_date_que();

     void on_menu_my_home_pushButton_clicked();

     void on_menu_order_cen_pushButton_clicked();

     void on_menu_flight_que_pushButton_clicked();

     void on_logout_pushButton_clicked();

     void on_one_way_radioButton_clicked();

     void on_two_way_radioButton_clicked();

     void on_flight_num_que_radioButton_clicked();

     void on_flight_date_que_radioButton_clicked();

     void on_flight_que_pushButton_clicked();

     void on_ch_lev_city_comboBox_activated(const QString &arg1);

     void on_ch_des_city_comboBox_activated(const QString &arg1);

     void on_ticket_book_pushButton_clicked();

     void on_order_pay_pushButton_clicked();

     void on_order_back_pushButton_clicked();

};

#endif // USERWINDOW_H
