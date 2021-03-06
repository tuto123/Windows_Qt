/*************************************************
FileName: mainwindow.cpp
Author: tuto; Version: 1.0; Date:2020-01-31;
Description: 本项目使用的为haarcascade_frontalface_alt.xml的
             分类级联器，使用步骤为1、人脸提取， 2、训练模型，
             3、人脸识别
Version: 1.0
Function List: on_pushButton_clicked();    // 1、人脸提取
               on_pushButton_2_clicked();    // 2、训练模型
               on_pushButton_3_clicked();    // 3、人脸识别
               takefacesShowHelpText();
               nameimport();
               face_image_save(QString dir_name, QString cascade_path);
History:
  1、Date：
     Author:
     Modification:
*************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QDir>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/face.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

int face_image_save(QString dir_name, QString cascade_path);
int face_model_train_save(string cvs_path);
int face_recg(Mat image, QString cascade_path);

QString cascade_xml_path = "E:\\QT5.6.1\\project\\FaceExtraction\\FaceExtraction\\haarcascade_frontalface_alt.xml";
QString face_image_path = "E:\\QT5.6.1\\project\\FaceExtraction\\FaceExtraction\\faces\\";
QString cvs_path = "E:\\QT5.6.1\\project\\FaceExtraction\\FaceExtraction\\faces_recg\\";
QString faces_models_path = "E:\\QT5.6.1\\project\\FaceExtraction\\FaceExtraction\\faces_models\\my_lbph_face_model.xml";

QString name;
QString name_cvs_path;
Ptr<LBPHFaceRecognizer> lbph_model;

int label_number = 1;

#define MY_SIZE  Size(92,112)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*************************************************
Function: takefacesShowHelpText()
Description: 第一个步骤提取人脸的使用帮助说明窗口
Calls:
Called by:
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void MainWindow::takefacesShowHelpText()
{

    QDialog *helpdlg;
    QLabel *helplabel;
    helpdlg = new QDialog(this);
    helpdlg->setWindowTitle(QStringLiteral("人脸提取"));
    helpdlg->setFixedSize(400,280);
    helplabel = new QLabel(helpdlg);
    QFont font ( "Microsoft YaHei", 10, 75);
    helplabel->setFont(font);
    helplabel->setText("此Demo为人脸提取\n"
                       "请面对摄像头，变换人脸角度进行采样\n");

    helpdlg->show();

}

/*************************************************
Function: write_cvs(QString& filename, QString line, int label_number, char separator = ';')
Description: 将图片信息存储到对应的文件路径中
Calls:
Called by: face_image_save(QString dir_name, QString cascade_path)
Tablle Accessed:
Table Updated:
Input: QString& filename, QString line, int label_number, char separator = ';'
Output:
Return:
Others:
*************************************************/
void write_cvs(QString& filename, QString line, int label_number, char separator = ';')
{
    ofstream cvs_file;
    String strfilename = filename.toStdString();
    String strline = line.toStdString();
    string str = strline + separator + format("%d\n", label_number);

    //printf("%s\n", str.c_str());
    cvs_file.open(strfilename,ios::app);
    if (cvs_file.is_open())
    {
        cvs_file << str;
        cvs_file.close();
    }
}

