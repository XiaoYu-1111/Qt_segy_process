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
    void on_stackpage1_change_clicked();//ҳ����ת1
    void on_stackpage2_change_clicked();//ҳ����ת1
    void on_stackpage3_change_clicked();//ҳ����ת1
    void on_stackpage4_change_clicked();//ҳ����ת1

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

    QTextEdit* textEdit1;

    QString  SaveFile_segy;//�洢·��
    float minValue;
    float maxValue;
    std::vector<std::vector<float>> dataArray;// ԭʼ�õ���data
    std::vector<std::vector<float>> dataArray_real;// ��ʵ����
    std::vector<std::vector<float>> dataArray_save;// ��������


    std::vector<std::vector<float>> agc_save_data;//����agc�������

    QSpinBox* windows_size_value;
    QSpinBox* agc_trace_i;

    QDoubleSpinBox* fft_sample_rate;//���ø�����
    QSpinBox* data_trace_i;

public slots://segy���ݲۺ���

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

    void dataArrayAGC();//AGC����

    void opencv_fft();//����fft��opencv���Դ�
    void chart_fftshow();

    void trace_i_agc();


private:
    Ui::Qt_segy_processClass ui;
};
