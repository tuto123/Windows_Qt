#include "adminwindow.h"
#include "ui_adminwindow.h"

#include "mainwindow.h"

#include <QPainter>

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
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

void AdminWindow::on_logout_pushButton_clicked()
{
    this->close();
    MainWindow *mw = new MainWindow;
    mw->setWindowTitle("航空机票预订系统");
    mw->show();
}