/*************************************************
Function: face_image_save(QString dir_name, QString cascade_path)
Description: 将对提取的人脸图片及图片信息存储到指定的路径中
Calls: face_image_save(QString dir_name, QString cascade_path)
       write_cvs(QString& filename, QString line, int label_number, char separator = ';')
Called by: nameimport()
Tablle Accessed:
Table Updated:
Input:
Output:
Return: ret
Others:
*************************************************/
int face_image_save(QString dir_name, QString cascade_path)
{
    QDir dir(dir_name);

    //判断文件夹是否存在，否则创建
    if (!dir.exists())
    {
        dir.mkdir(dir_name);
    }
    else
    {
        qDebug()<<"人脸图片已经保存在数据库，不需要重复读取\n";    //已录入将不重复录入
        return -1;
    }

    VideoCapture capture;

    // 打开笔记本摄像头
    capture.open(0);
    if (!capture.isOpened())
    {
        qDebug("can't open camera...\n");
        return -1;
    }

    // 加载分类器
    String strcascade_path = cascade_path.toStdString();
    CascadeClassifier cascade;
    cascade.load(strcascade_path);
    if (cascade.empty())
    {
        printf("can't load classifier\n");
        return -1;
    }

    Mat img, img_gray, faceROI;
    vector<Rect> faces;
    int count = 0;
    String my_path, tmp_path;

    while (true)
    {
        capture.read(img);
        cvtColor(img, img_gray, CV_RGB2GRAY);	// 转化为灰度图
        equalizeHist(img_gray, img_gray);		// 直方图均衡化
        cascade.detectMultiScale(img_gray, faces, 1.1, 6, 0, Size(30, 30));	// 人脸识别，获取faces矢量数据集

        if (faces.size() > 0)
        {
            for (int i = 0; i < faces.size(); ++i)
            {
                faceROI = img_gray(faces[i]);    // ROI部分为将要保存的图片，用img_gray获取灰度图部分，保存成灰度图；如果将img_gray改为img，就变成彩色图片了
                resize(faceROI, faceROI, MY_SIZE);    // 调整ROI图片大小到指定大小
                rectangle(img, faces[i], Scalar(0, 255, 0), 2, 8, 0);
                imshow("view", img);	// 显示视频图像
                imshow("ROI", faceROI);	// 显示ROI区域

                tmp_path = format("%d.jpg", count++);
                String strdir_name = dir_name.toStdString();
                my_path = strdir_name + tmp_path;
                imwrite(my_path, faceROI);		//保存采集到的图片到指定目录
                QString qstrmy_path = QString::fromStdString(my_path);
                qDebug()<<qstrmy_path;

                name_cvs_path = cvs_path + name + ".txt" ;
                write_cvs(name_cvs_path, qstrmy_path, label_number);
            }
        }

        if (waitKey(10) == 27 || count == 30)
        {
            break;
        }
    }

    capture.release();
    destroyAllWindows();

    return 0;
}

/*************************************************
Function: nameimport()
Description: 将改人脸姓名输入框后将创建对应的文件并将人脸
             图像存储至该文件夹中
Calls: face_image_save(QString dir_name, QString cascade_path)
Called by: on_pushButton_clicked();
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void MainWindow::nameimport()
{
    if(nameedit->text().isEmpty())
    {
        QMessageBox::information(NULL,"提示窗口","请输入姓名！");
    }
    else
    {
        name = nameedit->text();
        namedlg -> close();
        label_number++;
        QString dir_name = face_image_path + name + "\\";    // 添加在face_image_path目录下的子文件夹
        ret = face_image_save(dir_name, cascade_xml_path);
    }
}

/*************************************************
Function: on_pushButton_clicked()
Description: 人脸提取按钮
Calls: nameimport()
Called by:
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void MainWindow::on_pushButton_clicked()
{
    // 创建新窗口
    namedlg = new QDialog(this);
    nameedit = new QLineEdit(namedlg);
    okbutton = new QPushButton(namedlg);

    // 创建新编辑框及姓名确认按钮
    nameedit -> setGeometry(50,80,150,30);
    okbutton -> setGeometry(200,180,60,30);
    okbutton -> setText("确认");

    namedlg -> setWindowTitle(QStringLiteral("名字输入框"));
    namedlg -> setFixedSize(300,250);
    namedlg -> show();

    connect(okbutton, SIGNAL(clicked()), this, SLOT(nameimport()));    // okbutton连接nameimport槽函数


}

/*************************************************
Function: read_cvs(const string& filename, vector<Mat>& img, vector<int>& lable, char separator = ';')
Description: 读取已抓取好的人脸库
Calls:
Called by: face_model_train_save(string cvs_path)
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void read_cvs(const string& filename, vector<Mat>& img, vector<int>& lable, char separator = ';')
{
    Mat tmp_img;
    ifstream cvs_file(filename.c_str());
    assert(cvs_file);
    string line, path, tag;
    while (getline(cvs_file, line))
    {
        stringstream lines(line);
        getline(lines, path, separator);
        getline(lines, tag);
        if (!path.empty() && !tag.empty())
        {
            tmp_img = imread(path, IMREAD_GRAYSCALE);   //读入图像时转成灰度图
            assert(!tmp_img.empty());
            img.push_back(tmp_img);
            lable.push_back(atoi(tag.c_str()));
        }
    }
    tmp_img.release();
}

/*************************************************
Function: face_model_train_save(string cvs_path)
Description: 人脸模型训练,读取人脸库
Calls: read_cvs(const string& filename, vector<Mat>& img, vector<int>& lable, char separator = ';')；
Called by: on_pushButton_2_clicked()
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
int face_model_train_save(string cvs_path)
{
    printf("创建人脸识别的模型并进行训练，保存训练结果中（需要一些时间）...\n");

    vector<Mat> faces;
    vector<int> labels;

    try
    {
        read_cvs(cvs_path, faces, labels);
    }
    catch (Exception &e)
    {
        cerr << "Error opening file, reason :" << e.msg << endl;
        return -1;
    }

    if (faces.size() <= 1)
    {
        printf("Too few face images\n");
        return -1;
    }

    /* 创建人脸识别的模型，并进行训练，之后保存训练结果*/
    double start3;
    double end3;
    String strname = name.toStdString();

    //LBP局部二值模式直方图
    start3 = (double)getTickCount();
    Ptr<LBPHFaceRecognizer> lbph_model = LBPHFaceRecognizer::create();
    lbph_model->train(faces, labels);
    qDebug()<<faces_models_path;
    lbph_model->setLabelInfo(label_number,name.toStdString());
    qDebug()<<QString::fromStdString(lbph_model->getLabelInfo(label_number));
    lbph_model->save(faces_models_path.toStdString());
    end3 = (getTickCount() - start3) / getTickFrequency();

    qDebug("LBP算法训练所用时间：%.5fs\n",end3);

    qDebug()<<"训练结束，保存成功！" + '\n';

    return 0;
}

