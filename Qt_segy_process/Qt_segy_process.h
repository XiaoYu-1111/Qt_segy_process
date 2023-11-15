#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_segy_process.h"

#include <QMainWindow>
#include<QPushButton>
#include<QLabel>
#include<qfiledialog.h>
#include<QDebug>
#include <QImage>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QString>
#include<qslider.h>
#include<qdialog.h>

#include<qimageiohandler.h>
#include<qstackedwidget.h>
#include <opencv2/opencv.hpp>
#include<qspinbox.h>
#include<qcombobox.h>
#include<qmessagebox.h>
#include<QTextEdit>

#include <QGraphicsWidget>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QFont>

class Qt_segy_process : public QMainWindow
{
    Q_OBJECT

public:
    Qt_segy_process(QWidget *parent = nullptr);
    ~Qt_segy_process();

public slots:
    void on_stackpage1_change_clicked();//页面跳转1
    void on_stackpage2_change_clicked();//页面跳转1
    void on_stackpage3_change_clicked();//页面跳转1
    void on_stackpage4_change_clicked();//页面跳转1

public:
    QWidget* main_left_Widget;
    QWidget* main_center_Widget;
    QWidget* main_right_Widget;


    QStackedWidget* stackedWidget1;
    QWidget* page1;//页面成员声明
    QWidget* page2;
    QWidget* page3;
    QWidget* page4;
    QWidget* page5;

public:
    QString  OpenFile_path;
    QString  SaveFile_path;
    cv::Mat src;
    cv::Mat dst; // 声明作为成员变量

public://公共成员segy
    QLabel* label_picture;
    QLabel* page3_label1;
    QString  OpenFile_segy;//打开路径

    QTextEdit* textEdit1;

    QString  SaveFile_segy;//存储路径
    float minValue;
    float maxValue;
    std::vector<std::vector<float>> dataArray;// 原始得到的data
    std::vector<std::vector<float>> dataArray_real;// 真实数据
    std::vector<std::vector<float>> dataArray_save;// 最终数据


    std::vector<std::vector<float>> agc_save_data;//保存agc后的数据

    QSpinBox* windows_size_value;
    QSpinBox* agc_trace_i;

    QDoubleSpinBox* fft_sample_rate;//设置浮点数
    QSpinBox* data_trace_i;

public slots://segy数据槽函数

    void open_segy();
    void show_segy();
    void save_segy();
    void save_segy_picture();

    void save_AGC_segy();

    std::vector<std::vector<float>> getsegyarray(const std::string& inputfile);//read

    float ibm2float(int x);
    int swap4byte(int value);
    std::vector<std::vector<float>> normalized(std::vector<std::vector<float>> dataArray);
    std::vector<std::vector<float>> transposeMatrix(std::vector<std::vector<float>> matrix);
    float findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag);

    cv::Mat dataArray2image(std::vector<std::vector<float>> dataArray);

    float calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize);

    void dataArrayAGC();//AGC部分

    void opencv_fft();//计算fft，opencv中自带
    void chart_fftshow();

    void trace_i_agc();


private:
    Ui::Qt_segy_processClass ui;
};
