#include "Qt_segy_process.h"
#include"style.h"

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QString>
#include<QTextEdit>
#include <fstream>//header cpp std;
#include <cstring>
#include<cmath>
#include <vector>
#include <algorithm> 


using namespace cv;
using namespace std;


Qt_segy_process::Qt_segy_process(QWidget *parent)
    : QMainWindow(parent), isWiggleViewCreated(false)
{
    ui.setupUi(this);
    this->setWindowTitle("QT-SEGY-processing software");
    
    stylesheet_QT style1;
    ui.centralWidget->setStyleSheet(style1.widget_gray2);

    ui.statusBar->setMinimumHeight(30);
    ui.statusBar->setMaximumHeight(100);
    ui.mainToolBar->setMinimumHeight(30);

    main_left_Widget = new QWidget;
    main_center_Widget = new QWidget;
    main_right_Widget = new QWidget;

    QHBoxLayout* main_layout = new QHBoxLayout(ui.centralWidget);

    main_layout->setContentsMargins(0, 0, 0, 0);

    main_layout->addWidget(main_left_Widget);
    main_layout->addWidget(main_center_Widget);
    main_layout->addWidget(main_right_Widget);

    main_left_Widget->setStyleSheet(style1.widget_gray1);
    main_center_Widget->setStyleSheet(style1.widget_gray3);
    main_right_Widget->setStyleSheet(style1.widget_gray1);

    main_left_Widget->setMinimumWidth(150);
    main_left_Widget->setMaximumWidth(200);

    main_right_Widget->setMinimumWidth(150);
    main_right_Widget->setMaximumWidth(200);
    //��ര��

    QVBoxLayout* left_layout = new QVBoxLayout(main_left_Widget);


    QLabel* main_label = new QLabel("SEGY-DATA");
    QPushButton* main_button = new QPushButton("Main_button");

    left_layout->addWidget(main_label);
    left_layout->addWidget(main_button);

    main_button->setStyleSheet(style1.button_save_style1);//main
    main_button->setToolTip("<html><font size='5' color='lightgreen'>MAIN PAGE</font></html>");
    main_button->setMinimumSize(80, 40);
    main_label->setAlignment(Qt::AlignCenter);
    main_label->setStyleSheet(style1.label1);
    main_label->setMaximumSize(200, 50);

    QPushButton* open_button = new QPushButton("open_file");//open
    open_button->setStyleSheet(style1.button_save_style1);
    open_button->setMinimumSize(80, 40);
    left_layout->addWidget(open_button);

    QPushButton* show_button = new QPushButton("show_data");//show
    show_button->setStyleSheet(style1.button_save_style1);
    show_button->setMinimumSize(80, 40);
    left_layout->addWidget(show_button);

    QPushButton* save_picture_button = new QPushButton("save_picture");//save
    save_picture_button->setStyleSheet(style1.button_save_style1);
    save_picture_button->setMinimumSize(80, 40);
    left_layout->addWidget(save_picture_button);

    QPushButton* save_button = new QPushButton("save_data");//save
    save_button->setStyleSheet(style1.button_save_style1);
    save_button->setMinimumSize(80, 40);
    left_layout->addWidget(save_button);

    //�Ҳര��
    QVBoxLayout* right_layout = new QVBoxLayout(main_right_Widget);

    QPushButton* Page1_button = new QPushButton("page1_button");//open
    Page1_button->setStyleSheet(style1.button_save_style1);
    Page1_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page1_button);

    QPushButton* Page2_button = new QPushButton("2D_process");//open
    Page2_button->setStyleSheet(style1.button_save_style1);
    Page2_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page2_button);

    QPushButton* Page3_button = new QPushButton("2D Page");//open
    Page3_button->setStyleSheet(style1.button_save_style1);
    Page3_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page3_button);

    QPushButton* Page4_button = new QPushButton("3D Page");//open
    Page4_button->setStyleSheet(style1.button_save_style1);
    Page4_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page4_button);

    QPushButton* Page5_button = new QPushButton("page5_button");//open
    Page5_button->setStyleSheet(style1.button_save_style1);
    Page5_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page5_button);

    //�м�ҳ��
    QVBoxLayout* center_layout = new QVBoxLayout(main_center_Widget);

    stackedWidget1 = new QStackedWidget;//�ѵ�����
    center_layout->addWidget(stackedWidget1);
    center_layout->setContentsMargins(0, 0, 0, 0);
    page1 = new QWidget;//�����ҳ��
    page2 = new QWidget;
    page3 = new QWidget;
    page4 = new QWidget;
    page5 = new QWidget;

    stackedWidget1->addWidget(page1);
    stackedWidget1->addWidget(page2);
    stackedWidget1->addWidget(page3);
    stackedWidget1->addWidget(page4);
    stackedWidget1->addWidget(page5);
    page1->setStyleSheet("background-color:rgb(255,255,255);border-radius:5px;");//21������ʽ����
    page2->setStyleSheet("background-color:rgb(210,210,210);border-radius:5px;");//22������ʽ����
    page3->setStyleSheet("background-color:rgb(220,220,220);border-radius:5px;");//23������ʽ����
    page4->setStyleSheet("background-color:rgb(230,230,230);border-radius:5px;");//24������ʽ����
    page5->setStyleSheet("background-color:rgb(240,240,240);border-radius:5px;");//25������ʽ����


    //��ҳ��ۺ���
    connect(open_button, SIGNAL(clicked()), this, SLOT(open_segy()));//���ļ�
    connect(show_button, SIGNAL(clicked()), this, SLOT(show_segy()));//���ļ�
    connect(save_picture_button, SIGNAL(clicked()), this, SLOT(save_segy_picture()));//���ļ�
    connect(save_button, SIGNAL(clicked()), this, SLOT(save_segy()));//���ļ�
    //��תҳ��
    connect(main_button, SIGNAL(clicked()), this, SLOT(on_stackpage1_change_clicked()));// �л�����һҳ
    connect(Page1_button, SIGNAL(clicked()), this, SLOT(on_stackpage1_change_clicked()));// �л�����һҳ

    connect(Page2_button, SIGNAL(clicked()), this, SLOT(on_stackpage2_change_clicked()));// �л����ڶ�ҳ
    connect(Page3_button, SIGNAL(clicked()), this, SLOT(on_stackpage3_change_clicked()));// �л�������ҳ
    connect(Page4_button, SIGNAL(clicked()), this, SLOT(on_stackpage4_change_clicked()));// �л�������ҳ
    connect(Page5_button, SIGNAL(clicked()), this, SLOT(on_stackpage5_change_clicked()));

    ///toolbar����
    //part1
    QAction* myAction1 = new QAction("Main", this);//��������Ϊ
    // ���������˵�����Ӹ���ѡ��
    QMenu* myMenu = new QMenu(this);
    QAction* option1Action = new QAction("Option 1", this);
    myMenu->addAction(option1Action);
    myMenu->addAction("Option 2");
    myMenu->addAction("Option 3");
    // �������˵�����������
    myAction1->setMenu(myMenu);
    ui.mainToolBar->addAction(myAction1);
    //part data change
    QAction* myAction_datachange = new QAction("Data", this);
    QMenu* datachange_menu = new QMenu(this);
    QAction* option1_agcdata2dataarray = new QAction("Agc2data", this);
    QAction* option1_get_realdata = new QAction("Get_realdata", this);
    datachange_menu->addAction(option1_agcdata2dataarray);
    datachange_menu->addAction(option1_get_realdata);

    myAction_datachange->setMenu(datachange_menu);

    ui.mainToolBar->addAction(myAction_datachange);

    //part_version
    QAction* myAction2 = new QAction("version", this);//����versionҳ�����
    QMenu* myMenu_version = new QMenu(this);//����version�˵�
    QAction* version_info = new QAction("version_info", this);
    myMenu_version->addAction(version_info);
    myMenu_version->addAction("option_2");
    myAction2->setMenu(myMenu_version);
    ui.mainToolBar->addAction(myAction2);//��ӽ���ڵ�toolbar

    ///toolbar����solt

    connect(version_info, SIGNAL(triggered()), this, SLOT(show_version_info()));
    connect(option1_agcdata2dataarray, SIGNAL(triggered()), this, SLOT(agcdata2dataarray()));
    connect(option1_get_realdata, SIGNAL(triggered()), this, SLOT(get_orignal_real()));

    ///page1
    QVBoxLayout* page1_layout = new QVBoxLayout(page1);

    label_picture = new QLabel;
    // ����ͼƬ������Ϊ QLabel �ı���
    QString  path="D:\\Code\\visual_code\\Open_Cv\\Qt_segy_process\\Qt_segy_process\\icon\\flower.jpg";  // �滻Ϊ���ͼƬ·��
    
    label_picture->setMinimumSize(600, 400);

    Mat src = cv::imread(path.toStdString());

    QImage qtImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888);
    label_picture->setPixmap(QPixmap::fromImage(qtImage).scaled(label_picture->size()));

    label_picture->setAlignment(Qt::AlignCenter);
    page1_layout->addWidget(label_picture);


    QWidget* page1_widget1 = new QWidget();
    QHBoxLayout* page1_widget1_layout = new QHBoxLayout(page1_widget1);///��һҳ���±ߴ���
    page1_layout->addWidget(page1_widget1);
    page1_widget1->setStyleSheet("background-color:rgb(200,200,200)");
    page1_widget1->setMaximumHeight(100);

    textEdit1 = new QTextEdit();///������Ϣ
    textEdit1->setReadOnly(true);
    textEdit1->setStyleSheet("background-color:rgb(255,255,255);font-size:20px; ");
    page1_widget1_layout->addWidget(textEdit1);
    textEdit1->setPlainText("version_1.0,author by rain!");

    //page2
    QVBoxLayout* page2_layout = new QVBoxLayout(page2);

    QWidget* page2_widget1 = new QWidget();
    QWidget* page2_widget2 = new QWidget();
    QWidget* page2_widget3 = new QWidget();
    QWidget* page2_widget4 = new QWidget();

    QHBoxLayout* page2_widget1_layout = new QHBoxLayout(page2_widget1);
    QHBoxLayout* page2_widget2_layout = new QHBoxLayout(page2_widget2);
    QHBoxLayout* page2_widget3_layout = new QHBoxLayout(page2_widget3);
    QHBoxLayout* page2_widget4_layout = new QHBoxLayout(page2_widget4);

    page2_widget1->setMaximumHeight(100);
    page2_widget2->setMaximumHeight(100);
    page2_widget3->setMaximumHeight(100);
    page2_widget4->setMaximumHeight(100);

    page2_layout->addWidget(page2_widget1);
    page2_layout->addWidget(page2_widget3);//������ӽ����˳���Ų�
    page2_layout->addWidget(page2_widget2);
    page2_layout->addWidget(page2_widget4);

    page2_widget1->setStyleSheet("background-color:rgb(100,100,100);");
    page2_widget2->setStyleSheet("background-color:rgb(100,100,100);");
    page2_widget3->setStyleSheet("background-color:rgb(100,100,100);");
    page2_widget4->setStyleSheet("background-color:rgb(100,100,100);");
    ///page2_widget1
    QPushButton* button_AGC = new QPushButton("AGC_2D");
    button_AGC->setStyleSheet(style1.button_save_style1);
    button_AGC->setMaximumSize(100, 50);
    page2_widget1_layout->addWidget(button_AGC);

    QPushButton* AGC_single = new QPushButton("AGC_tracei");
    AGC_single->setStyleSheet(style1.button_save_style1);
    AGC_single->setMaximumSize(100, 50);
    page2_widget1_layout->addWidget(AGC_single);

    QLabel* windows_size = new QLabel("windows_size");
    windows_size->setMaximumSize(100, 50);
    windows_size->setStyleSheet("background-color:lightgreen");
    page2_widget1_layout->addWidget(windows_size);

    windows_size_value = new QSpinBox();//����windows_size��ֵ
    windows_size_value->setToolTip("<html><font size='5' color='lightgreen'>AGC windows size!</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    windows_size_value->setMaximumWidth(100);
    windows_size_value->setMaximumHeight(50);
    windows_size_value->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget1_layout->addWidget(windows_size_value);

    QLabel* label_trace_i = new QLabel("trace i");///�ָ��ǩ
    label_trace_i->setMaximumSize(100, 50);
    label_trace_i->setStyleSheet("background-color:lightgreen");
    page2_widget1_layout->addWidget(label_trace_i);

    agc_trace_i = new QSpinBox();//����windows_size��ֵ
    agc_trace_i->setToolTip("<html><font size='5' color='lightgreen'>AGC trace i!</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    agc_trace_i->setMaximumWidth(100);
    agc_trace_i->setMaximumHeight(50);
    agc_trace_i->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget1_layout->addWidget(agc_trace_i);


    QPushButton* AGC_save = new QPushButton("AGC_save");
    AGC_save->setStyleSheet(style1.button_save_style1);
    AGC_save->setMaximumSize(200, 50);
    page2_widget1_layout->addWidget(AGC_save);

    ///page2_widget2
    QPushButton* button_filter = new QPushButton("filter");
    page2_widget2_layout->addWidget(button_filter);
    button_filter->setMaximumSize(200, 50);
    button_filter->setStyleSheet(style1.button_save_style1);

    QPushButton* button_chart2 = new QPushButton("audio imput");
    page2_widget2_layout->addWidget(button_chart2);
    button_chart2->setMaximumSize(200, 50);
    button_chart2->setStyleSheet(style1.button_save_style1);

    QPushButton* button_polarchart = new QPushButton("polarchart");
    page2_widget2_layout->addWidget(button_polarchart);
    button_polarchart->setMaximumSize(200, 50);
    button_polarchart->setStyleSheet(style1.button_save_style1);

    QPushButton* button_polarchart2 = new QPushButton("polarchart2");
    page2_widget2_layout->addWidget(button_polarchart2);
    button_polarchart2->setMaximumSize(200, 50);
    button_polarchart2->setStyleSheet(style1.button_save_style1);
    //slot

    connect(button_filter, SIGNAL(clicked()), this, SLOT(drawcurve()));

    connect(button_chart2, SIGNAL(clicked()), this, SLOT(drawcurve2()));

    connect(button_polarchart, SIGNAL(clicked()), this, SLOT(PolarChart()));
    connect(button_polarchart2, SIGNAL(clicked()), this, SLOT(PolarChart2()));


    ///page2_widget3
    QPushButton* button_fft = new QPushButton("FFT_1d");
    page2_widget3_layout->addWidget(button_fft);
    button_fft->setMaximumSize(200, 50);
    button_fft->setStyleSheet(style1.button_save_style1);

    QPushButton* button_fft_2d = new QPushButton("FFT_2d");
    page2_widget3_layout->addWidget(button_fft_2d);
    button_fft_2d->setMaximumSize(200, 50);
    button_fft_2d->setStyleSheet(style1.button_save_style1);

    QLabel* label_sample_rate = new QLabel("sample_rate");///�ָ��ǩ
    label_sample_rate->setMaximumSize(100, 50);
    label_sample_rate->setStyleSheet("background-color:lightgreen");
    page2_widget3_layout->addWidget(label_sample_rate);

    fft_sample_rate = new QDoubleSpinBox();//����fft_sample_rate��ֵ
    fft_sample_rate->setToolTip("<html><font size='5' color='lightgreen'>set sample rate!</font></html>");
    //fft_sample_rate->setMinimum(1);
    //fft_sample_rate->setValue(500);
    /*fft_sample_rate->setMaximum(1000);*/
    fft_sample_rate->setMaximumWidth(200);
    fft_sample_rate->setMaximumHeight(50);
    fft_sample_rate->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget3_layout->addWidget(fft_sample_rate);

    QLabel* label_tracei2 = new QLabel("trace i");///�ָ��ǩ
    label_tracei2->setMaximumSize(100, 50);
    label_tracei2->setStyleSheet("background-color:lightgreen");
    page2_widget3_layout->addWidget(label_tracei2);

    data_trace_i = new QSpinBox();//����data_trace_i��ֵ
    data_trace_i->setToolTip("<html><font size='5' color='lightgreen'>set data_trace_i !</font></html>");
    /*data_trace_i->setMinimum(0);*/
    /*data_trace_i->setValue(500);*/
    data_trace_i->setMaximumWidth(200);
    data_trace_i->setMaximumHeight(50);
    data_trace_i->setStyleSheet("background-color:rgb(200,200,200)");
    page2_widget3_layout->addWidget(data_trace_i);

    QPushButton* button_fft_show = new QPushButton("FFT_show");
    page2_widget3_layout->addWidget(button_fft_show);
    button_fft_show->setMaximumSize(200, 50);
    button_fft_show->setStyleSheet(style1.button_save_style1);
    ///page2_widget4
    QPushButton* button_STFT = new QPushButton("STFT");
    page2_widget4_layout->addWidget(button_STFT);
    button_STFT->setMaximumSize(200, 50);
    button_STFT->setStyleSheet(style1.button_save_style1);

    ///function connect
    connect(button_AGC, SIGNAL(clicked()), this, SLOT(dataArrayAGC()));
    connect(AGC_save, SIGNAL(clicked()), this, SLOT(save_AGC_segy()));
    connect(AGC_single, SIGNAL(clicked()), this, SLOT(trace_i_agc()));
    ///fft1
    connect(button_fft, SIGNAL(clicked()), this, SLOT(opencv_fft_1d()));//һά����Ҷ�任
    connect(button_fft_2d, SIGNAL(clicked()), this, SLOT(opencv_fft2d()));//һά����Ҷ�任
    connect(button_fft_show, SIGNAL(clicked()), this, SLOT(chart_fftshow()));
    ///SF_function
    connect(button_STFT, SIGNAL(clicked()), this, SLOT(SF_function()));

    ///page3��ʾ���
    QVBoxLayout* page3_layout = new QVBoxLayout(page3);
    QPushButton* tableWidget = new QPushButton("table");
    
    tableWidget->setMaximumSize(200, 50);
    tableWidget->setStyleSheet(style1.button_main);
    page3_layout->addWidget(tableWidget);
    //page3��ʾwiggle
    QPushButton* wiggle_button_H = new QPushButton("Wiggle_H");
    wiggle_button_H->setMaximumSize(200, 50);
    wiggle_button_H->setStyleSheet(style1.button_main);
    page3_layout->addWidget(wiggle_button_H);
    QPushButton* wiggle_button_V = new QPushButton("Wiggle_V");
    wiggle_button_V->setMaximumSize(200, 50);
    wiggle_button_V->setStyleSheet(style1.button_main);
    page3_layout->addWidget(wiggle_button_V);
    //page3eiggle����
    QPushButton* Save_Wiggle = new QPushButton("Save_Wiggle");
    Save_Wiggle->setMaximumSize(200, 50);
    Save_Wiggle->setStyleSheet(style1.button_main);
    page3_layout->addWidget(Save_Wiggle);
    ///page3   @slot
    connect(tableWidget, SIGNAL(clicked()), this, SLOT(matrix_table_show()));
    connect(wiggle_button_H, SIGNAL(clicked()), this, SLOT(WiggleView_show_H()));
    connect(wiggle_button_V, SIGNAL(clicked()), this, SLOT(WiggleView_show_V()));
    connect(Save_Wiggle, SIGNAL(clicked()), this, SLOT(saveWiggle_1()));
    
    //page4��ʾ3D
    QVBoxLayout* page4_layout = new QVBoxLayout(page4);

    QPushButton* data_3d_but1 = new QPushButton("3D");
    data_3d_but1->setStyleSheet(style1.button_main);
    page4_layout->addWidget(data_3d_but1);
    //slot
    connect(data_3d_but1, SIGNAL(clicked()), this, SLOT(draw3DData()));

}
Qt_segy_process::~Qt_segy_process()
{}
void Qt_segy_process::on_stackpage1_change_clicked()//��ť����л�����һҳ�ۺ�������
{
    stackedWidget1->setCurrentIndex(0);
    ui.statusBar->showMessage(" Page1-->", 5000);
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
}
void Qt_segy_process::on_stackpage2_change_clicked()//��ť����л����ڶ�ҳ�ۺ�������
{
    stackedWidget1->setCurrentIndex(1);
    ui.statusBar->showMessage("Page2-->: ", 5000);
    stylesheet_QT style2;
    ui.statusBar->setStyleSheet(style2.styleSheet_bar);
}
void Qt_segy_process::on_stackpage3_change_clicked()//��ť����л�������ҳ�ۺ�������
{
    stackedWidget1->setCurrentIndex(2);
    ui.statusBar->showMessage("Page3-->", 5000);
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);


}
void Qt_segy_process::on_stackpage4_change_clicked()//��ť����л�������ҳ�ۺ�������
{
    stackedWidget1->setCurrentIndex(3);
    ui.statusBar->showMessage("Page4-->", 5000);
    stylesheet_QT style3;
    ui.statusBar->setStyleSheet(style3.styleSheet_bar);
}
void Qt_segy_process::on_stackpage5_change_clicked()//��ť����л�������ҳ�ۺ�������
{
    stackedWidget1->setCurrentIndex(4);
    ui.statusBar->showMessage("Page4-->", 5000);
    stylesheet_QT style3;
    ui.statusBar->setStyleSheet(style3.styleSheet_bar);
}
//SEISMIC-SEGY����part//open
void Qt_segy_process::open_segy() {
    qDebug() << "input data!";
    ui.statusBar->showMessage(tr("Loading data!"), 5000);
    //QString OpenFile;
    OpenFile_segy = QFileDialog::getOpenFileName(this,//openfile�д洢����ͼƬ��ַ;
        "please choose a file",
        "",
        "data Files(*.segy *.png *.sgy );;All(*.*)");

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";
        return;
    }
    ui.statusBar->showMessage(tr("Loading complet!"), 2000);
    ui.statusBar->showMessage(QString("disk location:%1").arg(OpenFile_segy), 3000);
    stylesheet_QT style2;
    ui.statusBar->setStyleSheet(style2.styleSheet_bar);
}
//show,�Ȼ�ȡ
void Qt_segy_process::show_segy() {

    std::string filePath = OpenFile_segy.toStdString();//get file_path

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";

        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);

    dataArray_real = dataArray;//�洢real_value
    dataArray = normalized(dataArray);
    dataArray = transposeMatrix(dataArray);
    // ����һ�� OpenCV �� Mat ���󲢽� dataArray ���ݸ��Ƶ�����
    //cv::Mat image(dataArray.size(), dataArray[0].size(), CV_8U);//��ȡ����ά������к��У�

    //for (int i = 0; i < dataArray.size(); ++i) {
    //    for (int j = 0; j < dataArray[i].size(); ++j) {
    //        // ���� dataArray ��Ԫ���� [0, 1] ��Χ�ڵĸ�����
    //        image.at<uchar>(i, j) = dataArray[i][j] * 256;
    //    }
    //}
    // 
    // ����һ��α��ɫӳ��
    cv::Mat image = dataArray2image(dataArray);//���涨��һ��ת����������
    cv::Mat colorMap;
    applyColorMap(image, colorMap, cv::COLORMAP_OCEAN); // ʹ��Jet��ɫӳ�䣬�����ѡ������ӳ��
    /*COLORMAP_JET��Jet��ɫӳ�䣬���������α��ɫӳ��֮һ��ͨ�����ڱ�ʾ�ȶȡ�
        COLORMAP_RAINBOW���ʺ���ɫӳ�䣬���ڱ�ʾ�������ݵĲ�ͬ����
        COLORMAP_HOT��Hot��ɫӳ�䣬���ڱ�ʾ�ȶȣ�ͨ�������¶����ݡ�
        COLORMAP_COOL��Cool��ɫӳ�䣬���ڱ�ʾ�¶ȣ�ͨ�����䵽�ȵ��¶ȱ仯��
        COLORMAP_SPRING��Spring��ɫӳ�䣬���ڱ�ʾ�¶Ȼ��¶ȱ仯��
        COLORMAP_SUMMER��Summer��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
        COLORMAP_AUTUMN��Autumn��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
        COLORMAP_WINTER��Winter��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
        COLORMAP_OCEAN��Ocean��ɫӳ�䣬ͨ�����ڱ�ʾ�����ˮ����ȡ�
        COLORMAP_PINK��Pink��ɫӳ�䣬ͨ�����ڱ�ʾ�������ݵĲ�ͬ����
        COLORMAP_HOT��Jet��ɫӳ�䣬���������α��ɫӳ��֮һ��ͨ�����ڱ�ʾ�ȶ�*/
        // ��ʾͼ��
    //imshow("colormap", colorMap);
    //cv::namedWindow("Original", cv::WINDOW_NORMAL);
    //cv::imshow("Original", image); // ��ʾԭʼͼ��
    //cv::namedWindow("colorMap", cv::WINDOW_NORMAL);
    //cv::imshow("colorMap", colorMap); // ��ʾcolorMap
    //cv::namedWindow("Resized", cv::WINDOW_NORMAL);
    //cv::imshow("Resized", resized); // ��ʾ�������ͼ��

    float minValue = findMinMaxValue(dataArray_real, 0); // ������Сֵ
    float maxValue = findMinMaxValue(dataArray_real, 1); // �������ֵ

    QString message = QString("orignal data value in Min Value: %1,<-> Max Value: %2").arg(minValue).arg(maxValue);
    ui.statusBar->showMessage(message);
    //��ҳ����ʾ����
    src = image;
    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����
    /*textEdit1->setText("dataArray_real");*/
    textEdit1->append(tr("dataArray_real:trace simple:%1 ;trace number %2").arg(dataArray.size()).arg(dataArray[0].size()));
    textEdit1->append(tr("dataArray_real:minvalue:%1 ;maxvalue %2").arg(minValue).arg(maxValue));

    stackedWidget1->setCurrentIndex(0);//��ʾͼƬ�أ���ת����ҳ
    stylesheet_QT style2;
    ui.statusBar->setStyleSheet(style2.styleSheet_bar);
    
}
//save
void  Qt_segy_process::save_segy() {

    
    ui.statusBar->showMessage(tr("hello!"), 5000);
    if (dataArray_real.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;
    }
    std::ofstream fileout;
    QString SaveFile_segy = QFileDialog::getSaveFileName(this,//�Ի���õ��洢·��
        "Save data2d",
        "",
        "Data Files(*.txt*.csv);;All(*.*)");

    std::string filePath = SaveFile_segy.toStdString();//Qstring-->string

    fileout.open(filePath);  // Open the output file
    if (!fileout.is_open())
    {
        std::cout << "Can not open File " << filePath << std::endl;
        return;
    }

    dataArray_save = transposeMatrix(dataArray_real);

    // Write the 2D vector to the output file
    for (int i = 0; i < dataArray_save.size(); i++)
    {
        for (int j = 0; j < dataArray_save[i].size(); j++)
        {
            fileout << dataArray_save[i][j] << ",";
        }
        fileout << std::endl;
    }
    fileout.close();
    ui.statusBar->showMessage(tr("saved data successfully!"));
    int trace_number;
    int trace_length;

    trace_length = dataArray_save.size();
    trace_number = dataArray_save[1].size();
    QString message = QString("trace_number: %1, trace_length: %2").arg(trace_number).arg(trace_length);
    ui.statusBar->showMessage(message);

}
//�洢���ݵ�ͼƬ
void Qt_segy_process::save_segy_picture() {

    std::string filePath = OpenFile_segy.toStdString();//get file_path

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";

        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);

    dataArray_real = dataArray;//�洢real_value
    dataArray = normalized(dataArray);
    dataArray = transposeMatrix(dataArray);
    // ����һ�� OpenCV �� Mat ���󲢽� dataArray ���ݸ��Ƶ�����
    Mat image(dataArray.size(), dataArray[0].size(), CV_8U);//��ȡ����ά������к��У�

    for (int i = 0; i < dataArray.size(); ++i) {
        for (int j = 0; j < dataArray[i].size(); ++j) {
            // ���� dataArray ��Ԫ���� [0, 1] ��Χ�ڵĸ�����
            image.at<uchar>(i, j) = dataArray[i][j] * 256;
        }
    }
    //����ת��ΪCV_8U��ʽ��
    if (image.empty()) {
        qDebug() << "image_DFT is empty. Make sure to load an image and erosion first!";
        ui.statusBar->showMessage(tr("image_DFT is empty. Make sure to load an image and erosion first!"), 3000);
        return;
    }

    QString saveFilePath = QFileDialog::getSaveFileName(this,
        "Save image_DFT",
        "",
        "Image Files(*.jpg *.png *.bmp);;All(*.*)");

    if (!saveFilePath.isEmpty()) {
        try {
            bool success = imwrite(saveFilePath.toStdString(), image);
            if (success) {
                qDebug() << "image_DFT saved to: " << saveFilePath;
                ui.statusBar->showMessage(tr("erosion image saved successfully!"), 3000);
            }
            else {
                qDebug() << "Failed to save the image_DFT!";
                ui.statusBar->showMessage(tr("Failed to save the erosion image!"), 3000);
            }
        }
        catch (cv::Exception& e) {
            qDebug() << "Error while saving the image_DFT: " << e.what();
            ui.statusBar->showMessage(tr("Error while saving the image_DFT."), 3000);
        }
    }
}
//���ļ��ж�ȡ��������
std::vector<std::vector<float>>  Qt_segy_process::getsegyarray(const std::string& inputfile) {

    std::ifstream filein;


    //std::string inputfile, outputfile;
    //inputfile = "D:\\Code\\visual_code\\Readsegy\\Readsegy\\data\\viking_new.segy";  // Input file path
    filein.open(inputfile, std::ios::binary);  // Open the input file
    if (!filein.is_open())
    {
        std::cout << "Can not open File " << inputfile << std::endl;
    }
    char f3200[3200];
    short int f400[200];

    filein.read(f3200, 3200);  // Read the first 3200 bytes of file header
    filein.read(reinterpret_cast<char*>(f400), 400);  // Read the next 400 bytes of file header

    short svalue;
    svalue = ((f400[10] & 0xff00) >> 8) | ((f400[10] & 0x00ff) << 8);  // Read trace length
    int trace_length = svalue;

    filein.seekg(0, std::ios::end);
    long len = filein.tellg();  // File length
    int traces = (len - 3600) / (240 + 4 * static_cast<long>(trace_length));  // Calculate number of traces

    std::cout << "len = " << len << "\t traces = " << traces << ", trace_length = " << trace_length << std::endl;

    filein.seekg(3600, std::ios::beg);
    char* header = new char[240];
    int* data = new int[trace_length];
    int sizeofTraceData = 4 * trace_length;
    int sizeofTraceHeader = 240;
    int qw1 = 0;

    // Create a 2D vector to store the data
    std::vector<std::vector<float>> dataArray(traces, std::vector<float>(trace_length));


    for (int i = 0; i < traces; i++)
    {
        if (i % 10000 == 0)
        {
            std::cout << i << std::endl;
        }
        filein.read(header, sizeofTraceHeader);  // Read trace header
        filein.read(reinterpret_cast<char*>(data), sizeofTraceData);  // Read trace data
        //���������ѭ����д�����ļ���ͷ����
        for (int j = 0; j < trace_length; j++)
        {
            qw1 = swap4byte(data[j]);
            dataArray[i][j] = ibm2float(qw1);  // Store data in the 2D vector
        }
    }
    delete[] header;
    filein.close();
    return dataArray;
}
//��������ת������
float Qt_segy_process::ibm2float(int x)
{
    int sign, expo, mantissa, res;
    float result, mant;
    if (x) {
        sign = x >> 31 & 0x01; // Calculate the sign bit 's'
        expo = x >> 24 & 0x7f; // Calculate the exponent 'e'
        mantissa = x & 0x00ffffff; // Calculate the mantissa 'f'

        if (expo == 127 && (mantissa & 0x00800000) && !(mantissa & 0x007fffff)) {  // Check for NaN
            res = (sign << 31) | 0x7f800001;
            memcpy(&result, &res, sizeof(float));
            return result;
        }

        if (expo > 96) {  // Check for infinity
            res = (sign << 31) | 0x7f800000;
            memcpy(&result, &res, sizeof(float));
        }
        else if (expo < 32)
            result = 0;  // Check for zero
        else {
            expo = expo - 64;  // Offset the exponent to e-64
            mant = static_cast<float>(mantissa) / std::pow(2, 24);  // Convert to decimal fraction 0.f
            result = (1 - 2 * sign) * mant * std::pow(16, expo);  // Calculate the decimal value using equation (2)
        }
        return result;  // Return the result
    }
    result = x;  // When x = 0, return 0
    return result;
}
//���ݸߵ�λת��
int Qt_segy_process::swap4byte(int value)
{
    int svalue;
    svalue = ((value & 0xff000000) >> 24) | ((value & 0x00ff0000) >> 8) |
        ((value & 0x0000ff00) << 8) | ((value & 0x000000ff) << 24);
    return svalue;
}
//���ݹ�һ��
std::vector<std::vector<float>> Qt_segy_process::normalized(std::vector<std::vector<float>> matrix) {

    // ���� 1: �ҵ���Сֵ�����ֵ
    float minValue = matrix[0][0];
    float maxValue = matrix[0][0];

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] < minValue)
                minValue = matrix[i][j];
            if (matrix[i][j] > maxValue)
                maxValue = matrix[i][j];
        }
    }

    // ���� 2: ��һ������
    float newMin = 0.0f;  // �µ���Сֵ
    float newMax = 1.0f;  // �µ����ֵ

    // �ȶ����ݽ��б�׼��
    //float meanValue = calculateMean(dataArray);
    //float stdDev = calculateStdDev(dataArray);

    //for (int i = 0; i < dataArray.size(); ++i) {
    //    for (int j = 0; j < dataArray[i].size(); ++j) {
    //        dataArray[i][j] = (dataArray[i][j] - meanValue) / stdDev;
    //    }
    //}
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            float dataValue = matrix[i][j];
            float normalizedValue = (dataValue - minValue) / (maxValue - minValue) * (newMax - newMin) + newMin;
            matrix[i][j] = normalizedValue;
        }
    }
    return  matrix;
}
//���ݱ�׼��
std::vector<std::vector<float>> Qt_segy_process::normalizeColumns(std::vector<std::vector<float>> matrix) {

    int rows = matrix.size();
    int cols = matrix[0].size();

    // ��ÿһ�н��б�׼��
    for (int j = 0; j < cols; ++j) {
        // �����е�ƽ��ֵ
        float mean = std::accumulate(matrix.begin(), matrix.end(), 0.0, [j](float sum, const std::vector<float>& row) {
            return sum + row[j];
            }) / rows;

        // �����еı�׼��
        float sum_squared_diff = 0.0;
        for (int i = 0; i < rows; ++i) {
            sum_squared_diff += std::pow(matrix[i][j] - mean, 2);
        }
        float std_dev = std::sqrt(sum_squared_diff / rows);

        // ���н��б�׼��
        for (int i = 0; i < rows; ++i) {
            matrix[i][j] = (matrix[i][j] - mean) / std_dev;
        }
    }

    return matrix; // ���ر�׼����ľ���
}
// ����һ�����������о���ת��
std::vector<std::vector<float>> Qt_segy_process::transposeMatrix(std::vector<std::vector<float>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<float>> transposed(cols, vector<float>(rows)); // ����һ���µľ������ڴ洢ת�ý��

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j]; // ����ת�ò���
        }
    }

    return transposed;
}
// ����������Сֵ�����ֵ
float  Qt_segy_process::findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag) {
    if (matrix.empty() || matrix[0].empty()) {
        std::cerr << "����Ϊ�գ��޷��ҵ���С�����ֵ��" << std::endl;
        return 0.0; // ����Ĭ��ֵ
    }

    float result = matrix[0][0];

    for (const std::vector<float>& row : matrix) {
        for (float value : row) {
            if (flag == 0) { // ������Сֵ
                if (value < result) {
                    result = value;
                }
            }
            else if (flag == 1) { // �������ֵ
                if (value > result) {
                    result = value;
                }
            }
            else {
                std::cerr << "��Ч�ı�־ֵ��ӦΪ0��1��" << std::endl;
                return 0.0; // ����Ĭ��ֵ
            }
        }
    }

    return result;
}
//dataarray2image
cv::Mat Qt_segy_process::dataArray2image(std::vector<std::vector<float>> dataArray) {
    cv::Mat image_temp(dataArray.size(), dataArray[0].size(), CV_8U);//��ȡ����ά������к��У�

    for (int i = 0; i < dataArray.size(); ++i) {
        for (int j = 0; j < dataArray[i].size(); ++j) {
            // ���� dataArray ��Ԫ���� [0, 1] ��Χ�ڵĸ�����
            image_temp.at<uchar>(i, j) = dataArray[i][j] * 256;
        }
    }
    return image_temp;
    ui.statusBar->showMessage(tr("dataarray2image complete!"), 3000);
}
// ��������Function to calculate the root mean square (RMS) of a vector
float Qt_segy_process::calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize) {
    float sum = 0.0f;
    for (int i = std::max(0, row - windowSize / 2); i < std::min(static_cast<int>(data.size()), row + windowSize / 2 + 1); ++i) {
        for (int j = std::max(0, col - windowSize / 2); j < std::min(static_cast<int>(data[0].size()), col + windowSize / 2 + 1); ++j) {
            sum += data[i][j] * data[i][j];
        }
    }
    return std::sqrt(sum / (windowSize * windowSize));
}
//AGC//agc2d,�������ڼ�������
void Qt_segy_process::dataArrayAGC() {//����Ӧ�������
    ///�ж� 
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    //std::vector<std::vector<float>>& data, int windowSize, float k
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);
    ///������ֵ
    if (dataarray_agc.empty()){
        return ;
    }

    windows_size_value->setMinimum(1);
    //windows_size_value->setValue(dataarray_agc.size() / 2) ;
    windows_size_value->setMaximum(dataarray_agc.size());
    //int windowSize = 3; 
    int window_size = windows_size_value->value();//�趨�������ڵĴ�С
    ///�ж�
    if (dataarray_agc.empty()) {

        QString message = QString("empty!");
        ui.statusBar->showMessage(message);
        ui.statusBar->setStyleSheet("color:red;font-size=20px;");
        return ;
    }
    
    /////�ж����ֵ��Сֵ�Ƿ�С��1
    //float minValue = findMinMaxValue(dataarray_agc, 0);
    //float maxValue = findMinMaxValue(dataarray_agc, 1);//��ȡ

    //if (minValue >-1 || maxValue <1)
    //{
    //    for (int i = 0; i < dataarray_agc.size(); ++i) {
    //        for (int j = 0; j < dataarray_agc[i].size(); ++j) {
    //            dataarray_agc[i][j] = dataarray_agc[i][j] / abs(minValue);
    //        }
    //    }
    //}
    //dataarray_agc = Exc_min(dataarray_agc);///�г���Сֵ

