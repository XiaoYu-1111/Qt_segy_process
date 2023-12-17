#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_segy_process.h"

#include <QMainWindow>
#include <QtConcurrent>//处理多线程
#include <QFutureWatcher>
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
#include <QThread>
#include <QObject>

#include<qimageiohandler.h>
#include<qstackedwidget.h>
#include <QDockWidget>
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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QDial>
#include <QPainter>
#include<QProgressBar>

#include <QtDataVisualization>
#include<cmath>
#include <vector>
#include <numeric>
#include <complex>
#include <algorithm> 
#include <QRandomGenerator>

#include<QAudioDevice>
#include<qmediadevices.h>
#include <QAudioInput>
#include <QAudioSource>
#include<QAudioSink>
#include <QAudioFormat>

#include"xyseriesiodevice.h"

class XYSeriesIODevice;

class Qt_segy_process : public QMainWindow
{
    Q_OBJECT

public:
    Qt_segy_process(QWidget *parent = nullptr);
    ~Qt_segy_process();

public slots:
    void main_page();
    void on_stackpage1_change_clicked();//页面跳转1
    void on_stackpage2_change_clicked();//页面跳转1
    void on_stackpage3_change_clicked();//页面跳转1
    void on_stackpage4_change_clicked();//页面跳转1
    void on_stackpage5_change_clicked();//页面跳转1

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
    QString  OpenFile_csv;//打开路径

    QTextEdit* textEdit1;

    QString  SaveFile_segy;//存储路径
    float minValue;
    float maxValue;
    std::vector<std::vector<float>> dataArray;// 原始得到的data
    std::vector<std::vector<float>> dataArray_real;// 真实数据
    std::vector<std::vector<float>> dataArray_save;// 最终数据
    std::vector<std::vector<float>> dataArray_csv;// 最终数据

    std::vector<std::vector<float>> agc_save_data;//保存agc后的数据
    std::vector<std::vector<float>> stocked_data;
    QSpinBox* windows_size_value;
    QSpinBox* agc_trace_i;
    QDoubleSpinBox* fft_sample_rate;//设置浮点数
    QSpinBox* data_trace_i;
    
    //wiggle
    QGraphicsView* wiggleView;
    bool isWiggleViewCreated;
    
    QDial* wiggle_dial_1;
    QDial* wiggle_dial_2;
    QDial* wiggle_dial_3;
    QDial* wiggle_dial_4;


    QLabel* label_dial_1;
    QLabel* label_dial_2;
    QLabel* label_dial_3;
    QLabel* label_dial_4;

    int traceHeight;//每道的高度
    int traceSpacing;//道之间间距
    int sampleSpacing;//采样点之间间距
    int line_width_wiggle;

    QValueAxis* axisX_dynamic;//动态曲线
    QValueAxis* axisY_dynamic;
    QSplineSeries* series_dynamic;
    int x_index=0;

    XYSeriesIODevice* m_device;//音频部分
    QChart* m_chart ; 
    QLineSeries* m_series;
    QAudioInput* m_audioInput;
    QAudioSource* m_audioSource;

    QWidget* widget_stockwell_fun;
    QImage * qtImage2;
    

    int lowThreshold = 50;  // 默认低阈值
    int highThreshold = 100; // 默认高阈值
    QSlider* lowThresholdSlider;
    QSlider* highThresholdSlider;

    QSpinBox* dft_trace_i;
    QSpinBox* StockTF_trace_i;

    std::vector<float> trace_i_data_dft_real;

    QSpinBox* header_samplerate;//全局采样率
    QSpinBox* freqlow_st;
    QSpinBox* freqhigh_st;
    QSpinBox* alpha_st;
    QPushButton* stack_save;//stockwell save
    QPushButton* stack_close;
    /*std::vector<vector<complex<double>>> data_s;*/
    std::vector<double> signal_st_i;//存储单道数据空间
    std::vector<double> t;// 存储生成时间序列t
    QChart* chart_s_data;
    QSplineSeries* series_stock;
    

public slots://segy数据槽函数

