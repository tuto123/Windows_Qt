#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "showdata.h"
#include "lockscreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString qssFile = qssFile = ":/rec/qss/black.css";
    setqssstyle(qssFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

//给界面添加可以缩放背景图片
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.setOpacity(0.9);          //背景图片透明度
    myPainter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/rec/img/show_data_background.png"));
}

void MainWindow::on_Button_ShowData_clicked()
{
    ShowData *sd = new ShowData();
    this->close();
    sd->setWindowTitle("ShowData");
    sd->show();
}

void MainWindow::on_Button_LockSreen_clicked()
{
    LockScreen *ls = new LockScreen();
    this->close();
    ls->setWindowTitle("LockScreen");
    ls->show();
}