std::vector<std::vector<float>> agc_result;

int num_traces = dataarray_agc[0].size();//��ȡ���� 
 ///start****************************************
for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//���ݵ����ļ����������ά����
    
    vector<float> data;//�洢�������ݿռ�
    data.reserve(dataarray_agc.size());
    for (int i = 0; i < dataarray_agc.size(); i++) {//��ȡָ��i�ĵ�������

        data.push_back(dataarray_agc[i][data_tracei]);//�õ�һά����data
    }
    // �������ݵ�ƽ��
    std::vector<float> squared_data;
    squared_data.reserve(data.size());
    for (const auto& value : data) {
        if (std::pow(value, 2)< 1e-30) {

            squared_data.push_back(std::pow(value, 2) + 1e-30);
        }
        else {
            squared_data.push_back(std::pow(value, 2) );
        }
        //����ֵ��ƽ����С����С��
    }
    // ʹ�û������ڼ���ÿ�������ڵ�ƽ������
    std::vector<float> sliding_mean(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = std::max(0, i - window_size / 2); j <= std::min(static_cast<int>(data.size()) - 1, i + window_size / 2); ++j) {
            sliding_mean[i] += squared_data[j];
        }
        sliding_mean[i] /= window_size;
    }
    std::vector<float> agc_data(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        agc_data[i] = data[i] / std::sqrt(sliding_mean[i]);
    }
    //const float threshold = 1e-6; /// ����һ����ֵ������ʵ���������
    //// agc���ţ����ݣ���ǰ����������С����
    //for (int i = 0; i < data.size(); ++i) {
    //    // ���������Ƿ�С����ֵ
    //    if (std::abs(data[i] / std::sqrt(sliding_mean[i])) < threshold) {
    //        agc_data[i] = 0.0; // �滻Ϊ��
    //    }
    //    else {
    //        agc_data[i] = data[i] / std::sqrt(sliding_mean[i]);
    //    }
    //}
    // Store the result for this trace
    agc_result.push_back(agc_data);//�������ķ�����ˣ���Ҫ���ȥ
}
///end****************************************
    std::vector<std::vector<float>> temp;
    agc_result = transposeMatrix(agc_result);//ת��

    temp = agc_result;//������������,���ݴ洢��
    agc_save_data = agc_result;
    //agc_save_data = temp;

    //temp = normalizeColumns(temp);
    temp = normalized(temp);//�����һ����ģ�����ݳ������⣬��Ҫ�Ľ���
    src= dataArray2image(temp);

    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));

    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // ��ʾcolorMap
    QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
    ui.statusBar->showMessage(message, 10000);//��ʾ10��

    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����

}
///��������agc
void Qt_segy_process::trace_i_agc() {

    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);//�����ڲ�

    if (dataarray_agc.empty()) {
        return;
    }
    vector<float> data;//�洢�������ݿռ�

    agc_trace_i->setMaximum(dataarray_agc[0].size());//����������

    windows_size_value->setMinimum(1);//���ô�����Сֵ
    //windows_size_value->setValue(dataarray_agc.size() / 2);
    windows_size_value->setMaximum(dataarray_agc.size());//������󴰿ڳ���

    int data_tracei = agc_trace_i->value();

    int window_size = windows_size_value->value();//�趨�������ڵĴ�С
    //int data_tracei = data_trace_i->value();
    ///��ʼ
    //const float threshold = 1e-6; /// ����һ����ֵ����ֹ���ݹ�С
    //// agc���ţ����ݣ���ǰ����������С����
    //for (int i = 0; i < dataarray_agc.size(); ++i) {
    //    for(int j = 0; j < dataarray_agc.size(); ++j){
    //            if (dataarray_agc[i][j] < threshold) {
    //                dataarray_agc[i][j] = 0.0; // �滻Ϊ��
    //            }
    //    }

    //}
    for (int i = 0; i < dataarray_agc.size(); i++) {//��ȡָ��i�ĵ�������

        data.push_back(dataarray_agc[i][data_tracei]);//�õ�һά����data
    }
    // �������ݵ�ƽ��
    std::vector<float> squared_data;
    squared_data.reserve(data.size());
    for (const auto& value : data) {
        if (std::pow(value, 2) < 1e-30) {

            squared_data.push_back(std::pow(value, 2) + 1e-30);///���ϼ�Сֵ����ֹ���ݶ�ʧ
        }
        else {
            squared_data.push_back(std::pow(value, 2));
        }
        //����ֵ��ƽ����С����С��
    }
    // ʹ�û������ڼ���ÿ�������ڵ�ƽ������
    std::vector<float> sliding_mean(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = std::max(0, i - window_size / 2); j <= std::min(static_cast<int>(data.size()) - 1, i + window_size / 2); ++j) {
            sliding_mean[i] += squared_data[j];
        }
        sliding_mean[i] /= window_size;
    }
    // agc���ţ����ݣ���ǰ����������С����
    std::vector<float> agc_data(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        agc_data[i] = data[i] / std::sqrt(sliding_mean[i]);
    }
    
    //������ʾ����
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();

    // �� std::vector<float> �е�������ӵ� QSplineSeries ��
    for (int i = 0; i < agc_data.size(); ++i) {
        series->append(i, agc_data[i]);
    }
    chart->addSeries(series);

    // ����������
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // �����������ǩ
    axisX->setTitleText("sample number");
    axisY->setTitleText("orignal_Ampli");

    QFont font;
    font.setPointSize(20);  // ���������С
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // ����������ӵ� QChart ��
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ��ϵ�й�����������
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();
    QString title0 = QString("agc_data%1  trace").arg(agc_trace_i->value());
    chart->setTitle(title0);
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);

    ChartView_widget->show();

    QChartView* ChartView_widget2 = new QChartView();
    QChart* chart2 = new QChart();
    QSplineSeries* series2 = new QSplineSeries();

    // �� std::vector<float> �е�������ӵ� QSplineSeries ��
    for (size_t i = 0; i < data.size(); ++i) {
        series2->append(i, data[i]);
    }
    chart2->addSeries(series2);

    // ����������
    QValueAxis* axisX1 = new QValueAxis;
    QValueAxis* axisY1 = new QValueAxis;

    // �����������ǩ
    axisX1->setTitleText("sample number");
    axisY1->setTitleText("after_agc_Ampli");


    font.setPointSize(20);  // ���������С
    axisX1->setTitleFont(font);
    axisY1->setTitleFont(font);

    // ����������ӵ� QChart ��
    chart2->addAxis(axisX1, Qt::AlignBottom);
    chart2->addAxis(axisY1, Qt::AlignLeft);

    // ��ϵ�й�����������
    series2->attachAxis(axisX1);
    series2->attachAxis(axisY1);

    chart2->legend()->hide();
    QString title1 = QString("orignal data:number   %1  trace").arg(agc_trace_i->value());
    chart2->setTitle(title1);
    chart2->setTitleFont(font);
    //chart->createDefaultAxes();
    chart2->setTheme(QChart::ChartThemeLight);
    ChartView_widget2->setChart(chart2);

    ChartView_widget2->show();

}
///agc����
void  Qt_segy_process::save_AGC_segy() {
    /// Write the 2D vector to the output file
    std::ofstream fileout;
    QString SaveFile_segy = QFileDialog::getSaveFileName(this,//�Ի���õ��洢·��
        "Save data2d",
        "",
        "Data Files(*.txt*.csv);;All(*.*)");

    std::string filePath = SaveFile_segy.toStdString();//Qstring-->string

    fileout.open(filePath);  // Open the output file
    if (!fileout.is_open())
    {
        std::cout << "Can not open File " << filePath << std::endl;
        return;
    }

    dataArray_save = agc_save_data;//����Ҫ�洢�����ݴ���
    if (dataArray_save.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;
    }

    // Write the 2D vector to the output file
    for (int i = 0; i < dataArray_save.size(); i++)
    {
        for (int j = 0; j < dataArray_save[i].size(); j++)
        {
            fileout << dataArray_save[i][j] << ",";
        }
        fileout << std::endl;
    }
    fileout.close();
    ui.statusBar->showMessage(tr("saved AGC data successfully!"));
}
///�г���Сֵ����ֹ���ݳ�����Χ
std::vector<std::vector<float>> Qt_segy_process::Exc_min(std::vector<std::vector<float>> matrix) 
{
    float cut_min = 1e-5;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)

            if (matrix[i][j] < cut_min && matrix[i][j]>-cut_min) {

                matrix[i][j] = 0;
            }
            /*else {
                matrix[i][j] = matrix[i][j];
            }*/
    }
    return  matrix;
}
//����һά���ݵ�Ƶ��
void Qt_segy_process::opencv_fft_1d() {

    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    vector<float> data;//�洢�������ݿռ�

    float sampling = fft_sample_rate->value();
    fft_sample_rate->setMaximum(100000);
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//ȡ��Ҫ�����segy����

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());

    int data_tracei = data_trace_i->value();
    for (int i = 0; i < dataarray_fft.size(); i++) {//��ȡָ��i�ĵ�������

        data.push_back(dataarray_fft[i][data_tracei]);
    }

    cv::Mat Data = cv::Mat(data);//����ת��Ϊmat��ʽ
    cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
    cv::Mat planes_true1 = cv::Mat_<float>(Data);
    cv::Mat Y1;
    merge(planes1, 2, Y1);
    dft(Y1, Y1);//����Ҷ�任���Ϊ����.ͨ��1�����ʵ��, ͨ��2������鲿
    split(Y1, planes1); // plannes[0]=Re(DFT(I))��ʵ��,plannes[1]=Im(DFT(I))���鲿
    std::vector<float> amplite_Re;
    amplite_Re = planes1[0];//cv::MatתΪvector
    std::vector<float> amplite_Im;
    amplite_Im = planes1[1];

    std::vector<float>Ampli; //����Ƶ�ʷ���ֵ
    std::vector<float>Freq; //�����ӦƵ��ֵ
    int L_freq = floor(data.size() / 2);
    for (int k = 1; k < L_freq + 1; k++)
    {
        float ampli = sqrt(pow(amplite_Re[k-1], 2) + pow(amplite_Im[k-1], 2)) / L_freq;
        Ampli.push_back(ampli);//FFT��ֵ

        float freq = ((float)sampling) / data.size() * k;
        Freq.push_back(freq);//Ƶ��ֵ
    }

    QString message = QString("vector fft completed!");
    ui.statusBar->showMessage(message);

    /*QString message2 = QString("data %1").arg(Freq[5]);
    ui.statusBar->showMessage(message2);*/
    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();

    // �� std::vector<float> �е�������ӵ� QSplineSeries ��
    for (size_t i = 0; i < Freq.size(); ++i) {
        series->append(Freq[i],Ampli[i]);
    }
    chart->addSeries(series);

    // ����������
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // �����������ǩ
    axisX->setTitleText("Freq");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // ���������С
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // ����������ӵ� QChart ��
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ��ϵ�й�����������
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();

    QString title1 = QString("opencv_fft:number   %1  trace").arg(data_tracei);
    
    chart->setTitle(title1);
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);

    ChartView_widget->show();
}
//�����ά���ݵ�Ƶ�ײ���ʾ
void Qt_segy_process::opencv_fft2d() {
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    fft_sample_rate->setMaximum(100000);//�����ڲ����ò��������ֵ
    float sampling = fft_sample_rate->value();
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//ȡ��Ҫ�����segy����

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());//����������
    std::vector<std::vector<float>> fft_result_freq;//�洢Ƶ��
    std::vector<std::vector<float>> fft_result_amp;//�洢Ƶ�ʶ�Ӧ�ķ�ֵ
    int num_traces = dataarray_fft[0].size();//��ȡ���� 
    ///��ʼ������
    
    for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//���ݵ����ļ����������ά����

        std::vector<float> amplite_Re;
        std::vector<float> amplite_Im;
        std::vector<float>Ampli; //����Ƶ�ʷ���ֵ
        std::vector<float>Freq; //�����ӦƵ��ֵ
        vector<float> data;//�洢�������ݿռ�//����ѭ����ߣ�push_back��һά���ں��棬�����⣬����ѭ��������и��£�
        data.reserve(dataarray_fft.size());

        for (int i = 0; i < dataarray_fft.size(); i++) {//��ȡָ��i�ĵ�������

            data.push_back(dataarray_fft[i][data_tracei]);
        }
        
        cv::Mat Data = cv::Mat(data);//����ת��Ϊmat��ʽ
        cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
        cv::Mat planes_true1 = cv::Mat_<float>(Data);
        cv::Mat Y1;
        merge(planes1, 2, Y1);
        dft(Y1, Y1);//����Ҷ�任���Ϊ����.ͨ��1�����ʵ��, ͨ��2������鲿
        split(Y1, planes1); // plannes[0]=Re(DFT(I))��ʵ��,plannes[1]=Im(DFT(I))���鲿

        amplite_Re = planes1[0];//cv::MatתΪvector
        amplite_Im = planes1[1];
       
        int L_freq = floor(data.size() / 2);
        for (int k = 1; k < L_freq + 1; k++)
        {
            float ampli = sqrt(pow(amplite_Re[k-1], 2) + pow(amplite_Im[k-1], 2)) / L_freq;
            Ampli.push_back(ampli);//FFT��ֵ

            float freq = ((float)sampling) / data.size() * k;
            Freq.push_back(freq);//һάƵ��ֵ
        }
        // Store the result for this trace
        fft_result_freq.push_back(Freq);//�������ķ�����ˣ���Ҫ���ȥ
        fft_result_amp.push_back(Ampli);
    }


    fft_result_freq = transposeMatrix(fft_result_freq);//���������������ʾ��
    fft_result_amp = transposeMatrix(fft_result_amp);

    fft_result_freq = normalized(fft_result_freq);
    fft_result_amp = normalized(fft_result_amp);

    Mat show_image_freq(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//����mat���飻
    Mat show_image_amp(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//����mat����

    show_image_freq = dataArray2image(fft_result_freq);
    show_image_amp = dataArray2image(fft_result_amp);

    cv::namedWindow("fft2d_freq", cv::WINDOW_NORMAL);
    cv::imshow("fft2d_freq", show_image_freq); // ��ʾcolorMap

    cv::namedWindow("fft2d_amp", cv::WINDOW_NORMAL);
    cv::imshow("fft2d_amp", show_image_amp); // ��ʾcolorMap
    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����


    QString message = QString("image completed! row %1 ;clo %2;").arg(fft_result_freq.size()).arg(fft_result_freq[0].size());
    ui.statusBar->showMessage(message);

    ///������ʾ
    //QChartView* ChartView_widget = new QChartView();
    //QChart* chart = new QChart();
    //QSplineSeries* series = new QSplineSeries();

    //for (size_t i = 0; i < fft_result_freq.size(); ++i) {
    //    series->append(i, fft_result_freq[i][3]);   
    //}
    //chart->addSeries(series);
    //ChartView_widget->setChart(chart);
    //ChartView_widget->show();
    ///ȡ��Qchart��ʾ

    /*QString message2 = QString("data %1").arg(Freq[5]);
    ui.statusBar->showMessage(message2);*/
    /////QChartView
    //QChartView* ChartView_widget = new QChartView();
    //QChart* chart = new QChart();
    //// �� std::vector<float> �е�������ӵ� QSplineSeries ��
    //QSplineSeries* series = new QSplineSeries();

    //for (size_t i = 0; i < fft_result_freq.size(); ++i) {
    //    
    //    for (size_t j = 0; j < fft_result_freq[0].size(); ++j) {

    //    series->append(fft_result_freq[i][j],fft_result_amp[i][j]);
    //    }
    //    
    //}
    //chart->addSeries(series);
    //// ����������
    //QValueAxis* axisX = new QValueAxis;
    //QValueAxis* axisY = new QValueAxis;

    //// �����������ǩ
    //axisX->setTitleText("Freq");
    //axisY->setTitleText("Ampli");

    //QFont font;
    //font.setPointSize(20);  // ���������С
    //axisX->setTitleFont(font);
    //axisY->setTitleFont(font);

    //// ����������ӵ� QChart ��
    //chart->addAxis(axisX, Qt::AlignBottom);
    //chart->addAxis(axisY, Qt::AlignLeft);

    //// ��ϵ�й�����������
    //series->attachAxis(axisX);
    //series->attachAxis(axisY);

    //chart->legend()->hide();
    //chart->setTitle("CV_algorithm_FFT_2d");
    //chart->setTitleFont(font);
    ////chart->createDefaultAxes();
    //chart->setTheme(QChart::ChartThemeLight);
    //ChartView_widget->setChart(chart);

    //ChartView_widget->show();

}
//�������е������Ƶ��chart��ʾ
void Qt_segy_process::chart_fftshow() {//���Ƴ�ÿһ�����ȽϺ�ʱ
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    fft_sample_rate->setMaximum(100000);//�����ڲ����ò��������ֵ
    float sampling = fft_sample_rate->value();
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//ȡ��Ҫ�����segy����

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());//����������
    std::vector<std::vector<float>> fft_result_freq;//�洢Ƶ��
    std::vector<std::vector<float>> fft_result_amp;//�洢Ƶ�ʶ�Ӧ�ķ�ֵ
    int num_traces = dataarray_fft[0].size();//��ȡ���� 
    ///��ʼ������
    for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//���ݵ����ļ����������ά����

        std::vector<float> amplite_Re;
        std::vector<float> amplite_Im;
        std::vector<float>Ampli; //����Ƶ�ʷ���ֵ
        std::vector<float>Freq; //�����ӦƵ��ֵ
        vector<float> data;//�洢�������ݿռ�//����ѭ����ߣ�push_back��һά���ں��棬�����⣬����ѭ��������и��£�
        data.reserve(dataarray_fft.size());

        for (int i = 0; i < dataarray_fft.size(); i++) {//��ȡָ��i�ĵ�������

            data.push_back(dataarray_fft[i][data_tracei]);
        }

        cv::Mat Data = cv::Mat(data);//����ת��Ϊmat��ʽ
        cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
        cv::Mat planes_true1 = cv::Mat_<float>(Data);
        cv::Mat Y1;
        merge(planes1, 2, Y1);
        dft(Y1, Y1);//����Ҷ�任���Ϊ����.ͨ��1�����ʵ��, ͨ��2������鲿
        split(Y1, planes1); // plannes[0]=Re(DFT(I))��ʵ��,plannes[1]=Im(DFT(I))���鲿

        amplite_Re = planes1[0];//cv::MatתΪvector
        amplite_Im = planes1[1];

        int L_freq = floor(data.size() / 2);
        for (int k = 1; k < L_freq + 1; k++)
        {
            float ampli = sqrt(pow(amplite_Re[k - 1], 2) + pow(amplite_Im[k - 1], 2)) / L_freq;
            Ampli.push_back(ampli);//FFT��ֵ

            float freq = ((float)sampling) / data.size() * k;
            Freq.push_back(freq);//һάƵ��ֵ
        }
        // Store the result for this trace
        fft_result_freq.push_back(Freq);//�������ķ�����ˣ���Ҫ���ȥ
        fft_result_amp.push_back(Ampli);
    }
    ///chart �����ʾ
    fft_result_freq = transposeMatrix(fft_result_freq);//���������������ʾ��
    fft_result_amp = transposeMatrix(fft_result_amp);

    //fft_result_freq = normalized(fft_result_freq);
    //fft_result_amp = normalized(fft_result_amp);

    //Mat show_image_freq(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//����mat���飻
    //Mat show_image_amp(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//����mat����

    //show_image_freq = dataArray2image(fft_result_freq);
    //show_image_amp = dataArray2image(fft_result_amp);

    //cv::namedWindow("fft2d_freq", cv::WINDOW_NORMAL);
    //cv::imshow("fft2d_freq", show_image_freq); // ��ʾcolorMap

    //cv::namedWindow("fft2d_amp", cv::WINDOW_NORMAL);
    //cv::imshow("fft2d_amp", show_image_amp); // ��ʾcolorMap
    //waitKey(0);
    //cv::destroyAllWindows(); // �ر�����OpenCV����
    QString message = QString("image completed! row %1 ;clo %2;").arg(fft_result_freq.size()).arg(fft_result_freq[0].size());
    ui.statusBar->showMessage(message);

    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    // �� std::vector<float> �е�������ӵ� QSplineSeries ��
    QSplineSeries* series = new QSplineSeries();

    for (size_t i = 0; i < fft_result_freq.size(); ++i) {

        for (size_t j = 0; j < fft_result_freq[0].size(); ++j) {

            series->append(fft_result_freq[i][j], fft_result_amp[i][j]);
        }

    }
    chart->addSeries(series);
    // ����������
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // �����������ǩ
    axisX->setTitleText("Freq");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // ���������С
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // ����������ӵ� QChart ��
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ��ϵ�й�����������
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();
    chart->setTitle("CV_algorithm_FFT_2d");
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);

    ChartView_widget->show();

}
//��ʾ���ݱ��
void Qt_segy_process::matrix_table_show() {

    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
    return;
    }
    ///��������
    std::vector<std::vector<float>> matrix = transposeMatrix(dataArray_real);///ԭʼ�����ǰ�����������row��ʾ��
    // ���� QTableWidget
    QTableWidget* tableWidget = new QTableWidget;
    tableWidget->setMinimumSize(600, 400);
    // ���ñ�������������
    tableWidget->setRowCount(matrix.size());
    tableWidget->setColumnCount(matrix[0].size());
    // ���������
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            tableWidget->setItem(row, col, item);
        }
    }
    // ��ʾ���
    tableWidget->show();
    /*QWidget* wid1 = new QWidget();
    wid1->setMinimumSize(600, 400);
    wid1->show();*/
}
//wiggle��ʾ��������horizontal direction
void Qt_segy_process::WiggleView_show_H() {

    ui.statusBar->setStyleSheet("background-color:orange");
    std::vector<std::vector<float>> matrix;
    if (dataArray_real.empty()) 
    {//���ж������Ƿ��ʼ��
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
    return;
    }
    matrix = dataArray_real;
    //matrix = normalized(matrix);
   /* std::vector<std::vector<float>> matrix = {
        {1.0, 2.0, 1.0, 2.0,3,4,5,6,7},
        {5.0, 6.0, 3.0, 8.0,4,6,7,6},
        {9.0, 10.0, 5.0, 8.0,3,5,6,7}
    };*/
    matrix = normalized(matrix);

    // ���� QGraphicsView �� QGraphicsScene
    QGraphicsView* wiggleView = new QGraphicsView();
    wiggleView->setWindowTitle("WiggleView_show_H");
    QGraphicsScene* scene = new QGraphicsScene();

    /*wiggleView->setFixedSize(matrix.size(), matrix[0].size());*/

// ���û�ͼ����
    int traceHeight = 20;//ÿ���ĸ߶�
    int traceSpacing = 10;//��֮����
    int sampleSpacing = 1;//������֮����
    // ���� Wiggle ͼ��ɫ
    QPen wigglePen;
    wigglePen.setColor(Qt::black);  // ������ɫΪ��ɫ
    wigglePen.setWidth(2);
    for (size_t i = 0; i < matrix.size(); ++i) {
        const std::vector<float>& trace = matrix[i];//ȡ��ÿһ��
        // ���ǵ����֮��Ĵ�ֱ���
        float verticalOffset = i * traceSpacing;
        // ���ݵ������ݻ���·��
        for (size_t j = 1; j < trace.size(); ++j) {
            // ʹ��QGraphicsLineItem��ʾ·��
            QGraphicsLineItem* lineItem = new QGraphicsLineItem();
            // ����������ɫ
            lineItem->setPen(wigglePen);

            // ʹ�� verticalOffset ����������Ĵ�ֱλ��
            lineItem->setLine((j - 1) * sampleSpacing, -trace[j - 1] * traceHeight + verticalOffset,
                j * sampleSpacing, -trace[j] * traceHeight + verticalOffset);
            scene->addItem(lineItem);
        }
    }
    // ���ó�����С
    scene->setSceneRect(scene->itemsBoundingRect());
    // ���������ø� QGraphicsView
    wiggleView->setScene(scene);
    //// ������ͼ��С
    //wiggleView->setFixedSize(800, 600);

    // ��ʾ QGraphicsView
    wiggleView->show();
}
//wiggle��ʾ��������vertical direction
void Qt_segy_process::WiggleView_show_V() {
        ui.statusBar->setStyleSheet("background-color:orange");
        //�ж�����
        std::vector<std::vector<float>> matrix;
        if (dataArray_real.empty()) {
            ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
            ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
            return;
        }
        matrix = dataArray_real;
        matrix = normalized(matrix);

        QWidget* wiggle_widget = new QWidget();
        isWiggleViewCreated = true;
        //���ÿؼ�������ʾ��
        QVBoxLayout* wiggle_main_layout = new QVBoxLayout(wiggle_widget);

        QWidget* wiggle_widget1 = new QWidget();
        QWidget* wiggle_widget2 = new QWidget();
        QWidget* wiggle_widget3 = new QWidget();

        QHBoxLayout* wiggle_widget1_layout = new QHBoxLayout(wiggle_widget1);
        QHBoxLayout* wiggle_widget2_layout = new QHBoxLayout(wiggle_widget2);
        QHBoxLayout* wiggle_widget3_layout = new QHBoxLayout(wiggle_widget3);

        wiggle_main_layout->addWidget(wiggle_widget1);
        wiggle_main_layout->addWidget(wiggle_widget2);//�������
        wiggle_main_layout->addWidget(wiggle_widget3);

        // ���� s�ĸ�QDial �ؼ�
        //traceSpacing = wiggle_dial_1->value();//�����
        //sampleSpacing = wiggle_dial_2->value();//��������
        //traceHeight = wiggle_dial_3->value();//ÿ���߶ȣ����ֵ
        //line_width_wiggle = wiggle_dial_4->value();//wiggle�߿�
        wiggle_dial_1 = new QDial();
        wiggle_dial_1->setNotchesVisible(true);
        wiggle_dial_1->setRange(1, 50); wiggle_dial_1->setSingleStep(1); wiggle_dial_1->setValue(10);//���ó�ʼֵ
        label_dial_1 =new QLabel("1");
        label_dial_1->setAlignment(Qt::AlignHCenter);

        wiggle_dial_2 = new QDial();
        wiggle_dial_2->setRange(1, 5);  wiggle_dial_2->setSingleStep(1);wiggle_dial_2->setValue(1);//���ó�ʼֵ
        wiggle_dial_2->setNotchesVisible(true);
        label_dial_2 = new QLabel("2");
        label_dial_2->setAlignment(Qt::AlignHCenter);

        wiggle_dial_3 = new QDial();
        wiggle_dial_3->setNotchesVisible(true);
        wiggle_dial_3->setRange(0, 100);  wiggle_dial_3->setSingleStep(1); wiggle_dial_3->setValue(20);//���ó�ʼֵ
        label_dial_3 = new QLabel("3");
        label_dial_3->setAlignment(Qt::AlignHCenter);

        wiggle_dial_4 = new QDial();
        wiggle_dial_4->setNotchesVisible(true);
        wiggle_dial_4->setRange(1, 10);  wiggle_dial_4->setSingleStep(1); wiggle_dial_4->setValue(1);//���ó�ʼֵ
        label_dial_4 = new QLabel("4");
        label_dial_4->setAlignment(Qt::AlignHCenter);

        /// ���� QGraphicsView �� QGraphicsScene
        wiggleView = new QGraphicsView();
        wiggleView->setWindowTitle("WiggleView_show_V");
        QGraphicsScene* scene = new QGraphicsScene();
        // ���ñ�����ɫ������������
        QBrush backgroundBrush(Qt::white);  // ����Ϊ��ɫ������Ҳ����ʹ�������������ɫ
        scene->setBackgroundBrush(backgroundBrush);
        // ���û�ͼ����
        int traceHeight = 20;//ÿ���ĸ߶�
        int traceSpacing = 10;//��֮����
        int sampleSpacing = 1;//������֮����
        // ���� Wiggle ͼ��ɫ
        QPen wigglePen;
        wigglePen.setColor(Qt::black);  // ������ɫΪ��ɫ
        wigglePen.setWidth(1);
        for (size_t i = 0; i < matrix.size(); ++i) {
            const std::vector<float>& trace = matrix[i];//ȡ��ÿһ��
            // ���ǵ����֮��Ĵ�ֱ���
            float HOffset = i * traceSpacing;
            // ���ݵ������ݻ���·��
            for (size_t j = 1; j < trace.size(); ++j) {
                // ʹ��QGraphicsLineItem��ʾ·��
                QGraphicsLineItem* lineItem = new QGraphicsLineItem();
                // ����������ɫ
                lineItem->setPen(wigglePen);
                // ʹ�� HOffset ����������Ĵ�ֱλ��
                lineItem->setLine(-trace[j - 1] * traceHeight + HOffset, (j - 1) * sampleSpacing ,
                    -trace[j] * traceHeight + HOffset,j * sampleSpacing  );
                scene->addItem(lineItem);
            }
        }
        // ���ó�����С
        scene->setSceneRect(scene->itemsBoundingRect());
        // ���������ø� QGraphicsView
        wiggleView->setScene(scene);
        //// ������ͼ��С
        //wiggleView->setFixedSize(800, 600);
        // ��������������
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setInteractive(true);
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        //wiggleView->setRenderHint(QPainter::HighQualityAntialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setDragMode(QGraphicsView::ScrollHandDrag);

        // ����ʵ���������¼�������
        wiggleView->viewport()->installEventFilter(this);
        // ��ʾ QGraphicsView
        wiggleView->show();

        wiggle_widget1_layout->addWidget(wiggleView);
        wiggle_widget2_layout->addWidget(label_dial_1);
        wiggle_widget2_layout->addWidget(label_dial_2);
        wiggle_widget2_layout->addWidget(label_dial_3);
        wiggle_widget2_layout->addWidget(label_dial_4);

        wiggle_widget3_layout->addWidget(wiggle_dial_1);
        wiggle_widget3_layout->addWidget(wiggle_dial_2);
        wiggle_widget3_layout->addWidget(wiggle_dial_3);
        wiggle_widget3_layout->addWidget(wiggle_dial_4);
        wiggle_widget->show();

        //��dial�������ϵ������ͼ��
        connect(wiggle_dial_1, SIGNAL(valueChanged(int)), this, SLOT(Dial_1_ValueChanged(int)));
        connect(wiggle_dial_2, SIGNAL(valueChanged(int)), this, SLOT(Dial_2_ValueChanged(int)));
        connect(wiggle_dial_3, SIGNAL(valueChanged(int)), this, SLOT(Dial_3_ValueChanged(int)));
        connect(wiggle_dial_4, SIGNAL(valueChanged(int)), this, SLOT(Dial_4_ValueChanged(int)));

    }
