#include "lockscreen.h"
#include "ui_lockscreen.h"

#include "mainwindow.h"
#include "showdata.h"

#include <QMessageBox>

LockScreen::LockScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LockScreen)
{
    ui->setupUi(this);

    QString qssFile = qssFile = ":/rec/qss/silvery.css";
    setqssstyle(qssFile);

    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}

LockScreen::~LockScreen()
{
    delete ui;
}

void LockScreen::setqssstyle(const QString &qssFile)
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

//给界面添加可以缩放背景图片
void LockScreen::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/rec/img/show_data_background.png"));
}

void LockScreen::on_pushButton_Enter_clicked()
{
    QString password;
    password = "123456";
    if(ui->lineEdit_Password->text() == password)
    {
        QMessageBox::about(NULL, "提示", "登录成功!");
#if 0
        MainWindow *mw = new MainWindow();
        mw->setWindowTitle("Home");
        this->close();
        mw->show();
#endif
        ShowData *sd = new ShowData();
        this->close();
        sd->setWindowTitle("ShowData");
        sd->show();
    }
    else
    {
        QMessageBox::about(NULL, "提示", "请输入正确的密码!");
        ui->lineEdit_Password->clear();
        ui->lineEdit_Password->setFocus();
    }
}

void LockScreen::on_pushButton_Delete_clicked()
{
    ui->lineEdit_Password->backspace();
}

void LockScreen::on_pushButton_Num1_clicked()
{
    ui->lineEdit_Password->insert("1");
}

void LockScreen::on_pushButton_Num2_clicked()
{
    ui->lineEdit_Password->insert("2");
}

void LockScreen::on_pushButton_Num3_clicked()
{
    ui->lineEdit_Password->insert("3");
}

void LockScreen::on_pushButton_Num4_clicked()
{
    ui->lineEdit_Password->insert("4");
}

void LockScreen::on_pushButton_Num5_clicked()
{
    ui->lineEdit_Password->insert("5");
}

void LockScreen::on_pushButton_Num6_clicked()
{
    ui->lineEdit_Password->insert("6");
}

void LockScreen::on_pushButton_Num7_clicked()
{
    ui->lineEdit_Password->insert("7");
}

void LockScreen::on_pushButton_Num8_clicked()
{
    ui->lineEdit_Password->insert("8");
}

void LockScreen::on_pushButton_Num9_clicked()
{
    ui->lineEdit_Password->insert("9");
}

void LockScreen::on_pushButton_Num0_clicked()
{
    ui->lineEdit_Password->insert("0");
}
