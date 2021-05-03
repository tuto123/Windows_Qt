#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void paintEvent(QPaintEvent *event);

    void setqssstyle(const QString &qssFile);

    void on_Button_ShowData_clicked();

    void on_Button_LockSreen_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
