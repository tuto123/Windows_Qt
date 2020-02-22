/*************************************************
Copyright (C), 2020-2020, XK_605
File name: main.cpp
Author: tuto; Version: 1.0; Date: 2020-01-31;
Description: 本项目的主要功能为识别出人脸并提取出来；
             目前仅能识别一个人脸信息;
             需改进的地方1、可重复提取人脸到指定文件夹
                       2、训练特定路径的人脸图片文件夹
                       3、可将训练信息存储到同一模型中
                       4、可识别多个人脸
Others:
Function List:
  1、main(int argc, char *argv[]);
History:
  1、Date：
     Author:
     Modification:
*************************************************/
#include "mainwindow.h"
#include <QApplication>

/*************************************************
Function: main(int argc, char *argv[])
Description: 程序入口
Calls:
Called by:
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
