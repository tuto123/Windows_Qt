#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool loginwhether = true;
    bool showpassword = true;
    bool adminlogin = true;

private:
    Ui::MainWindow *ui;

private slots:
    void paintEvent(QPaintEvent *event);   //添加可调节背景图功能函数

    void initMywindow();   //初始化界面窗口

    void clearall();

    void setqssstyle(const QString &qssFile);  //添加样式功能函数

    void on_login_radioButton_clicked();

    void on_signup_radioButton_clicked();

    void on_showpassword_pushButton_clicked();

    void on_login_signup_pushButton_clicked();

    void on_admin_login_pushButton_clicked();
};

#endif // MAINWINDOW_H