    void open_segy();
    void open_csv();
    void show_segy();
    void save_segy();
    void save_segy_picture();

    void save_AGC_segy();

    std::vector<std::vector<float>> getsegyarray(const std::string& inputfile);//read
    std::vector<std::vector<float>>get_partsegyarray(int row,int col);//获取part_array

    float ibm2float(int x);
    int swap4byte(int value);
    std::vector<std::vector<float>> normalized(std::vector<std::vector<float>> matrix);
    std::vector<std::vector<float>> normalizeColumns(std::vector<std::vector<float>> matrix);//标准化
    std::vector<std::vector<float>> transposeMatrix(std::vector<std::vector<float>> matrix);
    float findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag);
    double findExtremeValue(const std::vector<double>& s, int flag);
    float findExtremeValue(const std::vector<float>& s, int flag);//重载
    cv::Mat dataArray2image(std::vector<std::vector<float>> dataArray);
    void data2d2image(std::vector<std::vector<float>> dataArray);
    float calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize);
    std::vector<float> calculate_energy(std::vector<std::vector<float>> matrix, int calculateFor);
    void trace_i_agc();//单道数据agc
    void dataArrayAGC();//AGC部分
    std::vector<std::vector<float>> Exc_min(std::vector<std::vector<float>> matrix);//切除极小值
    void opencv_fft_1d();//计算fft，opencv中自带

    std::vector<std::complex<float>> discrete_fourier_transform(const std::vector<float> x);
    std::vector<std::vector<float>> opencv_fft_1d(std::vector<std::vector<float>> matrix, int tracei, int sampling);//计算fft，opencv中自带
    void opencv_fft2d();//多道数据fft

    void chart_fftshow();//测试chart

    void matrix_table_show();
    void WiggleView_show_H();//wiggle显示
    void WiggleView_show_V();//wiggle显示
    void updataWigglePlot();//更新wiggle;
    void saveWiggleViewImage(QGraphicsView* view);
    void saveWiggle_1();

    void Dial_1_ValueChanged(int value);
    void Dial_2_ValueChanged(int value);
    void Dial_3_ValueChanged(int value);
    void Dial_4_ValueChanged(int value);
    void agcdata2dataarray();//将当前默认数据更换为agc数据
    void get_orignal_real();//获取实际数据data_real
    void csvdata2dataarray();//csv数据转dataarray
    
    //S变换
    void STOCK_function();
    std::vector<std::vector<std::complex<double>>> myst(const std::vector<double> t, const std::vector<double> Sig,
        double freqlow, double freqhigh, double alpha);
    void calculate_st_main();
    void  save_stacked_data();
    void  close_stackwindow();
    void  save_stackimage();
    
    //静态曲线
    void drawcurve();
    void draw_dynamic_curve();
    void Timeout_handler();
    //audio曲线
    void draw_audio_curve2();
    //雷达图
    void PolarChart();
    void PolarChart2();

    void show_data2image();
    void data1d_2chartview(std::vector<float> data);

    //page2_center
    void filter_1d_widget();
    void update_partsegydata();
    void updateLowThreshold_row(int value);
    void updateHighThreshold_col(int value);

    void DFT_custom_1d_widget();
    void display_dft_chart_window();
    void save_trace_i_dft_real();
    void save_1d_data(std::vector<float> data_1d);
    void save_2d_data(std::vector<std::vector<float>> data_2d);
    //page2_right
    void Filter_widget();
    //page4
    //3d
    void draw3DData();
    void draw3Dsurface();


public:
    QWidget* widget_info;//信息窗口
    QPushButton* info_close;

public slots:
    ///toolbar
    //setting
    void setting_header();
    void confirm_header();
    //version
    void show_version_info();//显示版本信息
    void closeVersionInfo();
    bool eventFilter(QObject* obj, QEvent* event);

private:
    Ui::Qt_segy_processClass ui;
};


