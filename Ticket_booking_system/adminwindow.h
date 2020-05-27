#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void paintEvent(QPaintEvent *event);    //添加可调节背景图功能函数

    void initAdminwindow();                 //初始化管理员界面

    void clear_flight_info_table();         //清除flight_que_table

    void clear_order_info_table();          //清除order_info_table

    void clear_pasnger_info_table();        //pasnger_info

    void flight_num_que();

    void flight_date_que();

    void on_menu_order_info_pushButton_clicked();

    void on_menu_pasnger_info_pushButton_clicked();

    void on_menu_flight_info_pushButton_clicked();

    void on_logout_pushButton_clicked();

    void on_flight_date_que_radioButton_clicked();

    void on_flight_num_que_radioButton_clicked();

    void on_flight_que_pushButton_clicked();

    void on_flight_change_pushButton_clicked();

    void on_flight_delete_pushButton_clicked();

    void on_order_que_pushButton_clicked();

    void on_order_change_pushButton_clicked();

    void on_order_del_pushButton_clicked();

    void on_pasnger_info_que_pushButton_clicked();

    void on_pasnger_info_change_pushButton_clicked();

    void on_pasnger_info_del_pushButton_clicked();

private:
    Ui::AdminWindow *ui;

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

    QString user_name;
    QString user_IDcard;
    QString user_tel;
    QString user_pwd;

    QByteArray b_f_flight_num;
    QByteArray b_f_flight_price;
    QByteArray b_f_u_tel;
    QByteArray b_f_name;
    QByteArray b_f_pay_state;
    QByteArray b_f_flight_to_date;
    QByteArray b_f_flight_ar_date;
    QByteArray b_f_flight_to_time;
    QByteArray b_f_flight_dis;
    QByteArray b_f_flight_type;
    QByteArray b_f_flight_to_city;
    QByteArray b_f_flight_ar_city;
    QByteArray b_f_flight_cro_city;

    QByteArray b_order_num;
    QByteArray b_order_flight_num;
    QByteArray b_order_u_tel;
    QByteArray b_order_u_name;
    QByteArray b_order_pay_state;
    QByteArray b_order_flight_date;
    QByteArray b_order_flight_time;
    QByteArray b_order_flight_to_city;
    QByteArray b_order_flight_ar_city;
    QByteArray b_order_flight_price;
    QByteArray b_order_time;
    QByteArray b_order_pay_time;

    QByteArray b_user_name;
    QByteArray b_user_IDcard;
    QByteArray b_user_tel;
    QByteArray b_user_pwd;

    char *f_flight_num;
    char *f_flight_price;
    char *f_u_tel;
    char *f_name;
    char *f_pay_state;
    char *f_flight_to_date;
    char *f_flight_ar_date;
    char *f_flight_to_time;
    char *f_flight_dis;
    char *f_flight_type;
    char *f_flight_to_city;
    char *f_flight_ar_city;
    char *f_flight_cro_city;

    char *c_order_num;
    char *c_order_flight_num;
    char *c_order_u_tel;
    char *c_order_u_name;
    char *c_order_pay_state;
    char *c_order_flight_date;
    char *c_order_flight_time;
    char *c_order_flight_to_city;
    char *c_order_flight_ar_city;
    char *c_order_flight_price;
    char *c_order_time;
    char *c_order_pay_time;

    char *c_user_name;
    char *c_user_IDcard;
    char *c_user_tel;
    char *c_user_pwd;

};

#endif // ADMINWINDOW_H
