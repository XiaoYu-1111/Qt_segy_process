#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_segy_process.h"

#include <QMainWindow>
#include <QtConcurrent>//������߳�
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

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QDial>
#include <QPainter>
#include<QProgressBar>

#include <QtDataVisualization>
#include <vector>
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
    void on_stackpage1_change_clicked();//ҳ����ת1
    void on_stackpage2_change_clicked();//ҳ����ת1
    void on_stackpage3_change_clicked();//ҳ����ת1
    void on_stackpage4_change_clicked();//ҳ����ת1
    void on_stackpage5_change_clicked();//ҳ����ת1

public:
    QWidget* main_left_Widget;
    QWidget* main_center_Widget;
    QWidget* main_right_Widget;

    QStackedWidget* stackedWidget1;
    QWidget* page1;//ҳ���Ա����
    QWidget* page2;
    QWidget* page3;
    QWidget* page4;
    QWidget* page5;

public:
    QString  OpenFile_path;
    QString  SaveFile_path;
    cv::Mat src;
    cv::Mat dst; // ������Ϊ��Ա����

public://������Աsegy
    QLabel* label_picture;
    QLabel* page3_label1;
    QString  OpenFile_segy;//��·��
    QString  OpenFile_csv;//��·��

    QTextEdit* textEdit1;

    QString  SaveFile_segy;//�洢·��
    float minValue;
    float maxValue;
    std::vector<std::vector<float>> dataArray;// ԭʼ�õ���data
    std::vector<std::vector<float>> dataArray_real;// ��ʵ����
    std::vector<std::vector<float>> dataArray_save;// ��������
    std::vector<std::vector<float>> dataArray_csv;// ��������

    std::vector<std::vector<float>> agc_save_data;//����agc�������
    QSpinBox* windows_size_value;
    QSpinBox* agc_trace_i;
    QDoubleSpinBox* fft_sample_rate;//���ø�����
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

    int traceHeight;//ÿ���ĸ߶�
    int traceSpacing;//��֮����
    int sampleSpacing;//������֮����
    int line_width_wiggle;

    QValueAxis* axisX_dynamic;//��̬����
    QValueAxis* axisY_dynamic;
    QSplineSeries* series_dynamic;
    int x_index=0;

    XYSeriesIODevice* m_device;//��Ƶ����
    QChart* m_chart ; 
    QLineSeries* m_series;
    QAudioInput* m_audioInput;
    QAudioSource* m_audioSource;

    QWidget* widget_stockwell_fun;
    QImage * qtImage2;
    QPushButton* stack_save;//stockwell save
    QPushButton* stack_close;


public slots://segy���ݲۺ���

    void open_segy();
    void open_csv();
    void show_segy();
    void save_segy();
    void save_segy_picture();

    void save_AGC_segy();

    std::vector<std::vector<float>> getsegyarray(const std::string& inputfile);//read

    float ibm2float(int x);
    int swap4byte(int value);
    std::vector<std::vector<float>> normalized(std::vector<std::vector<float>> matrix);
    std::vector<std::vector<float>> normalizeColumns(std::vector<std::vector<float>> matrix);//��׼��
    std::vector<std::vector<float>> transposeMatrix(std::vector<std::vector<float>> matrix);
    float findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag);
    double findExtremeValue(const std::vector<double>& s, int flag);
    float findExtremeValue(const std::vector<float>& s, int flag);//����
    cv::Mat dataArray2image(std::vector<std::vector<float>> dataArray);

    float calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize);
    
    void trace_i_agc();//��������agc
    void dataArrayAGC();//AGC����
    std::vector<std::vector<float>> Exc_min(std::vector<std::vector<float>> matrix);//�г���Сֵ

    void opencv_fft_1d();//����fft��opencv���Դ�
    void opencv_fft2d();//�������fft

    void chart_fftshow();//����chart

    void matrix_table_show();
    void WiggleView_show_H();//wiggle��ʾ
    void WiggleView_show_V();//wiggle��ʾ
    void updataWigglePlot();//����wiggle;
    void saveWiggleViewImage(QGraphicsView* view);
    void saveWiggle_1();

    void Dial_1_ValueChanged(int value);
    void Dial_2_ValueChanged(int value);
    void Dial_3_ValueChanged(int value);
    void Dial_4_ValueChanged(int value);
    void agcdata2dataarray();//����ǰĬ�����ݸ���Ϊagc����
    void get_orignal_real();//��ȡʵ������data_real
    //3d
    void draw3DData();
    //S�任

    void STOCK_function();
    std::vector<std::vector<std::complex<double>>> myst(const std::vector<double> t, const std::vector<double> Sig,
        double freqlow, double freqhigh, double alpha);
    void  close_stackwindow();
    void  save_stackimage();
    //��̬����
    void drawcurve();
    void draw_dynamic_curve();
    
    void Timeout_handler();
    //sudio����
    void draw_audio_curve2();

    //�״�ͼ
    void PolarChart();
    void PolarChart2();

    void show_data2image();

public:
    QWidget* widget_info;//��Ϣ����
    QPushButton* info_close;

public slots:
    ///toolbar
    void show_version_info();//��ʾ�汾��Ϣ
    void closeVersionInfo();
    bool eventFilter(QObject* obj, QEvent* event);

private:
    Ui::Qt_segy_processClass ui;
};