//���»ص�����
void Qt_segy_process::updataWigglePlot() {
        /*ui.statusBar->setStyleSheet("background-color:orange");*/
        //�ж�����
        std::vector<std::vector<float>> matrix;
        if (dataArray_real.empty()) {
            ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
            ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
            return;
        }
        matrix = dataArray_real;
        matrix = normalized(matrix);
        /// ���� QGraphicsView �� QGraphicsScene
        //wiggleView = new QGraphicsView();
        wiggleView->setWindowTitle("WiggleView_show_V");
        QGraphicsScene* scene = new QGraphicsScene();
        // ���ñ�����ɫ������������
        QBrush backgroundBrush(Qt::white);  // ����Ϊ��ɫ������Ҳ����ʹ�������������ɫ
        scene->setBackgroundBrush(backgroundBrush);
        // ���û�ͼ����
        traceHeight = 20;//ÿ���ĸ߶�
        //int traceSpacing = 10;//��֮����
        sampleSpacing = 1;//������֮����
        line_width_wiggle = 1;
        traceSpacing= wiggle_dial_1->value();//�����
        sampleSpacing = wiggle_dial_2->value();//��������
        traceHeight = wiggle_dial_3->value();//ÿ���߶ȣ����ֵ
        line_width_wiggle = wiggle_dial_4->value();//wiggle�߿�


        // ���� Wiggle ͼ��ɫ
        QPen wigglePen;
        wigglePen.setColor(Qt::black);  // ������ɫΪ��ɫ
        wigglePen.setWidth(line_width_wiggle);
        for (size_t i = 0; i < matrix.size(); ++i) {
            const std::vector<float>& trace = matrix[i];//ȡ��ÿһ��
            // ���ǵ����֮��Ĵ�ֱ���
            float HOffset = i * traceSpacing;
            // ���ݵ������ݻ���·��
            for (size_t j = 1; j < trace.size(); ++j) {
                // ʹ��QGraphicsLineItem��ʾ·��
                QGraphicsLineItem* lineItem = new QGraphicsLineItem();
                // ����������ɫ
                lineItem->setPen(wigglePen);
                // ʹ�� HOffset ����������Ĵ�ֱλ��
                lineItem->setLine(-trace[j - 1] * traceHeight + HOffset, (j - 1) * sampleSpacing,
                    -trace[j] * traceHeight + HOffset, j * sampleSpacing);
                scene->addItem(lineItem);
            }
        }
        // ���ó�����С
        scene->setSceneRect(scene->itemsBoundingRect());
        // ���������ø� QGraphicsView
        wiggleView->setScene(scene);
        //// ������ͼ��С
        //wiggleView->setFixedSize(800, 600);
        // ��������������
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setInteractive(true);
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        //wiggleView->setRenderHint(QPainter::HighQualityAntialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setDragMode(QGraphicsView::ScrollHandDrag);

        // ����ʵ���������¼�������
        wiggleView->viewport()->installEventFilter(this);
        // ��ʾ QGraphicsView
        wiggleView->show();
}
//����QGraphicsView* viewͼ��
void Qt_segy_process::saveWiggleViewImage(QGraphicsView* view) {
    // Render the QGraphicsView content to a QPixmap
    QPixmap pixmap(view->viewport()->size());
    // Create a QPainter to render into the QPixmap
    QPainter painter(&pixmap);
    // Render the QGraphicsView content to the QPixmap
    view->render(&painter);
    // End painting
    painter.end();
    // Ask the user for the file name and location
    QString filePath = QFileDialog::getSaveFileName(view, "Save Image", "", "Images (*.png *.jpg *.bmp)");
    // Check if the user canceled the dialog
    if (!filePath.isEmpty()) {
        // Save the QPixmap to the specified file
        pixmap.save(filePath);
    }
    QString message = QString("wiggle save completed! ");
    ui.statusBar->showMessage(message);
}
//����wiggleͼ��
void Qt_segy_process::saveWiggle_1() {
    // Check if wiggleView is created successfully
    if (isWiggleViewCreated) {
        // ��� wiggleView �Ƿ��������
        if (wiggleView != nullptr && !wiggleView->scene()->items().isEmpty()) {
            // wiggleView ��������
            saveWiggleViewImage(wiggleView);
        }
        else {
            // wiggleView ��û������
            qDebug() << "wiggleView is empty.";
            ui.statusBar->setStyleSheet("background-color:red");
        }
    }
    else {
        // Handle the case where wiggleView creation failed
        qDebug() << "wiggleView is not created.";
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        ui.statusBar->setStyleSheet("background-color:red");
    }
}
//��agc������ת����dataarray�У�����
void Qt_segy_process::agcdata2dataarray() {
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    if (agc_save_data.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr(" please load the agc data first."), 3000);
        return;
    }
    dataArray_real = transposeMatrix(agc_save_data);

    QString message = QString("AGC loaded! Trace simple %1 ;Trace number %2;").arg(agc_save_data.size()).arg(agc_save_data[0].size());
    ui.statusBar->showMessage(message);
}
//��ԭʼ·���л�ȡԭʼ����
void Qt_segy_process::get_orignal_real() {
    std::string filePath = OpenFile_segy.toStdString();//get file_path
    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";
        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);
    dataArray_real = dataArray;//��ά������ʽ��rowΪ�����;
    QString message = QString("Real data loaded! Trace simple %1 ;Trace number %2;").arg(dataArray_real.size()).arg(dataArray_real[0].size());
    ui.statusBar->showMessage(message);
}
//dial�ı�wiggle����
void Qt_segy_process::Dial_1_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_1->value()), 3000);
    updataWigglePlot();
    label_dial_1->setText(QString("trace space Value: %1").arg(wiggle_dial_1->value()));//���±�ǩ��ֵ
}
void Qt_segy_process::Dial_2_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_2->value()), 3000);
    updataWigglePlot();
    label_dial_2->setText(QString("height Value: %1").arg(wiggle_dial_2->value()));//���±�ǩ��ֵ
} 
void Qt_segy_process::Dial_3_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_3->value()), 3000);
    updataWigglePlot();
    label_dial_3->setText(QString("max Value: %1").arg(wiggle_dial_3->value()));//���±�ǩ��ֵ
}
void Qt_segy_process::Dial_4_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_4->value()), 3000);
    updataWigglePlot();
    label_dial_4->setText(QString("line width Value: %1").arg(wiggle_dial_4->value()));//���±�ǩ��ֵ
    label_dial_4->setText(QString("line width Value: %1").arg(wiggle_dial_4->value()));//���±�ǩ��ֵ
}
//wiggle������ƶ��¼��ػ�
bool Qt_segy_process::eventFilter(QObject* obj, QEvent* event) {//����������
    if (obj == wiggleView->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        int delta = wheelEvent->angleDelta().y();
        qreal factor = 1.2; // ������������
        if (delta > 0) {
            wiggleView->scale(factor, factor);
        }
        else {
            wiggleView->scale(1.0 / factor, 1.0 / factor);
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}
//3d��ͼ
void Qt_segy_process::draw3DData() {
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
    return;
}
    QWidget* data_3d = new QWidget();
    data_3d->setMinimumSize(800, 600);
    // ���� Q3DScatter
    Q3DScatter* scatter = new Q3DScatter();
    // ���3Dɢ��ϵ��
    QScatter3DSeries* series = new QScatter3DSeries;
    series->setItemLabelFormat(QStringLiteral("(@xLabel @yLabel @zLabel)"));
    series->setMesh(QAbstract3DSeries::MeshSphere);
    series->setMeshSmooth(true);

    // �������
    QScatterDataArray data;
    std::vector<std::vector<float>> matrixData;
    dataArray = normalized(dataArray_real);
    matrixData = dataArray_real;
    // �� matrixData ת��Ϊ QVector<QVector3D>
    for (int i = 0; i < dataArray_real.size(); ++i) {
        for (int j = 0; j < dataArray_real[i].size(); ++j) {

            data << QVector3D( i, j, matrixData[i][j]);
        }
    }
    series->dataProxy()->addItems(data);
    scatter->addSeries(series);
    // ����������
    scatter->axisX()->setTitle(QStringLiteral("X Axis-trace"));
    scatter->axisY()->setTitle(QStringLiteral("Y Axis-sample"));
    scatter->axisZ()->setTitle(QStringLiteral("Z Axis-value"));
    //���������᷶Χ
    /////�ж����ֵ��Сֵ�Ƿ�С��1
    //float minValue = findMinMaxValue(dataArray, 0);
    //float maxValue = findMinMaxValue(dataArray, 1);//��ȡ
    //scatter->axisX()->setRange(0, dataArray.size());
    //scatter->axisY()->setRange(0, dataArray[0].size());
    //scatter->axisZ()->setRange(minValue, maxValue);  // minZValue �� maxZValue ����������� Z ֵ����С�����ֵ
    //scatter->activeTheme()->setType(Q3DTheme::ThemeQt);
    // �����ӽ�
    scatter->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    // ���ò���
   // ʹ�� QPointer ���� QVBoxLayout ��� Q3DScatter
    QPointer<QWidget> scatterContainer = QWidget::createWindowContainer(scatter);
    QVBoxLayout* layout = new QVBoxLayout(data_3d);
    layout->addWidget(scatterContainer);

    data_3d->show();
}
//S�任
void Qt_segy_process::SF_function() {

    if (dataArray.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    vector<double> s;//�洢�������ݿռ�
    // ����ʱ������ t
    vector<double> t;

    int data_tracei = 80;

    for (int i = 0; i < dataArray.size(); i++) {//��ȡָ��i�ĵ�������

        s.push_back(dataArray[i][data_tracei]);//�õ�һά����data
    }
    double dt = 0.001;
    int time_len = s.size();
    for (int i = 0; i < time_len; i++) {
        t.push_back(i * dt);
    }
    // �������
    if (t.empty() || s.empty() || t.size() != s.size()) {
        cerr << "Error: Invalid input data." << endl;
        return ; // ���߲�ȡ�������ʵĴ���ʽ
    }
    for (double time : t) {
        // �����Ҳ�Ϊ����Ƶ��Ϊ10 Hz�����Ϊ1
        double signal = sin(2 * M_PI * 10 * time);
        s.push_back(signal);
    }
    double freqlow = 1.0;
    double freqhigh = 1000.0;
    double alpha = 1.0;

    // ����S�任
    vector<vector<complex<double>>> data_s = st(t, s, freqlow, freqhigh, alpha);

    // ��ȡ��һ��Ԫ�ص�ʵ��
    double realPart = data_s[0][0].real();

    // Ҳ���Ա���������ά����
    for (const auto& row : data_s) {
        for (const auto& elem : row) {
            double elemReal = elem.real();
            // ������ʹ�� elemReal
        }
    }

        // ����������ά��������ӡʵ��
    std::vector<std::vector<float>> temp(data_s.size(), std::vector<float>(data_s[0].size()));

    for (int i = 0; i < data_s.size(); ++i) {
        for (int j = 0; j < data_s[i].size(); ++j) {
            cout << "(" << data_s[i][j].real() << ", " << data_s[i][j].imag() << ") ";
            
            temp[i][j] = static_cast<float>(data_s[i][j].real());
        }
        cout << endl;
    }
    //temp = normalized(temp);
    src = dataArray2image(temp);
    QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(temp.size()).arg(temp[0].size());
    ui.statusBar->showMessage(message);


    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//�Ҷ�ͼ
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // ��ʾcolorMap
    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����

    

    //QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
//ui.statusBar->showMessage(message);
}
std::vector<std::vector<std::complex<double>>> Qt_segy_process::st(const std::vector<double>& t, const std::vector<double>& s, double freqlow, double freqhigh, double alpha) {
    ui.statusBar->setStyleSheet("background-color:red");

    int TimeLen = t.size();
    double dt = t[1] - t[0];
    int nLevel = static_cast<int>((freqhigh - freqlow) / alpha) + 1;

    vector<vector<complex<double>>> wcoefs(nLevel, vector<complex<double>>(TimeLen, { 0.0, 0.0 }));

    for (int m = 0; m < nLevel; ++m) {
        double f = freqlow + m * alpha;
        double sigma_f = 1.0 / f;

        for (int n = 0; n < TimeLen; ++n) {
            double Gauss_st = (1.0 / (sqrt(2 * M_PI) * sigma_f)) * exp(-0.5 * pow(n * dt - t[n], 2) / pow(sigma_f, 2)) * cos(2 * M_PI * f * t[n]);
            wcoefs[m][n] = { 0.0, 0.0 };

            for (int i = 0; i < TimeLen; ++i) {
                wcoefs[m][n] += s[i] * Gauss_st * complex<double>(cos(2 * M_PI * f * t[i]), sin(2 * M_PI * f * t[i])) * dt;
            }
        }
    }

    return wcoefs;
}
//��������
void Qt_segy_process::drawcurve()
{
    QChart *chart = new QChart();

    QChartView* chartview = new QChartView();

    QSplineSeries* series = new QSplineSeries();


    for (int i = 0; i <= 100; i ++){ 
        series->append(i, i*i); 
    }
        
    //���������
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();

    QFont font;
    font.setPointSize(20);  // ���������С
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("XXX");
    axisY->setTitleText("YYY");
    axisX->setTickCount(11);//���ÿ̶�����
    axisY->setTickCount(11);
    chart->addAxis(axisX, Qt::AlignBottom);//����λ��
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->addSeries(series);
    chartview->setChart(chart);

    axisX->setRange(0, 100);
    axisY->setRange(0, 100);

    chartview->setRenderHint(QPainter::Antialiasing);

    chartview->show();

}

void Qt_segy_process::drawcurve2() {
   
   /* QWidget* widget2 = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();*/

    const QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();
    if (inputDevice.isNull()) {
        QMessageBox::warning(nullptr, "audio",
            "There is no audio input device available.");
        return;
    }
    else {
        ui.statusBar->showMessage("ok");
    }

    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);
    QChartView* chartview = new QChartView();
    chartview->setMinimumHeight(400);
    chartview->setStyleSheet("backgroung-color:black");
    QChart* chart = new QChart();
    QSplineSeries* series1 = new QSplineSeries();
    QTextEdit* textedit = new QTextEdit();
    
    QString message = QString("inputDevice%1").arg(inputDevice.description());
    textedit->setText(message);
    textedit->setMaximumHeight(200);
    textedit->setStyleSheet("background-color:rgb(255,255,255);font-size:20px; ");

    layout->addWidget(chartview);
    chartview->setChart(chart);
    layout->addWidget(textedit);

    //������Ƶ������ʽ
    QAudioFormat formatAudio;
    formatAudio.setSampleRate(20000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleFormat(QAudioFormat::UInt8);
    //�жϲ�����ʽ�Ƿ�֧��
    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    if (!info.isFormatSupported(formatAudio)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }
    else {
        ui.statusBar->showMessage(" format ok");
    }
    //������ƵԴ
    audio = new QAudioSource(inputDevice, formatAudio, this);
    
    QBuffer audiodata;

    audio->start();
    QTimer::singleShot(3000, this, &Qt_segy_process::stopRecording);
    //
    // �˴���Ҫ�洢audio����
    //
    //// ����������
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // �����������ǩ
    axisX->setTitleText("time");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // ���������С
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // ����������ӵ� QChart ��
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    axisX->setRange(0, 100);
    axisY->setRange(0, 100);

    // ��ϵ�й�����������
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);

    chart->legend()->hide();
    chart->setTitle("data from"+ inputDevice.description()+" ok");
    chart->setTitleFont(font);
    chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);

    chart->addSeries(series1);
    widget->show();
}
void Qt_segy_process::stopRecording()
{
    audio->stop();

    delete audio;
    ui.statusBar -> showMessage("stopRecording");
}


