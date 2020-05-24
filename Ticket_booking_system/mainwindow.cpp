#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPainter>
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "userwindow.h"
#include "adminwindow.h"

extern QString ac_user_tel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMywindow();

    /*QString qssFile = qssFile = ":/style/qss/brown.css";
    setqssstyle(qssFile);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

//给主登录界面添加可以缩放背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/image/images/background.jpg"));
}

//设置样式功能函数
void MainWindow::setqssstyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        QString PaletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(PaletteColor)));
        file.close();
    }
}

void MainWindow::on_admin_login_pushButton_clicked()    //管理员登录
{
    clearall();
    if(ui->admin_login_pushButton->text() == "管理员登录")
    {
        ui->signup_radioButton->setVisible(false);
        ui->login_signup_pushButton->setText("管理员登录");
        ui->admin_login_pushButton->setText("用户登录");
        ui->tel_num_label->setText("管理员账号:");
        ui->passwo_label->setText("管理员密码:");
        ui->name_label->setVisible(false);
        ui->name_lineEdit->setVisible(false);
        ui->idcardnum_label->setVisible(false);
        ui->idcardnum_lineEdit->setVisible(false);
    }
    else if(ui->admin_login_pushButton->text() == "用户登录")
    {
        ui->signup_radioButton->setVisible(true);
        ui->login_signup_pushButton->setText("登录");
        ui->admin_login_pushButton->setText("管理员登录");
        ui->tel_num_label->setText("手机号码:");
        ui->passwo_label->setText("密码:");
        ui->name_label->setVisible(false);
        ui->name_lineEdit->setVisible(false);
        ui->idcardnum_label->setVisible(false);
        ui->idcardnum_lineEdit->setVisible(false);
    }
}

void MainWindow::on_login_radioButton_clicked()    //登录功能
{
    clearall();
    ui->admin_login_pushButton->setVisible(true);
    if(loginwhether)
    {
        loginwhether = false;

        ui->login_signup_pushButton->setText("登录");
        ui->name_label->setVisible(false);
        ui->name_lineEdit->setVisible(false);
        ui->idcardnum_label->setVisible(false);
        ui->idcardnum_lineEdit->setVisible(false);
    }

}

void MainWindow::on_signup_radioButton_clicked()    //注册功能
{
    clearall();
    ui->admin_login_pushButton->setVisible(false);
    if(!loginwhether)
    {
        loginwhether = true;

        ui->login_signup_pushButton->setText("注册");
        ui->name_label->setVisible(true);
        ui->name_lineEdit->setVisible(true);
        ui->tel_num_label->setVisible(true);
        ui->tel_num_lineEdit->setVisible(true);
        ui->idcardnum_label->setVisible(true);
        ui->idcardnum_lineEdit->setVisible(true);
    }
}

void MainWindow::on_showpassword_pushButton_clicked()
{
    if(showpassword)
    {
        showpassword = false;
        ui->showpassword_pushButton->setText("不显示密码");
        ui->password_lineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        showpassword = true;
        ui->showpassword_pushButton->setText("显示密码");
        ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::initMywindow()    //初始化功能函数
{
    ui->login_radioButton->setChecked(true);
    loginwhether = false;
    ui->name_label->setVisible(false);
    ui->name_lineEdit->setVisible(false);
    ui->idcardnum_label->setVisible(false);
    ui->idcardnum_lineEdit->setVisible(false);
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

void MainWindow::clearall()    //清空LineEdit功能函数
{
    ui->tel_num_lineEdit->clear();
    ui->idcardnum_lineEdit->clear();
    ui->password_lineEdit->clear();
    ui->name_lineEdit->clear();
}

void MainWindow::on_login_signup_pushButton_clicked()   //登录功能函数
{
    /*************************登录功能***************************/
    if(ui->login_signup_pushButton->text() == "登录")
    {
        if(ui->tel_num_lineEdit->text().isEmpty() || ui->password_lineEdit->text().isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请输入手机号以及密码!");
            ui->tel_num_lineEdit->setFocus();
        }
        else
        {
            QString u_tel = ui->tel_num_lineEdit->text();
            QString u_pwd = ui->password_lineEdit->text();

            QSqlTableModel model;
            model.setTable("user_info");
            model.setFilter(tr("u_tel = '%1' and u_pwd = '%2'").arg(u_tel).arg(u_pwd));
            model.select();
            if(model.rowCount() == 1)
            {
                ac_user_tel = u_tel;
                QMessageBox::about(NULL, "提示", "登陆成功");
                this->close();
                UserWindow *uw = new UserWindow;
                uw->setWindowTitle("用户机票管理");
                uw->show();
            }
            else
            {
                QMessageBox::about(NULL, "提示", "账户或密码错误，请重新输入!");
                ui->tel_num_lineEdit->clear();
                ui->password_lineEdit->clear();
                ui->tel_num_lineEdit->setFocus();
            }
        }
    }
    /****************************************************************/

    /*************************管理员登录功能***************************/
    if(ui->login_signup_pushButton->text() == "管理员登录")
    {
        if(ui->tel_num_lineEdit->text().isEmpty() || ui->password_lineEdit->text().isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请输入管理员账号以及密码!");
            ui->tel_num_lineEdit->setFocus();
        }
        else
        {
            QString a_tel = ui->tel_num_lineEdit->text();
            QString a_pwd = ui->password_lineEdit->text();

            QSqlTableModel model;
            model.setTable("aim_info");
            model.setFilter(tr("aim_id = '%1' and aim_pwd = '%2'").arg(a_tel).arg(a_pwd));
            model.select();
            if(model.rowCount() == 1)
            {
                this->close();
                AdminWindow *aw = new AdminWindow;
                aw->setWindowTitle("系统管理员");
                aw->show();
            }
            else
            {
                QMessageBox::about(NULL, "提示", "账户或密码错误，请重新输入!");
                ui->tel_num_lineEdit->clear();
                ui->password_lineEdit->clear();
                ui->tel_num_lineEdit->setFocus();
            }
         }
    }
    /***********************************************************/

    /*************************注册功能***************************/
    if(ui->login_signup_pushButton->text() == "注册")
    {
        QByteArray bu_name = ui->name_lineEdit->text().toUtf8();
        QByteArray bu_IDcard = ui->idcardnum_lineEdit->text().toUtf8();
        QByteArray bu_tel = ui->tel_num_lineEdit->text().toUtf8();
        QByteArray bu_pwd = ui->password_lineEdit->text().toUtf8();
        char *u_name = bu_name.data();
        char *u_IDcard = bu_IDcard.data();
        char *u_tel = bu_tel.data();
        char *u_pwd = bu_pwd.data();
        QString str = QString("insert into user_info(u_name, u_IDcard, u_tel, u_pwd)values('%1', '%2', '%3', '%4')").arg(u_name).arg(u_IDcard).arg(u_tel).arg(u_pwd);
        if(ui->idcardnum_lineEdit->text().isEmpty() || ui->name_lineEdit->text().isEmpty() || ui->tel_num_lineEdit->text().isEmpty() || ui->password_lineEdit->text().isEmpty())
        {
            QMessageBox::about(NULL, "提示", "请输入完整信息!");
            ui->idcardnum_lineEdit->setFocus();
        }
        else
        {
            QSqlTableModel model;
            model.setTable("user_info");
            model.setFilter(tr("u_IDcard = '%1' and u_tel = '%2'").arg(ui->idcardnum_lineEdit->text()).arg(ui->tel_num_lineEdit->text()));
            model.select();
            if(model.rowCount() == 1)
            {
                QMessageBox::about(NULL, "提示", "该用户已注册，请检查用户信息");
                ui->idcardnum_lineEdit->setFocus();
            }
            else
            {
                QSqlQuery query;
                if(query.exec(str))
                {
                    QMessageBox::about(NULL, "提示", "注册成功!");

                    clearall();
                    ui->login_radioButton->setChecked(true);

                    loginwhether = false;

                    ui->login_signup_pushButton->setText("登录");
                    ui->name_label->setVisible(false);
                    ui->name_lineEdit->setVisible(false);
                    ui->idcardnum_label->setVisible(false);
                    ui->idcardnum_lineEdit->setVisible(false);
                }
                else
                {
                    QMessageBox::about(NULL, "提示", "注册信息失败请检查!");
                }
            }
        }
    }
    /***********************************************************/
}

