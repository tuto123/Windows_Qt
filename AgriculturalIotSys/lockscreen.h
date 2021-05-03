#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H

#include <QWidget>

namespace Ui {
class LockScreen;
}

class LockScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LockScreen(QWidget *parent = 0);
    ~LockScreen();

private slots:
    void paintEvent(QPaintEvent *event);

    void setqssstyle(const QString &qssFile);

    void on_pushButton_Num1_clicked();

    void on_pushButton_Num2_clicked();

    void on_pushButton_Num3_clicked();

    void on_pushButton_Num4_clicked();

    void on_pushButton_Num5_clicked();

    void on_pushButton_Num6_clicked();

    void on_pushButton_Num7_clicked();

    void on_pushButton_Num8_clicked();

    void on_pushButton_Num9_clicked();

    void on_pushButton_Num0_clicked();

    void on_pushButton_Enter_clicked();

    void on_pushButton_Delete_clicked();

private:
    Ui::LockScreen *ui;
};

#endif // LOCKSCREEN_H