void Qt_segy_process::PolarChart() {
    const qreal angularMin = -100;
    const qreal angularMax = 100;

    const qreal radialMin = -100;
    const qreal radialMax = 100;

    //����
    QScatterSeries* series1 = new QScatterSeries();
    series1->setName("scatter");
    for (int i = angularMin; i <= angularMax; i += 10)
        series1->append(i, (i / radialMax) * radialMax + 8.0);

    //ģ��
    QPolarChart* chart = new QPolarChart();
    chart->addSeries(series1);

    //��
    QValueAxis* angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis* radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    series1->attachAxis(radialAxis);
    series1->attachAxis(angularAxis);

    radialAxis->setRange(radialMin, radialMax);
    angularAxis->setRange(angularMin, angularMax);

    QChartView* chartView = new QChartView();

    //�����ص���ͼ��

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}
void Qt_segy_process::PolarChart2() {
    
    //const qreal angularMin = -100;
    //const qreal angularMax = 100;

    //const qreal radialMin = -100;
    //const qreal radialMax = 100;
    //ģ��
    QPolarChart* chart = new QPolarChart();
    
    //����
    //QScatterSeries* series1 = new QScatterSeries();
    //series1->setName("scatter");
    //for (int i = angularMin; i <= angularMax; i += 10)
    //    series1->append(i, (i / radialMax) * radialMax + 8.0);

    QLineSeries* series = new QLineSeries();//����
    series->setPen(QPen(QColor(Qt::blue)));
    for (int i = 0; i <= 100; i++) {
        series->append(i / 100.0 * 360.0, qSin(i / 100.0 * M_PI * 6) * 2);
    }
    QAreaSeries* series4 = new QAreaSeries();//����
    series4->setUpperSeries(series);
    series4->setPen(QPen(QColor(255, 150, 20, 0)));
    series4->setBrush(QColor(255, 150, 20, 60));
    
    //chart->addSeries(series1);
    chart->addSeries(series);
    chart->addSeries(series4);
    //��
    QValueAxis* angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis* radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    //radialAxis->setRange(radialMin, radialMax);
    //angularAxis->setRange(angularMin, angularMax);
    series->attachAxis(angularAxis);
    series->attachAxis(radialAxis);
    series4->attachAxis(angularAxis);
    series4->attachAxis(radialAxis);

    QChartView* chartView = new QChartView();
    //�����ص���ͼ��
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}
//toolbar��ʾversion
void Qt_segy_process::show_version_info() {

    widget_info = new QWidget();
    stylesheet_QT style_info;

    widget_info->setMinimumSize(600, 400);
    widget_info->setStyleSheet(style_info.information_widget);
    widget_info->setWindowTitle("version!");

    QVBoxLayout* widget_info_layout = new QVBoxLayout(widget_info);

    QLabel* info_label = new QLabel("Software Information");
    info_label->setMaximumSize(600, 50);
    info_label->setStyleSheet("color:rgb(0,0,128); font-size:30px; border-radius:50px; ");

    QWidget* widget_1 = new QWidget();
    widget_1->setMinimumHeight(200);
    widget_1->setStyleSheet(style_info.information_widget);

    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    widget_info_layout->addWidget(info_label);
    widget_info_layout->addWidget(widget_1);

    QTextEdit* textEdit1 = new QTextEdit();///������Ϣ
    textEdit1->setReadOnly(true);
    textEdit1->setStyleSheet("background-color:rgb(200,200,200);font-size:20px; ");
    widget_1_layout->addWidget(textEdit1);
    textEdit1->setPlainText("Version_1.0,author by Rain!\n"
                            "Warning: This computer program is protected by copyright laws and international treaties.");
    info_close = new QPushButton("ok");
    info_close->setMinimumSize(100, 30);
    info_close->setMaximumSize(160, 50);
    info_close->setStyleSheet(style_info.button_save_style1);
    

    widget_info_layout->addWidget(info_close, 0, Qt::AlignHCenter);
    widget_info->show();
    //״̬���仯
    ui.statusBar->setStyleSheet(style_info.styleSheet_bar);
    QString message = QString("The window has opened.Information has been shown");
    ui.statusBar->showMessage(message);

    ///slot
    connect(info_close, SIGNAL(clicked()), this, SLOT(closeVersionInfo()));//�ۺ����ڲ�ʵ�ֹر�;
}
void Qt_segy_process::closeVersionInfo() {
    widget_info->close();
}
///���ݶ���
//std::vector<std::vector<float>> dataarray

