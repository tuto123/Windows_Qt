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
    void paintEvent(QPaintEvent *event);   //添加可调节背景图功能函数

    void on_menu_order_info_pushButton_clicked();

    void on_menu_pasnger_info_pushButton_clicked();

    void on_menu_flight_info_pushButton_clicked();

    void on_logout_pushButton_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
