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

    QDockWidget* dockWidget1;

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
    std::vector<std::vector<float>> stocked_data;
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
    

    int lowThreshold = 50;  // Ĭ�ϵ���ֵ
    int highThreshold = 100; // Ĭ�ϸ���ֵ
    QSlider* lowThresholdSlider;
    QSlider* highThresholdSlider;

    QSpinBox* dft_trace_i;
    QSpinBox* dft_trace_sample;
    QSpinBox* StockTF_trace_i;
    QSpinBox* StockTF_trace_samplerate;

    std::vector<float> trace_i_data_dft_real;
    std::vector<float> trace_i_data_idft_real;//��任���
    std::vector<std::complex<float>> trace_i_data_dft_result;

    std::vector<float>opencv_fft_1d_Ampli;//opencv_fft_1d��ֵ����
    //STft
    QSpinBox* header_samplerate;//ȫ�ֲ�����
    QSpinBox* freqlow_st;
    QSpinBox* freqhigh_st;
    QSpinBox* alpha_st;
    QPushButton* stack_save;//stockwell save
    QPushButton* stack_close;
    /*std::vector<vector<complex<double>>> data_s;*/
    std::vector<double> signal_st_i;//�洢�������ݿռ�
    std::vector<double> t;// �洢����ʱ������t
    QChart* chart_s_data;
    QSplineSeries* series_stock;
    QProgressBar* progress_bar;
    //CWT
    std::vector<double> signal_cwt_i;//�洢�������ݿռ�
    QSpinBox* cwt_trace_i;

    //stft
    std::vector<double>signal_stft_i;
    QSpinBox* stft_trace_i;
    QSpinBox* stft_windows_size;
    QSpinBox* stft_hop_length;
    QSplineSeries* series_stft;

    //filter  1d
    QSpinBox* filter1d_tracei;

    QSpinBox* kernelsize_filter1d;
    std::vector<double> signal_filter1d_tracei;
    QSplineSeries* series_signal_filter1d;
    QSplineSeries* filter1d_signal_result;
    QComboBox* ComboBox_filter1d_type;

    //fft2d-fk
    std::vector<std::vector<float>> FFT2_FK_data;

public slots://segy���ݲۺ���

    void open_segy();
    void open_csv();
    void show_segy();
    void save_segy();
    void save_segy_picture();

    void save_AGC_segy();

    std::vector<std::vector<float>> getsegyarray(const std::string& inputfile);//read
    std::vector<std::vector<float>>get_partsegyarray(int row,int col);//��ȡpart_array

    float ibm2float(int x);
    int swap4byte(int value);
    std::vector<std::vector<float>> normalized(std::vector<std::vector<float>> matrix);
    std::vector<std::vector<float>> normalizeColumns(std::vector<std::vector<float>> matrix);//��׼��
    std::vector<std::vector<float>> transposeMatrix(std::vector<std::vector<float>> matrix);
    float findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag);
    double findExtremeValue(const std::vector<double>& s, int flag);
    float findExtremeValue(const std::vector<float>& s, int flag);//����
    cv::Mat dataArray2image(std::vector<std::vector<float>> dataArray);
    void data2d2image(std::vector<std::vector<float>> dataArray);
    float calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize);
    std::vector<float> calculate_energy(std::vector<std::vector<float>> matrix, int calculateFor);
    void trace_i_agc();//��������agc
    void dataArrayAGC();//AGC����
    std::vector<std::vector<float>> Exc_min(std::vector<std::vector<float>> matrix);//�г���Сֵ
    void opencv_fft_1d();//����fft��opencv���Դ�
    void save_opencv_dft_i_real();
    std::vector<std::complex<float>> discrete_fourier_transform(const std::vector<float> x);
    std::vector<std::vector<float>> opencv_fft_1d(std::vector<std::vector<float>> matrix, int tracei, int sampling);//����fft��opencv���Դ�
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
    void csvdata2dataarray();//csv����תdataarray

    //ͼ���ʽת��
    cv::Mat QImage2Mat(const QImage& image);
    QImage Mat2QImage(const cv::Mat& mat);
    void drawAxes(QImage& image);
    ///ʱƵ��������
    //part1����S�任
    void STOCK_function();
    std::vector<std::vector<std::complex<double>>> myst(const std::vector<double> t, const std::vector<double> Sig,
        double freqlow, double freqhigh, double alpha);
    void calculate_st_main();
    void  save_stacked_data();
    void  close_stackwindow();
    void  save_stackimage();
    //part2-CWT
    void CWT_function();
    void CWT_calcualte();
    //part3-STFT
    void STFT_function();
    double abs(std::complex<double> z);
    void calculate_stft_main();
    std::vector<std::vector<std::complex<double>>> stft(const std::vector<double> signal,
        int window_size, int hop_length,
        const std::vector<double> window_fn);

    //
    //��̬����
    void drawcurve();
    void draw_dynamic_curve();
    void Timeout_handler();
    //audio����
    void draw_audio_curve2();
    //�״�ͼ
    void PolarChart();
    void PolarChart2();

    void show_data2image();
    void data1d_2chartview(std::vector<float> data);

    //page2_center
    void cvdft_1d_widget();
    void update_partsegydata();
    void updata_opencv_fft_1d();
    void updateLowThreshold_row(int value);
    void updateHighThreshold_col(int value);
    //����Ҷ�任
    void DFT_custom_1d_widget();
    void display_dft_chart_window();
    void save_trace_i_dft_real();
    void save_1d_data(std::vector<float> data_1d);
    void save_2d_data(std::vector<std::vector<float>> data_2d);
    //����Ҷ��任
    void IDFT_custom_1d_widget();
    void display_idft_chart_window();
    std::vector<std::complex<float>> inverse_discrete_fourier_transform(const std::vector<float> x);
    //2d����Ҷ�任-fk�任
    void FFT2_FK();
    void FFT2_FK_widget();
    std::vector<std::vector<float>> FFT2_FK_t(std::vector<std::vector<float>> data_2d);
    void FFT2_FK_save();
    
    //page2_right
    void Filter_widget();
    void filter1d_process();
    void save_filter1d_data();

    std::vector<double> medianFilter(std::vector<double> inputSignal, int kernelSize);
    //page4
    //3d
    void draw3DData();
    void draw3Dsurface();


public:
    QWidget* widget_info;//��Ϣ����
    QPushButton* info_close;

public slots:
    ///toolbar
    //setting
    void setting_header();
    void confirm_header();

    void stylesheet_change_1();
    void stylesheet_change_2();
    void changeAllStyles_widget();
    void changeAllStyles(QWidget* widget, const QString& newStyle);
    //version
    void show_version_info();//��ʾ�汾��Ϣ
    void closeVersionInfo();
    bool eventFilter(QObject* obj, QEvent* event);

private:
    Ui::Qt_segy_processClass ui;
};