///��ȡ��������
//for (int i = 0; i < dataarray_agc.size(); i++) {//��ȡָ��i�ĵ�������
//
//    data.push_back(dataarray_agc[i][data_tracei]);//�õ�һά����data
//}
///��ȡ��ά����
//for (int i = 0; i < dataArray.size(); ++i) {
//    for (int j = 0; j < dataArray[i].size(); ++j) {
//         dataArray[i][j]=0
//    }
//}
///QChartView��ͼ
//QChartView* ChartView_widget = new QChartView();
//QChart* chart = new QChart();
//QSplineSeries* series = new QSplineSeries();
//
//// �� std::vector<float> �е�������ӵ� QSplineSeries ��
//for (size_t i = 0; i < Freq.size(); ++i) {
//    series->append(Freq[i], Ampli[i]);
//}
//chart->addSeries(series);
//
//// ����������
//QValueAxis* axisX = new QValueAxis;
//QValueAxis* axisY = new QValueAxis;
//
//// �����������ǩ
//axisX->setTitleText("Freq");
//axisY->setTitleText("Ampli");
//
//QFont font;
//font.setPointSize(20);  // ���������С
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//
//// ����������ӵ� QChart ��
//chart->addAxis(axisX, Qt::AlignBottom);
//chart->addAxis(axisY, Qt::AlignLeft);
//
//// ��ϵ�й�����������
//series->attachAxis(axisX);
//series->attachAxis(axisY);
//
//chart->legend()->hide();
//chart->setTitle("CV_algorithm_FFT");
//chart->setTitleFont(font);
////chart->createDefaultAxes();
//chart->setTheme(QChart::ChartThemeLight);
//ChartView_widget->setChart(chart);
//
//ChartView_widget->show();
///�ж������Ƿ�Ϊ��
//if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��
//
//    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
//    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
//    return;
//}
///״̬����ʾ��Ϣ
//ui.statusBar->showMessage(QString("disk location:%1").arg(OpenFile_segy), 3000);
//QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
//ui.statusBar->showMessage(message);
//
//QString message = QString("support");
//ui.statusBar->showMessage(message);
///�½���ť
//QPushButton* Page4_button = new QPushButton("page4_button");//open
//Page4_button->setStyleSheet(style1.button_save_style1);
//Page4_button->setMinimumSize(80, 40);
//right_layout->addWidget(Page4_button);
///�½�������ֵ����
//data_trace_i = new QSpinBox();//����fft_sample_rate��ֵ
//data_trace_i->setToolTip("<html><font size='5' color='lightgreen'>QSpinBox</font></html>");
//data_trace_i->setMinimum(0);
//data_trace_i->setValue(500);
//data_trace_i->setMaximumWidth(200);
//data_trace_i->setMaximumHeight(50);
//data_trace_i->setStyleSheet("background-color:rgb(200,200,200)");
//page2_widget3_layout->addWidget(data_trace_i);//���ò㲼��
///����ת��ΪͼƬ��cv������ʾ
//std::vector<std::vector<float>> temp;
//temp = dataarray;//������������,���ݴ洢��
//temp = normalized(temp);
//src = dataArray2image(temp);
//
//QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//�Ҷ�ͼ
//label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
//
//cv::namedWindow("AGC", cv::WINDOW_NORMAL);
//cv::imshow("AGC", src); // ��ʾcolorMap
//waitKey(0);
//cv::destroyAllWindows(); // �ر�����OpenCV����
//
//QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
//ui.statusBar->showMessage(message);
///cvͼƬ��ɫת��
//applyColorMap(image, colorMap, cv::COLORMAP_OCEAN); // ʹ��Jet��ɫӳ�䣬�����ѡ������ӳ��
////COLORMAP_JET��Jet��ɫӳ�䣬���������α��ɫӳ��֮һ��ͨ�����ڱ�ʾ�ȶȡ�
////COLORMAP_RAINBOW���ʺ���ɫӳ�䣬���ڱ�ʾ�������ݵĲ�ͬ����
////COLORMAP_HOT��Hot��ɫӳ�䣬���ڱ�ʾ�ȶȣ�ͨ�������¶����ݡ�
////COLORMAP_COOL��Cool��ɫӳ�䣬���ڱ�ʾ�¶ȣ�ͨ�����䵽�ȵ��¶ȱ仯��
////COLORMAP_SPRING��Spring��ɫӳ�䣬���ڱ�ʾ�¶Ȼ��¶ȱ仯��
////COLORMAP_SUMMER��Summer��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
////COLORMAP_AUTUMN��Autumn��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
////COLORMAP_WINTER��Winter��ɫӳ�䣬���ڱ�ʾ���ڻ��¶ȡ�
////COLORMAP_OCEAN��Ocean��ɫӳ�䣬ͨ�����ڱ�ʾ�����ˮ����ȡ�
////COLORMAP_PINK��Pink��ɫӳ�䣬ͨ�����ڱ�ʾ�������ݵĲ�ͬ����
////COLORMAP_HOT��Jet��ɫӳ�䣬���������α��ɫӳ��֮һ��ͨ�����ڱ�ʾ�ȶ�*
//
//imshow("colormap", colorMap);
///��ʾһά����
//QChartView* ChartView_widget = new QChartView();
//QChart* chart = new QChart();
//QSplineSeries* series = new QSplineSeries();
//
//for (size_t i = 0; i < fft_result_freq.size(); ++i) {
//
//    series->append(i, fft_result_freq[i][3]);
//    ;
//}
//chart->addSeries(series);
//ChartView_widget->setChart(chart);
//ChartView_widget->show();
///һά���ݻ�������
//QChart* chart = new QChart();
//
//QChartView* chartview = new QChartView();
//
//QSplineSeries* series = new QSplineSeries();
//
//
//for (int i = 0; i <= 100; i++) {
//    series->append(i, i * i);
//}
//
////���������
//QValueAxis* axisX = new QValueAxis();
//QValueAxis* axisY = new QValueAxis();
//
//QFont font;
//font.setPointSize(20);  // ���������С
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//axisX->setTitleText("XXX");
//axisY->setTitleText("YYY");
//axisX->setTickCount(11);//���ÿ̶�����
//axisY->setTickCount(11);
//chart->addAxis(axisX, Qt::AlignBottom);//����λ��
//chart->addAxis(axisY, Qt::AlignLeft);
//series->attachAxis(axisX);
//series->attachAxis(axisY);
//chart->addSeries(series);
//chartview->setChart(chart);
//
//axisX->setRange(0, 100);
//axisY->setRange(0, 100);
//
//chartview->setRenderHint(QPainter::Antialiasing);
//
//chartview->show();