/*************************************************
Function: on_pushButton_2_clicked()
Description: 训练模型按钮
Calls: face_model_train_save(string cvs_path)
Called by:
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void MainWindow::on_pushButton_2_clicked()
{
    String strcvs_path = name_cvs_path.toStdString();

    if (ret == 0)
        {
          face_model_train_save(strcvs_path);
        }
    else
    {
        QMessageBox::information(NULL,"提示窗口","加载图片库失败!");
    }
}

/*************************************************
Function: face_recg(Mat image, String cascade_path)
Description: 人脸识别，对摄像头抓取的人脸和已训练好的模型
             进行比对，如果置信值小于限定则识别成功
Calls:
Called by: on_pushButton_3_clicked()
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
int face_recg(Mat image, String cascade_path)
{
    printf("人脸识别中...\n");

    //显示读入的图片
    imshow("origin", image);

    //加载分类器
    CascadeClassifier cascade;
    cascade.load(cascade_path);
    if (cascade.empty())
    {
        printf("can't load classifier\n");
        return -1;
    }

    Mat faceROI, img_gray;
    double confidence;
    int predictPCA;

    vector<Rect> faces;
    cvtColor(image, img_gray, CV_RGB2GRAY);	// 转化为灰度图
    equalizeHist(img_gray, img_gray);		// 直方图均衡化
    cascade.detectMultiScale(img_gray, faces, 1.1, 6, 0, Size(30, 30));	//人脸识别，获取faces矢量数据集

    qDebug("size = %zd\n", faces.size());
    if (faces.size() > 0)
    {
        for (int i = 0; i < faces.size(); ++i)
        {
            faceROI = img_gray(faces[i]);
            resize(faceROI, faceROI, MY_SIZE);	//调整成训练集一样的大小
            rectangle(image, faces[i], Scalar(0, 255, 0), 2, 8, 0);


            lbph_model->predict(faceROI, predictPCA, confidence);

            qDebug("predictPCA: %d\n", predictPCA);
            qDebug("confidence: %0.5f\n", confidence);

            if (confidence < 100)
            {
                putText(image, "Recognition success", Point(faces[i].x, faces[i].y-20), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255), 4, 8);
            }
            else
            {
                putText(image, "Unaccepted Face", Point(faces[i].x, faces[i].y-20), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,0,255), 4, 8);
            }

            imshow("origin", image);
            imshow("result", faceROI);
        }
    }
    return 0;
}

/*************************************************
Function: on_pushButton_3_clicked()
Description: 人脸识别按钮
Calls: face_recg(Mat image, String cascade_path)
Called by:
Tablle Accessed:
Table Updated:
Input:
Output:
Return:
Others:
*************************************************/
void MainWindow::on_pushButton_3_clicked()
{
    Mat frame;
    VideoCapture capture;
    capture.open(0);

    // 打开摄像头
    // 读取人脸识别模型
    double  start3;
    double  end3;
    start3 = (double)getTickCount();
    lbph_model = Algorithm::load<LBPHFaceRecognizer>(faces_models_path.toStdString());		//LBP 算法
    qDebug()<<QString::fromStdString(faces_models_path.toStdString());
    end3 = (getTickCount() - start3) / getTickFrequency();
    qDebug("加载LBP算法训练模型所用时间：	%f s\n", end3);
    if(capture.isOpened())
    {
        while(1)
        {
            namedWindow("origin");
            namedWindow("result");
            capture >> frame;

            //人脸识别
            String strcascade_xml_path = cascade_xml_path.toStdString();
            face_recg(frame, strcascade_xml_path);
            char c = waitKey(10);
            if(c==27)
            {
                break;
            }
        }
    }
    else
    {
        qDebug()<<"can't open cam!";
    }

}
