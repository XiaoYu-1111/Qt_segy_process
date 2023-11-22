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
    //左侧窗口

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

    //右侧窗口
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

    //中间页面
    QVBoxLayout* center_layout = new QVBoxLayout(main_center_Widget);

    stackedWidget1 = new QStackedWidget;//堆叠窗口
    center_layout->addWidget(stackedWidget1);
    center_layout->setContentsMargins(0, 0, 0, 0);
    page1 = new QWidget;//添加新页面
    page2 = new QWidget;
    page3 = new QWidget;
    page4 = new QWidget;
    page5 = new QWidget;

    stackedWidget1->addWidget(page1);
    stackedWidget1->addWidget(page2);
    stackedWidget1->addWidget(page3);
    stackedWidget1->addWidget(page4);
    stackedWidget1->addWidget(page5);
    page1->setStyleSheet("background-color:rgb(255,255,255);border-radius:5px;");//21界面样式设置
    page2->setStyleSheet("background-color:rgb(210,210,210);border-radius:5px;");//22界面样式设置
    page3->setStyleSheet("background-color:rgb(220,220,220);border-radius:5px;");//23界面样式设置
    page4->setStyleSheet("background-color:rgb(230,230,230);border-radius:5px;");//24界面样式设置
    page5->setStyleSheet("background-color:rgb(240,240,240);border-radius:5px;");//25界面样式设置


    //主页面槽函数
    connect(open_button, SIGNAL(clicked()), this, SLOT(open_segy()));//打开文件
    connect(show_button, SIGNAL(clicked()), this, SLOT(show_segy()));//打开文件
    connect(save_picture_button, SIGNAL(clicked()), this, SLOT(save_segy_picture()));//打开文件
    connect(save_button, SIGNAL(clicked()), this, SLOT(save_segy()));//打开文件
    //跳转页面
    connect(main_button, SIGNAL(clicked()), this, SLOT(on_stackpage1_change_clicked()));// 切换到第一页
    connect(Page1_button, SIGNAL(clicked()), this, SLOT(on_stackpage1_change_clicked()));// 切换到第一页

    connect(Page2_button, SIGNAL(clicked()), this, SLOT(on_stackpage2_change_clicked()));// 切换到第二页
    connect(Page3_button, SIGNAL(clicked()), this, SLOT(on_stackpage3_change_clicked()));// 切换到第三页
    connect(Page4_button, SIGNAL(clicked()), this, SLOT(on_stackpage4_change_clicked()));// 切换到第四页
    connect(Page5_button, SIGNAL(clicked()), this, SLOT(on_stackpage5_change_clicked()));

    ///toolbar部分
    //part1
    QAction* myAction1 = new QAction("Main", this);//主动作行为
    // 创建下拉菜单并添加格子选项
    QMenu* myMenu = new QMenu(this);
    QAction* option1Action = new QAction("Option 1", this);
    myMenu->addAction(option1Action);
    myMenu->addAction("Option 2");
    myMenu->addAction("Option 3");
    // 将下拉菜单关联到动作
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
    QAction* myAction2 = new QAction("version", this);//创建version页面入口
    QMenu* myMenu_version = new QMenu(this);//创建version菜单
    QAction* version_info = new QAction("version_info", this);
    myMenu_version->addAction(version_info);
    myMenu_version->addAction("option_2");
    myAction2->setMenu(myMenu_version);
    ui.mainToolBar->addAction(myAction2);//添加进入口到toolbar

    ///toolbar部分solt

    connect(version_info, SIGNAL(triggered()), this, SLOT(show_version_info()));
    connect(option1_agcdata2dataarray, SIGNAL(triggered()), this, SLOT(agcdata2dataarray()));
    connect(option1_get_realdata, SIGNAL(triggered()), this, SLOT(get_orignal_real()));

    ///page1
    QVBoxLayout* page1_layout = new QVBoxLayout(page1);

    label_picture = new QLabel;
    // 加载图片并设置为 QLabel 的背景
    QString  path="D:\\Code\\visual_code\\Open_Cv\\Qt_segy_process\\Qt_segy_process\\icon\\flower.jpg";  // 替换为你的图片路径
    
    label_picture->setMinimumSize(600, 400);

    Mat src = cv::imread(path.toStdString());

    QImage qtImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888);
    label_picture->setPixmap(QPixmap::fromImage(qtImage).scaled(label_picture->size()));

    label_picture->setAlignment(Qt::AlignCenter);
    page1_layout->addWidget(label_picture);


    QWidget* page1_widget1 = new QWidget();
    QHBoxLayout* page1_widget1_layout = new QHBoxLayout(page1_widget1);///第一页面下边窗口
    page1_layout->addWidget(page1_widget1);
    page1_widget1->setStyleSheet("background-color:rgb(200,200,200)");
    page1_widget1->setMaximumHeight(100);

    textEdit1 = new QTextEdit();///放置信息
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
    page2_layout->addWidget(page2_widget3);//按照提加进层的顺序排布
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

    windows_size_value = new QSpinBox();//调节windows_size数值
    windows_size_value->setToolTip("<html><font size='5' color='lightgreen'>AGC windows size!</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    windows_size_value->setMaximumWidth(100);
    windows_size_value->setMaximumHeight(50);
    windows_size_value->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget1_layout->addWidget(windows_size_value);

    QLabel* label_trace_i = new QLabel("trace i");///分割标签
    label_trace_i->setMaximumSize(100, 50);
    label_trace_i->setStyleSheet("background-color:lightgreen");
    page2_widget1_layout->addWidget(label_trace_i);

    agc_trace_i = new QSpinBox();//调节windows_size数值
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

    QLabel* label_sample_rate = new QLabel("sample_rate");///分割标签
    label_sample_rate->setMaximumSize(100, 50);
    label_sample_rate->setStyleSheet("background-color:lightgreen");
    page2_widget3_layout->addWidget(label_sample_rate);

    fft_sample_rate = new QDoubleSpinBox();//调节fft_sample_rate数值
    fft_sample_rate->setToolTip("<html><font size='5' color='lightgreen'>set sample rate!</font></html>");
    //fft_sample_rate->setMinimum(1);
    //fft_sample_rate->setValue(500);
    /*fft_sample_rate->setMaximum(1000);*/
    fft_sample_rate->setMaximumWidth(200);
    fft_sample_rate->setMaximumHeight(50);
    fft_sample_rate->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget3_layout->addWidget(fft_sample_rate);

    QLabel* label_tracei2 = new QLabel("trace i");///分割标签
    label_tracei2->setMaximumSize(100, 50);
    label_tracei2->setStyleSheet("background-color:lightgreen");
    page2_widget3_layout->addWidget(label_tracei2);

    data_trace_i = new QSpinBox();//调节data_trace_i数值
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
    connect(button_fft, SIGNAL(clicked()), this, SLOT(opencv_fft_1d()));//一维傅里叶变换
    connect(button_fft_2d, SIGNAL(clicked()), this, SLOT(opencv_fft2d()));//一维傅里叶变换
    connect(button_fft_show, SIGNAL(clicked()), this, SLOT(chart_fftshow()));
    ///SF_function
    connect(button_STFT, SIGNAL(clicked()), this, SLOT(SF_function()));

    ///page3显示表格
    QVBoxLayout* page3_layout = new QVBoxLayout(page3);
    QPushButton* tableWidget = new QPushButton("table");
    
    tableWidget->setMaximumSize(200, 50);
    tableWidget->setStyleSheet(style1.button_main);
    page3_layout->addWidget(tableWidget);
    //page3显示wiggle
    QPushButton* wiggle_button_H = new QPushButton("Wiggle_H");
    wiggle_button_H->setMaximumSize(200, 50);
    wiggle_button_H->setStyleSheet(style1.button_main);
    page3_layout->addWidget(wiggle_button_H);
    QPushButton* wiggle_button_V = new QPushButton("Wiggle_V");
    wiggle_button_V->setMaximumSize(200, 50);
    wiggle_button_V->setStyleSheet(style1.button_main);
    page3_layout->addWidget(wiggle_button_V);
    //page3eiggle保存
    QPushButton* Save_Wiggle = new QPushButton("Save_Wiggle");
    Save_Wiggle->setMaximumSize(200, 50);
    Save_Wiggle->setStyleSheet(style1.button_main);
    page3_layout->addWidget(Save_Wiggle);
    ///page3   @slot
    connect(tableWidget, SIGNAL(clicked()), this, SLOT(matrix_table_show()));
    connect(wiggle_button_H, SIGNAL(clicked()), this, SLOT(WiggleView_show_H()));
    connect(wiggle_button_V, SIGNAL(clicked()), this, SLOT(WiggleView_show_V()));
    connect(Save_Wiggle, SIGNAL(clicked()), this, SLOT(saveWiggle_1()));
    
    //page4显示3D
    QVBoxLayout* page4_layout = new QVBoxLayout(page4);

    QPushButton* data_3d_but1 = new QPushButton("3D");
    data_3d_but1->setStyleSheet(style1.button_main);
    page4_layout->addWidget(data_3d_but1);
    //slot
    connect(data_3d_but1, SIGNAL(clicked()), this, SLOT(draw3DData()));

}
Qt_segy_process::~Qt_segy_process()
{}
void Qt_segy_process::on_stackpage1_change_clicked()//按钮点击切换到第一页槽函数内容
{
    stackedWidget1->setCurrentIndex(0);
    ui.statusBar->showMessage(" Page1-->", 5000);
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
}
void Qt_segy_process::on_stackpage2_change_clicked()//按钮点击切换到第二页槽函数内容
{
    stackedWidget1->setCurrentIndex(1);
    ui.statusBar->showMessage("Page2-->: ", 5000);
    stylesheet_QT style2;
    ui.statusBar->setStyleSheet(style2.styleSheet_bar);
}
void Qt_segy_process::on_stackpage3_change_clicked()//按钮点击切换到第三页槽函数内容
{
    stackedWidget1->setCurrentIndex(2);
    ui.statusBar->showMessage("Page3-->", 5000);
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);


}
void Qt_segy_process::on_stackpage4_change_clicked()//按钮点击切换到第三页槽函数内容
{
    stackedWidget1->setCurrentIndex(3);
    ui.statusBar->showMessage("Page4-->", 5000);
    stylesheet_QT style3;
    ui.statusBar->setStyleSheet(style3.styleSheet_bar);
}
void Qt_segy_process::on_stackpage5_change_clicked()//按钮点击切换到第三页槽函数内容
{
    stackedWidget1->setCurrentIndex(4);
    ui.statusBar->showMessage("Page4-->", 5000);
    stylesheet_QT style3;
    ui.statusBar->setStyleSheet(style3.styleSheet_bar);
}
//SEISMIC-SEGY——part//open
void Qt_segy_process::open_segy() {
    qDebug() << "input data!";
    ui.statusBar->showMessage(tr("Loading data!"), 5000);
    //QString OpenFile;
    OpenFile_segy = QFileDialog::getOpenFileName(this,//openfile中存储的是图片地址;
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
//show,先获取
void Qt_segy_process::show_segy() {

    std::string filePath = OpenFile_segy.toStdString();//get file_path

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";

        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);

    dataArray_real = dataArray;//存储real_value
    dataArray = normalized(dataArray);
    dataArray = transposeMatrix(dataArray);
    // 创建一个 OpenCV 的 Mat 对象并将 dataArray 数据复制到其中
    //cv::Mat image(dataArray.size(), dataArray[0].size(), CV_8U);//获取到二维数组的行和列；

    //for (int i = 0; i < dataArray.size(); ++i) {
    //    for (int j = 0; j < dataArray[i].size(); ++j) {
    //        // 假设 dataArray 的元素是 [0, 1] 范围内的浮点数
    //        image.at<uchar>(i, j) = dataArray[i][j] * 256;
    //    }
    //}
    // 
    // 创建一个伪彩色映射
    cv::Mat image = dataArray2image(dataArray);//后面定义一个转换函数，将
    cv::Mat colorMap;
    applyColorMap(image, colorMap, cv::COLORMAP_OCEAN); // 使用Jet颜色映射，你可以选择其他映射
    /*COLORMAP_JET：Jet颜色映射，它是最常见的伪彩色映射之一，通常用于表示热度。
        COLORMAP_RAINBOW：彩虹颜色映射，用于表示连续数据的不同级别。
        COLORMAP_HOT：Hot颜色映射，用于表示热度，通常用于温度数据。
        COLORMAP_COOL：Cool颜色映射，用于表示温度，通常从冷到热的温度变化。
        COLORMAP_SPRING：Spring颜色映射，用于表示温度或温度变化。
        COLORMAP_SUMMER：Summer颜色映射，用于表示季节或温度。
        COLORMAP_AUTUMN：Autumn颜色映射，用于表示季节或温度。
        COLORMAP_WINTER：Winter颜色映射，用于表示季节或温度。
        COLORMAP_OCEAN：Ocean颜色映射，通常用于表示海洋或水的深度。
        COLORMAP_PINK：Pink颜色映射，通常用于表示连续数据的不同级别。
        COLORMAP_HOT：Jet颜色映射，它是最常见的伪彩色映射之一，通常用于表示热度*/
        // 显示图像
    //imshow("colormap", colorMap);
    //cv::namedWindow("Original", cv::WINDOW_NORMAL);
    //cv::imshow("Original", image); // 显示原始图像
    //cv::namedWindow("colorMap", cv::WINDOW_NORMAL);
    //cv::imshow("colorMap", colorMap); // 显示colorMap
    //cv::namedWindow("Resized", cv::WINDOW_NORMAL);
    //cv::imshow("Resized", resized); // 显示调整后的图像

    float minValue = findMinMaxValue(dataArray_real, 0); // 查找最小值
    float maxValue = findMinMaxValue(dataArray_real, 1); // 查找最大值

    QString message = QString("orignal data value in Min Value: %1,<-> Max Value: %2").arg(minValue).arg(maxValue);
    ui.statusBar->showMessage(message);
    //主页面显示数据
    src = image;
    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口
    /*textEdit1->setText("dataArray_real");*/
    textEdit1->append(tr("dataArray_real:trace simple:%1 ;trace number %2").arg(dataArray.size()).arg(dataArray[0].size()));
    textEdit1->append(tr("dataArray_real:minvalue:%1 ;maxvalue %2").arg(minValue).arg(maxValue));

    stackedWidget1->setCurrentIndex(0);//显示图片呢，跳转到首页
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
    QString SaveFile_segy = QFileDialog::getSaveFileName(this,//对话框得到存储路径
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
//存储数据到图片
void Qt_segy_process::save_segy_picture() {

    std::string filePath = OpenFile_segy.toStdString();//get file_path

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";

        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);

    dataArray_real = dataArray;//存储real_value
    dataArray = normalized(dataArray);
    dataArray = transposeMatrix(dataArray);
    // 创建一个 OpenCV 的 Mat 对象并将 dataArray 数据复制到其中
    Mat image(dataArray.size(), dataArray[0].size(), CV_8U);//获取到二维数组的行和列；

    for (int i = 0; i < dataArray.size(); ++i) {
        for (int j = 0; j < dataArray[i].size(); ++j) {
            // 假设 dataArray 的元素是 [0, 1] 范围内的浮点数
            image.at<uchar>(i, j) = dataArray[i][j] * 256;
        }
    }
    //数据转换为CV_8U格式；
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
//从文件中读取地震数据
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
        //这里可以在循环中写入新文件道头数据
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
//地震数据转换函数
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
//数据高低位转换
int Qt_segy_process::swap4byte(int value)
{
    int svalue;
    svalue = ((value & 0xff000000) >> 24) | ((value & 0x00ff0000) >> 8) |
        ((value & 0x0000ff00) << 8) | ((value & 0x000000ff) << 24);
    return svalue;
}
//数据归一化
std::vector<std::vector<float>> Qt_segy_process::normalized(std::vector<std::vector<float>> matrix) {

    // 步骤 1: 找到最小值和最大值
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

    // 步骤 2: 归一化数据
    float newMin = 0.0f;  // 新的最小值
    float newMax = 1.0f;  // 新的最大值

    // 先对数据进行标准化
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
//数据标准化
std::vector<std::vector<float>> Qt_segy_process::normalizeColumns(std::vector<std::vector<float>> matrix) {

    int rows = matrix.size();
    int cols = matrix[0].size();

    // 对每一列进行标准化
    for (int j = 0; j < cols; ++j) {
        // 计算列的平均值
        float mean = std::accumulate(matrix.begin(), matrix.end(), 0.0, [j](float sum, const std::vector<float>& row) {
            return sum + row[j];
            }) / rows;

        // 计算列的标准差
        float sum_squared_diff = 0.0;
        for (int i = 0; i < rows; ++i) {
            sum_squared_diff += std::pow(matrix[i][j] - mean, 2);
        }
        float std_dev = std::sqrt(sum_squared_diff / rows);

        // 对列进行标准化
        for (int i = 0; i < rows; ++i) {
            matrix[i][j] = (matrix[i][j] - mean) / std_dev;
        }
    }

    return matrix; // 返回标准化后的矩阵
}
// 定义一个函数来进行矩阵转置
std::vector<std::vector<float>> Qt_segy_process::transposeMatrix(std::vector<std::vector<float>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<float>> transposed(cols, vector<float>(rows)); // 创建一个新的矩阵用于存储转置结果

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j]; // 进行转置操作
        }
    }

    return transposed;
}
// 函数返回最小值或最大值
float  Qt_segy_process::findMinMaxValue(const std::vector<std::vector<float>>& matrix, int flag) {
    if (matrix.empty() || matrix[0].empty()) {
        std::cerr << "矩阵为空，无法找到最小和最大值。" << std::endl;
        return 0.0; // 返回默认值
    }

    float result = matrix[0][0];

    for (const std::vector<float>& row : matrix) {
        for (float value : row) {
            if (flag == 0) { // 查找最小值
                if (value < result) {
                    result = value;
                }
            }
            else if (flag == 1) { // 查找最大值
                if (value > result) {
                    result = value;
                }
            }
            else {
                std::cerr << "无效的标志值，应为0或1。" << std::endl;
                return 0.0; // 返回默认值
            }
        }
    }

    return result;
}
//dataarray2image
cv::Mat Qt_segy_process::dataArray2image(std::vector<std::vector<float>> dataArray) {
    cv::Mat image_temp(dataArray.size(), dataArray[0].size(), CV_8U);//获取到二维数组的行和列；

    for (int i = 0; i < dataArray.size(); ++i) {
        for (int j = 0; j < dataArray[i].size(); ++j) {
            // 假设 dataArray 的元素是 [0, 1] 范围内的浮点数
            image_temp.at<uchar>(i, j) = dataArray[i][j] * 256;
        }
    }
    return image_temp;
    ui.statusBar->showMessage(tr("dataarray2image complete!"), 3000);
}
// 滑动窗口Function to calculate the root mean square (RMS) of a vector
float Qt_segy_process::calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize) {
    float sum = 0.0f;
    for (int i = std::max(0, row - windowSize / 2); i < std::min(static_cast<int>(data.size()), row + windowSize / 2 + 1); ++i) {
        for (int j = std::max(0, col - windowSize / 2); j < std::min(static_cast<int>(data[0].size()), col + windowSize / 2 + 1); ++j) {
            sum += data[i][j] * data[i][j];
        }
    }
    return std::sqrt(sum / (windowSize * windowSize));
}
//AGC//agc2d,滑动窗口计算能量
void Qt_segy_process::dataArrayAGC() {//自适应增益控制
    ///判断 
    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    //std::vector<std::vector<float>>& data, int windowSize, float k
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);
    ///调整数值
    if (dataarray_agc.empty()){
        return ;
    }

    windows_size_value->setMinimum(1);
    //windows_size_value->setValue(dataarray_agc.size() / 2) ;
    windows_size_value->setMaximum(dataarray_agc.size());
    //int windowSize = 3; 
    int window_size = windows_size_value->value();//设定滑动窗口的大小
    ///判断
    if (dataarray_agc.empty()) {

        QString message = QString("empty!");
        ui.statusBar->showMessage(message);
        ui.statusBar->setStyleSheet("color:red;font-size=20px;");
        return ;
    }
    
    /////判断最大值最小值是否小于1
    //float minValue = findMinMaxValue(dataarray_agc, 0);
    //float maxValue = findMinMaxValue(dataarray_agc, 1);//获取

    //if (minValue >-1 || maxValue <1)
    //{
    //    for (int i = 0; i < dataarray_agc.size(); ++i) {
    //        for (int j = 0; j < dataarray_agc[i].size(); ++j) {
    //            dataarray_agc[i][j] = dataarray_agc[i][j] / abs(minValue);
    //        }
    //    }
    //}
    //dataarray_agc = Exc_min(dataarray_agc);///切除极小值

std::vector<std::vector<float>> agc_result;

int num_traces = dataarray_agc[0].size();//获取道数 
 ///start****************************************
for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//根据单道的计算规则计算二维数据
    
    vector<float> data;//存储单道数据空间
    data.reserve(dataarray_agc.size());
    for (int i = 0; i < dataarray_agc.size(); i++) {//获取指定i的单道数据

        data.push_back(dataarray_agc[i][data_tracei]);//得到一维向量data
    }
    // 计算数据的平方
    std::vector<float> squared_data;
    squared_data.reserve(data.size());
    for (const auto& value : data) {
        if (std::pow(value, 2)< 1e-30) {

            squared_data.push_back(std::pow(value, 2) + 1e-30);
        }
        else {
            squared_data.push_back(std::pow(value, 2) );
        }
        //单点值的平方。小数变小；
    }
    // 使用滑动窗口计算每个窗口内的平均能量
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
    //const float threshold = 1e-6; /// 设置一个阈值，根据实际情况调整
    //// agc缩放，根据，当前窗口能量大小进行
    //for (int i = 0; i < data.size(); ++i) {
    //    // 检查计算结果是否小于阈值
    //    if (std::abs(data[i] / std::sqrt(sliding_mean[i])) < threshold) {
    //        agc_data[i] = 0.0; // 替换为零
    //    }
    //    else {
    //        agc_data[i] = data[i] / std::sqrt(sliding_mean[i]);
    //    }
    //}
    // Store the result for this trace
    agc_result.push_back(agc_data);//这里矩阵的方向变了，需要变回去
}
///end****************************************
    std::vector<std::vector<float>> temp;
    agc_result = transposeMatrix(agc_result);//转置

    temp = agc_result;//增益过后的数据,数据存储用
    agc_save_data = agc_result;
    //agc_save_data = temp;

    //temp = normalizeColumns(temp);
    temp = normalized(temp);//这里归一化后，模拟数据出现问题，需要改进。
    src= dataArray2image(temp);

    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));

    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // 显示colorMap
    QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
    ui.statusBar->showMessage(message, 10000);//显示10秒

    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口

}
///单道数据agc
void Qt_segy_process::trace_i_agc() {

    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);//函数内部

    if (dataarray_agc.empty()) {
        return;
    }
    vector<float> data;//存储单道数据空间

    agc_trace_i->setMaximum(dataarray_agc[0].size());//设置最大道数

    windows_size_value->setMinimum(1);//设置窗口最小值
    //windows_size_value->setValue(dataarray_agc.size() / 2);
    windows_size_value->setMaximum(dataarray_agc.size());//设置最大窗口长度

    int data_tracei = agc_trace_i->value();

    int window_size = windows_size_value->value();//设定滑动窗口的大小
    //int data_tracei = data_trace_i->value();
    ///开始
    //const float threshold = 1e-6; /// 设置一个阈值，防止数据过小
    //// agc缩放，根据，当前窗口能量大小进行
    //for (int i = 0; i < dataarray_agc.size(); ++i) {
    //    for(int j = 0; j < dataarray_agc.size(); ++j){
    //            if (dataarray_agc[i][j] < threshold) {
    //                dataarray_agc[i][j] = 0.0; // 替换为零
    //            }
    //    }

    //}
    for (int i = 0; i < dataarray_agc.size(); i++) {//获取指定i的单道数据

        data.push_back(dataarray_agc[i][data_tracei]);//得到一维向量data
    }
    // 计算数据的平方
    std::vector<float> squared_data;
    squared_data.reserve(data.size());
    for (const auto& value : data) {
        if (std::pow(value, 2) < 1e-30) {

            squared_data.push_back(std::pow(value, 2) + 1e-30);///加上极小值，防止数据丢失
        }
        else {
            squared_data.push_back(std::pow(value, 2));
        }
        //单点值的平方。小数变小；
    }
    // 使用滑动窗口计算每个窗口内的平均能量
    std::vector<float> sliding_mean(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        for (int j = std::max(0, i - window_size / 2); j <= std::min(static_cast<int>(data.size()) - 1, i + window_size / 2); ++j) {
            sliding_mean[i] += squared_data[j];
        }
        sliding_mean[i] /= window_size;
    }
    // agc缩放，根据，当前窗口能量大小进行
    std::vector<float> agc_data(data.size(), 0.0);
    for (int i = 0; i < data.size(); ++i) {
        agc_data[i] = data[i] / std::sqrt(sliding_mean[i]);
    }
    
    //数据显示部分
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();

    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (int i = 0; i < agc_data.size(); ++i) {
        series->append(i, agc_data[i]);
    }
    chart->addSeries(series);

    // 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // 设置坐标轴标签
    axisX->setTitleText("sample number");
    axisY->setTitleText("orignal_Ampli");

    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将系列关联到坐标轴
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

    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (size_t i = 0; i < data.size(); ++i) {
        series2->append(i, data[i]);
    }
    chart2->addSeries(series2);

    // 创建坐标轴
    QValueAxis* axisX1 = new QValueAxis;
    QValueAxis* axisY1 = new QValueAxis;

    // 设置坐标轴标签
    axisX1->setTitleText("sample number");
    axisY1->setTitleText("after_agc_Ampli");


    font.setPointSize(20);  // 设置字体大小
    axisX1->setTitleFont(font);
    axisY1->setTitleFont(font);

    // 将坐标轴添加到 QChart 中
    chart2->addAxis(axisX1, Qt::AlignBottom);
    chart2->addAxis(axisY1, Qt::AlignLeft);

    // 将系列关联到坐标轴
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
///agc保存
void  Qt_segy_process::save_AGC_segy() {
    /// Write the 2D vector to the output file
    std::ofstream fileout;
    QString SaveFile_segy = QFileDialog::getSaveFileName(this,//对话框得到存储路径
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

    dataArray_save = agc_save_data;//将需要存储的数据传入
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
///切除极小值，防止数据超出范围
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
//计算一维数据的频谱
void Qt_segy_process::opencv_fft_1d() {

    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    vector<float> data;//存储单道数据空间

    float sampling = fft_sample_rate->value();
    fft_sample_rate->setMaximum(100000);
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//取出要处理的segy数据

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());

    int data_tracei = data_trace_i->value();
    for (int i = 0; i < dataarray_fft.size(); i++) {//获取指定i的单道数据

        data.push_back(dataarray_fft[i][data_tracei]);
    }

    cv::Mat Data = cv::Mat(data);//数据转换为mat格式
    cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
    cv::Mat planes_true1 = cv::Mat_<float>(Data);
    cv::Mat Y1;
    merge(planes1, 2, Y1);
    dft(Y1, Y1);//傅里叶变换结果为复数.通道1存的是实部, 通道2存的是虚部
    split(Y1, planes1); // plannes[0]=Re(DFT(I))即实部,plannes[1]=Im(DFT(I))即虚部
    std::vector<float> amplite_Re;
    amplite_Re = planes1[0];//cv::Mat转为vector
    std::vector<float> amplite_Im;
    amplite_Im = planes1[1];

    std::vector<float>Ampli; //保存频率幅度值
    std::vector<float>Freq; //保存对应频率值
    int L_freq = floor(data.size() / 2);
    for (int k = 1; k < L_freq + 1; k++)
    {
        float ampli = sqrt(pow(amplite_Re[k-1], 2) + pow(amplite_Im[k-1], 2)) / L_freq;
        Ampli.push_back(ampli);//FFT幅值

        float freq = ((float)sampling) / data.size() * k;
        Freq.push_back(freq);//频率值
    }

    QString message = QString("vector fft completed!");
    ui.statusBar->showMessage(message);

    /*QString message2 = QString("data %1").arg(Freq[5]);
    ui.statusBar->showMessage(message2);*/
    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();

    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (size_t i = 0; i < Freq.size(); ++i) {
        series->append(Freq[i],Ampli[i]);
    }
    chart->addSeries(series);

    // 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // 设置坐标轴标签
    axisX->setTitleText("Freq");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将系列关联到坐标轴
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
//计算二维数据的频谱并显示
void Qt_segy_process::opencv_fft2d() {
    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    fft_sample_rate->setMaximum(100000);//函数内部设置采样率最大值
    float sampling = fft_sample_rate->value();
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//取出要处理的segy数据

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());//设置最大道数
    std::vector<std::vector<float>> fft_result_freq;//存储频率
    std::vector<std::vector<float>> fft_result_amp;//存储频率对应的幅值
    int num_traces = dataarray_fft[0].size();//获取道数 
    ///初始化数据
    
    for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//根据单道的计算规则计算二维数据

        std::vector<float> amplite_Re;
        std::vector<float> amplite_Im;
        std::vector<float>Ampli; //保存频率幅度值
        std::vector<float>Freq; //保存对应频率值
        vector<float> data;//存储单道数据空间//放在循环外边，push_back，一维放在后面，出问题，放在循环里面进行更新；
        data.reserve(dataarray_fft.size());

        for (int i = 0; i < dataarray_fft.size(); i++) {//获取指定i的单道数据

            data.push_back(dataarray_fft[i][data_tracei]);
        }
        
        cv::Mat Data = cv::Mat(data);//数据转换为mat格式
        cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
        cv::Mat planes_true1 = cv::Mat_<float>(Data);
        cv::Mat Y1;
        merge(planes1, 2, Y1);
        dft(Y1, Y1);//傅里叶变换结果为复数.通道1存的是实部, 通道2存的是虚部
        split(Y1, planes1); // plannes[0]=Re(DFT(I))即实部,plannes[1]=Im(DFT(I))即虚部

        amplite_Re = planes1[0];//cv::Mat转为vector
        amplite_Im = planes1[1];
       
        int L_freq = floor(data.size() / 2);
        for (int k = 1; k < L_freq + 1; k++)
        {
            float ampli = sqrt(pow(amplite_Re[k-1], 2) + pow(amplite_Im[k-1], 2)) / L_freq;
            Ampli.push_back(ampli);//FFT幅值

            float freq = ((float)sampling) / data.size() * k;
            Freq.push_back(freq);//一维频率值
        }
        // Store the result for this trace
        fft_result_freq.push_back(Freq);//这里矩阵的方向变了，需要变回去
        fft_result_amp.push_back(Ampli);
    }


    fft_result_freq = transposeMatrix(fft_result_freq);//方向调整，按道显示；
    fft_result_amp = transposeMatrix(fft_result_amp);

    fft_result_freq = normalized(fft_result_freq);
    fft_result_amp = normalized(fft_result_amp);

    Mat show_image_freq(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//创建mat数组；
    Mat show_image_amp(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//创建mat数组

    show_image_freq = dataArray2image(fft_result_freq);
    show_image_amp = dataArray2image(fft_result_amp);

    cv::namedWindow("fft2d_freq", cv::WINDOW_NORMAL);
    cv::imshow("fft2d_freq", show_image_freq); // 显示colorMap

    cv::namedWindow("fft2d_amp", cv::WINDOW_NORMAL);
    cv::imshow("fft2d_amp", show_image_amp); // 显示colorMap
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口


    QString message = QString("image completed! row %1 ;clo %2;").arg(fft_result_freq.size()).arg(fft_result_freq[0].size());
    ui.statusBar->showMessage(message);

    ///单道显示
    //QChartView* ChartView_widget = new QChartView();
    //QChart* chart = new QChart();
    //QSplineSeries* series = new QSplineSeries();

    //for (size_t i = 0; i < fft_result_freq.size(); ++i) {
    //    series->append(i, fft_result_freq[i][3]);   
    //}
    //chart->addSeries(series);
    //ChartView_widget->setChart(chart);
    //ChartView_widget->show();
    ///取消Qchart显示

    /*QString message2 = QString("data %1").arg(Freq[5]);
    ui.statusBar->showMessage(message2);*/
    /////QChartView
    //QChartView* ChartView_widget = new QChartView();
    //QChart* chart = new QChart();
    //// 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    //QSplineSeries* series = new QSplineSeries();

    //for (size_t i = 0; i < fft_result_freq.size(); ++i) {
    //    
    //    for (size_t j = 0; j < fft_result_freq[0].size(); ++j) {

    //    series->append(fft_result_freq[i][j],fft_result_amp[i][j]);
    //    }
    //    
    //}
    //chart->addSeries(series);
    //// 创建坐标轴
    //QValueAxis* axisX = new QValueAxis;
    //QValueAxis* axisY = new QValueAxis;

    //// 设置坐标轴标签
    //axisX->setTitleText("Freq");
    //axisY->setTitleText("Ampli");

    //QFont font;
    //font.setPointSize(20);  // 设置字体大小
    //axisX->setTitleFont(font);
    //axisY->setTitleFont(font);

    //// 将坐标轴添加到 QChart 中
    //chart->addAxis(axisX, Qt::AlignBottom);
    //chart->addAxis(axisY, Qt::AlignLeft);

    //// 将系列关联到坐标轴
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
//计算所有地震道的频谱chart显示
void Qt_segy_process::chart_fftshow() {//绘制出每一道，比较耗时
    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    fft_sample_rate->setMaximum(100000);//函数内部设置采样率最大值
    float sampling = fft_sample_rate->value();
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(dataArray_real);//取出要处理的segy数据

    if (dataarray_fft.empty()) {
        return;
    }
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_fft[0].size());//设置最大道数
    std::vector<std::vector<float>> fft_result_freq;//存储频率
    std::vector<std::vector<float>> fft_result_amp;//存储频率对应的幅值
    int num_traces = dataarray_fft[0].size();//获取道数 
    ///初始化数据
    for (int data_tracei = 0; data_tracei < num_traces; ++data_tracei) {//根据单道的计算规则计算二维数据

        std::vector<float> amplite_Re;
        std::vector<float> amplite_Im;
        std::vector<float>Ampli; //保存频率幅度值
        std::vector<float>Freq; //保存对应频率值
        vector<float> data;//存储单道数据空间//放在循环外边，push_back，一维放在后面，出问题，放在循环里面进行更新；
        data.reserve(dataarray_fft.size());

        for (int i = 0; i < dataarray_fft.size(); i++) {//获取指定i的单道数据

            data.push_back(dataarray_fft[i][data_tracei]);
        }

        cv::Mat Data = cv::Mat(data);//数据转换为mat格式
        cv::Mat planes1[] = { cv::Mat_<float>(Data), cv::Mat::zeros(Data.size(), CV_32F) };
        cv::Mat planes_true1 = cv::Mat_<float>(Data);
        cv::Mat Y1;
        merge(planes1, 2, Y1);
        dft(Y1, Y1);//傅里叶变换结果为复数.通道1存的是实部, 通道2存的是虚部
        split(Y1, planes1); // plannes[0]=Re(DFT(I))即实部,plannes[1]=Im(DFT(I))即虚部

        amplite_Re = planes1[0];//cv::Mat转为vector
        amplite_Im = planes1[1];

        int L_freq = floor(data.size() / 2);
        for (int k = 1; k < L_freq + 1; k++)
        {
            float ampli = sqrt(pow(amplite_Re[k - 1], 2) + pow(amplite_Im[k - 1], 2)) / L_freq;
            Ampli.push_back(ampli);//FFT幅值

            float freq = ((float)sampling) / data.size() * k;
            Freq.push_back(freq);//一维频率值
        }
        // Store the result for this trace
        fft_result_freq.push_back(Freq);//这里矩阵的方向变了，需要变回去
        fft_result_amp.push_back(Ampli);
    }
    ///chart 多道显示
    fft_result_freq = transposeMatrix(fft_result_freq);//方向调整，按道显示；
    fft_result_amp = transposeMatrix(fft_result_amp);

    //fft_result_freq = normalized(fft_result_freq);
    //fft_result_amp = normalized(fft_result_amp);

    //Mat show_image_freq(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//创建mat数组；
    //Mat show_image_amp(fft_result_freq.size(), fft_result_freq[0].size(), CV_8U);//创建mat数组

    //show_image_freq = dataArray2image(fft_result_freq);
    //show_image_amp = dataArray2image(fft_result_amp);

    //cv::namedWindow("fft2d_freq", cv::WINDOW_NORMAL);
    //cv::imshow("fft2d_freq", show_image_freq); // 显示colorMap

    //cv::namedWindow("fft2d_amp", cv::WINDOW_NORMAL);
    //cv::imshow("fft2d_amp", show_image_amp); // 显示colorMap
    //waitKey(0);
    //cv::destroyAllWindows(); // 关闭所有OpenCV窗口
    QString message = QString("image completed! row %1 ;clo %2;").arg(fft_result_freq.size()).arg(fft_result_freq[0].size());
    ui.statusBar->showMessage(message);

    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    QSplineSeries* series = new QSplineSeries();

    for (size_t i = 0; i < fft_result_freq.size(); ++i) {

        for (size_t j = 0; j < fft_result_freq[0].size(); ++j) {

            series->append(fft_result_freq[i][j], fft_result_amp[i][j]);
        }

    }
    chart->addSeries(series);
    // 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // 设置坐标轴标签
    axisX->setTitleText("Freq");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将系列关联到坐标轴
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
//显示数据表格
void Qt_segy_process::matrix_table_show() {

    if (dataArray_real.empty()) {//先判断数据是否初始化
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
    return;
    }
    ///加载数据
    std::vector<std::vector<float>> matrix = transposeMatrix(dataArray_real);///原始数据是按照样本道，row显示；
    // 创建 QTableWidget
    QTableWidget* tableWidget = new QTableWidget;
    tableWidget->setMinimumSize(600, 400);
    // 设置表格的行数和列数
    tableWidget->setRowCount(matrix.size());
    tableWidget->setColumnCount(matrix[0].size());
    // 填充表格数据
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[row].size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            tableWidget->setItem(row, col, item);
        }
    }
    // 显示表格
    tableWidget->show();
    /*QWidget* wid1 = new QWidget();
    wid1->setMinimumSize(600, 400);
    wid1->show();*/
}
//wiggle显示地震数据horizontal direction
void Qt_segy_process::WiggleView_show_H() {

    ui.statusBar->setStyleSheet("background-color:orange");
    std::vector<std::vector<float>> matrix;
    if (dataArray_real.empty()) 
    {//先判断数据是否初始化
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

    // 创建 QGraphicsView 和 QGraphicsScene
    QGraphicsView* wiggleView = new QGraphicsView();
    wiggleView->setWindowTitle("WiggleView_show_H");
    QGraphicsScene* scene = new QGraphicsScene();

    /*wiggleView->setFixedSize(matrix.size(), matrix[0].size());*/

// 设置绘图参数
    int traceHeight = 20;//每道的高度
    int traceSpacing = 10;//道之间间距
    int sampleSpacing = 1;//采样点之间间距
    // 设置 Wiggle 图颜色
    QPen wigglePen;
    wigglePen.setColor(Qt::black);  // 设置颜色为红色
    wigglePen.setWidth(2);
    for (size_t i = 0; i < matrix.size(); ++i) {
        const std::vector<float>& trace = matrix[i];//取出每一行
        // 考虑地震道之间的垂直间隔
        float verticalOffset = i * traceSpacing;
        // 根据地震数据绘制路径
        for (size_t j = 1; j < trace.size(); ++j) {
            // 使用QGraphicsLineItem显示路径
            QGraphicsLineItem* lineItem = new QGraphicsLineItem();
            // 设置线条颜色
            lineItem->setPen(wigglePen);

            // 使用 verticalOffset 调整地震道的垂直位置
            lineItem->setLine((j - 1) * sampleSpacing, -trace[j - 1] * traceHeight + verticalOffset,
                j * sampleSpacing, -trace[j] * traceHeight + verticalOffset);
            scene->addItem(lineItem);
        }
    }
    // 设置场景大小
    scene->setSceneRect(scene->itemsBoundingRect());
    // 将场景设置给 QGraphicsView
    wiggleView->setScene(scene);
    //// 设置视图大小
    //wiggleView->setFixedSize(800, 600);

    // 显示 QGraphicsView
    wiggleView->show();
}
//wiggle显示地震数据vertical direction
void Qt_segy_process::WiggleView_show_V() {
        ui.statusBar->setStyleSheet("background-color:orange");
        //判断数据
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
        //设置控件调整显示；
        QVBoxLayout* wiggle_main_layout = new QVBoxLayout(wiggle_widget);

        QWidget* wiggle_widget1 = new QWidget();
        QWidget* wiggle_widget2 = new QWidget();
        QWidget* wiggle_widget3 = new QWidget();

        QHBoxLayout* wiggle_widget1_layout = new QHBoxLayout(wiggle_widget1);
        QHBoxLayout* wiggle_widget2_layout = new QHBoxLayout(wiggle_widget2);
        QHBoxLayout* wiggle_widget3_layout = new QHBoxLayout(wiggle_widget3);

        wiggle_main_layout->addWidget(wiggle_widget1);
        wiggle_main_layout->addWidget(wiggle_widget2);//添加三层
        wiggle_main_layout->addWidget(wiggle_widget3);

        // 创建 s四个QDial 控件
        //traceSpacing = wiggle_dial_1->value();//道间距
        //sampleSpacing = wiggle_dial_2->value();//采样点间距
        //traceHeight = wiggle_dial_3->value();//每道高度，最大值
        //line_width_wiggle = wiggle_dial_4->value();//wiggle线宽
        wiggle_dial_1 = new QDial();
        wiggle_dial_1->setNotchesVisible(true);
        wiggle_dial_1->setRange(1, 50); wiggle_dial_1->setSingleStep(1); wiggle_dial_1->setValue(10);//设置初始值
        label_dial_1 =new QLabel("1");
        label_dial_1->setAlignment(Qt::AlignHCenter);

        wiggle_dial_2 = new QDial();
        wiggle_dial_2->setRange(1, 5);  wiggle_dial_2->setSingleStep(1);wiggle_dial_2->setValue(1);//设置初始值
        wiggle_dial_2->setNotchesVisible(true);
        label_dial_2 = new QLabel("2");
        label_dial_2->setAlignment(Qt::AlignHCenter);

        wiggle_dial_3 = new QDial();
        wiggle_dial_3->setNotchesVisible(true);
        wiggle_dial_3->setRange(0, 100);  wiggle_dial_3->setSingleStep(1); wiggle_dial_3->setValue(20);//设置初始值
        label_dial_3 = new QLabel("3");
        label_dial_3->setAlignment(Qt::AlignHCenter);

        wiggle_dial_4 = new QDial();
        wiggle_dial_4->setNotchesVisible(true);
        wiggle_dial_4->setRange(1, 10);  wiggle_dial_4->setSingleStep(1); wiggle_dial_4->setValue(1);//设置初始值
        label_dial_4 = new QLabel("4");
        label_dial_4->setAlignment(Qt::AlignHCenter);

        /// 创建 QGraphicsView 和 QGraphicsScene
        wiggleView = new QGraphicsView();
        wiggleView->setWindowTitle("WiggleView_show_V");
        QGraphicsScene* scene = new QGraphicsScene();
        // 设置背景颜色或者网格纹理
        QBrush backgroundBrush(Qt::white);  // 设置为白色背景，也可以使用纹理或其他颜色
        scene->setBackgroundBrush(backgroundBrush);
        // 设置绘图参数
        int traceHeight = 20;//每道的高度
        int traceSpacing = 10;//道之间间距
        int sampleSpacing = 1;//采样点之间间距
        // 设置 Wiggle 图颜色
        QPen wigglePen;
        wigglePen.setColor(Qt::black);  // 设置颜色为红色
        wigglePen.setWidth(1);
        for (size_t i = 0; i < matrix.size(); ++i) {
            const std::vector<float>& trace = matrix[i];//取出每一行
            // 考虑地震道之间的垂直间隔
            float HOffset = i * traceSpacing;
            // 根据地震数据绘制路径
            for (size_t j = 1; j < trace.size(); ++j) {
                // 使用QGraphicsLineItem显示路径
                QGraphicsLineItem* lineItem = new QGraphicsLineItem();
                // 设置线条颜色
                lineItem->setPen(wigglePen);
                // 使用 HOffset 调整地震道的垂直位置
                lineItem->setLine(-trace[j - 1] * traceHeight + HOffset, (j - 1) * sampleSpacing ,
                    -trace[j] * traceHeight + HOffset,j * sampleSpacing  );
                scene->addItem(lineItem);
            }
        }
        // 设置场景大小
        scene->setSceneRect(scene->itemsBoundingRect());
        // 将场景设置给 QGraphicsView
        wiggleView->setScene(scene);
        //// 设置视图大小
        //wiggleView->setFixedSize(800, 600);
        // 启用鼠标滚轮缩放
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setInteractive(true);
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        //wiggleView->setRenderHint(QPainter::HighQualityAntialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setDragMode(QGraphicsView::ScrollHandDrag);

        // 重新实现鼠标滚轮事件处理函数
        wiggleView->viewport()->installEventFilter(this);
        // 显示 QGraphicsView
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

        //将dial与参数联系，更新图像；
        connect(wiggle_dial_1, SIGNAL(valueChanged(int)), this, SLOT(Dial_1_ValueChanged(int)));
        connect(wiggle_dial_2, SIGNAL(valueChanged(int)), this, SLOT(Dial_2_ValueChanged(int)));
        connect(wiggle_dial_3, SIGNAL(valueChanged(int)), this, SLOT(Dial_3_ValueChanged(int)));
        connect(wiggle_dial_4, SIGNAL(valueChanged(int)), this, SLOT(Dial_4_ValueChanged(int)));

    }
//更新回调函数
void Qt_segy_process::updataWigglePlot() {
        /*ui.statusBar->setStyleSheet("background-color:orange");*/
        //判断数据
        std::vector<std::vector<float>> matrix;
        if (dataArray_real.empty()) {
            ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
            ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
            return;
        }
        matrix = dataArray_real;
        matrix = normalized(matrix);
        /// 创建 QGraphicsView 和 QGraphicsScene
        //wiggleView = new QGraphicsView();
        wiggleView->setWindowTitle("WiggleView_show_V");
        QGraphicsScene* scene = new QGraphicsScene();
        // 设置背景颜色或者网格纹理
        QBrush backgroundBrush(Qt::white);  // 设置为白色背景，也可以使用纹理或其他颜色
        scene->setBackgroundBrush(backgroundBrush);
        // 设置绘图参数
        traceHeight = 20;//每道的高度
        //int traceSpacing = 10;//道之间间距
        sampleSpacing = 1;//采样点之间间距
        line_width_wiggle = 1;
        traceSpacing= wiggle_dial_1->value();//道间距
        sampleSpacing = wiggle_dial_2->value();//采样点间距
        traceHeight = wiggle_dial_3->value();//每道高度，最大值
        line_width_wiggle = wiggle_dial_4->value();//wiggle线宽


        // 设置 Wiggle 图颜色
        QPen wigglePen;
        wigglePen.setColor(Qt::black);  // 设置颜色为红色
        wigglePen.setWidth(line_width_wiggle);
        for (size_t i = 0; i < matrix.size(); ++i) {
            const std::vector<float>& trace = matrix[i];//取出每一行
            // 考虑地震道之间的垂直间隔
            float HOffset = i * traceSpacing;
            // 根据地震数据绘制路径
            for (size_t j = 1; j < trace.size(); ++j) {
                // 使用QGraphicsLineItem显示路径
                QGraphicsLineItem* lineItem = new QGraphicsLineItem();
                // 设置线条颜色
                lineItem->setPen(wigglePen);
                // 使用 HOffset 调整地震道的垂直位置
                lineItem->setLine(-trace[j - 1] * traceHeight + HOffset, (j - 1) * sampleSpacing,
                    -trace[j] * traceHeight + HOffset, j * sampleSpacing);
                scene->addItem(lineItem);
            }
        }
        // 设置场景大小
        scene->setSceneRect(scene->itemsBoundingRect());
        // 将场景设置给 QGraphicsView
        wiggleView->setScene(scene);
        //// 设置视图大小
        //wiggleView->setFixedSize(800, 600);
        // 启用鼠标滚轮缩放
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setInteractive(true);
        wiggleView->setRenderHint(QPainter::Antialiasing, true);
        //wiggleView->setRenderHint(QPainter::HighQualityAntialiasing, true);
        wiggleView->setRenderHint(QPainter::SmoothPixmapTransform, true);
        wiggleView->setDragMode(QGraphicsView::ScrollHandDrag);

        // 重新实现鼠标滚轮事件处理函数
        wiggleView->viewport()->installEventFilter(this);
        // 显示 QGraphicsView
        wiggleView->show();
}
//保存QGraphicsView* view图像
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
//保存wiggle图像
void Qt_segy_process::saveWiggle_1() {
    // Check if wiggleView is created successfully
    if (isWiggleViewCreated) {
        // 检查 wiggleView 是否包含内容
        if (wiggleView != nullptr && !wiggleView->scene()->items().isEmpty()) {
            // wiggleView 中有内容
            saveWiggleViewImage(wiggleView);
        }
        else {
            // wiggleView 中没有内容
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
//将agc的数据转换到dataarray中，调换
void Qt_segy_process::agcdata2dataarray() {
    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    if (agc_save_data.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr(" please load the agc data first."), 3000);
        return;
    }
    dataArray_real = transposeMatrix(agc_save_data);

    QString message = QString("AGC loaded! Trace simple %1 ;Trace number %2;").arg(agc_save_data.size()).arg(agc_save_data[0].size());
    ui.statusBar->showMessage(message);
}
//从原始路径中获取原始数据
void Qt_segy_process::get_orignal_real() {
    std::string filePath = OpenFile_segy.toStdString();//get file_path
    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";
        ui.statusBar->showMessage(QString("no file selected! Please open a file first"));
        return;
    }
    dataArray = getsegyarray(filePath);
    dataArray_real = dataArray;//二维向量格式，row为地震道;
    QString message = QString("Real data loaded! Trace simple %1 ;Trace number %2;").arg(dataArray_real.size()).arg(dataArray_real[0].size());
    ui.statusBar->showMessage(message);
}
//dial改变wiggle参数
void Qt_segy_process::Dial_1_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_1->value()), 3000);
    updataWigglePlot();
    label_dial_1->setText(QString("trace space Value: %1").arg(wiggle_dial_1->value()));//更新标签数值
}
void Qt_segy_process::Dial_2_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_2->value()), 3000);
    updataWigglePlot();
    label_dial_2->setText(QString("height Value: %1").arg(wiggle_dial_2->value()));//更新标签数值
} 
void Qt_segy_process::Dial_3_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_3->value()), 3000);
    updataWigglePlot();
    label_dial_3->setText(QString("max Value: %1").arg(wiggle_dial_3->value()));//更新标签数值
}
void Qt_segy_process::Dial_4_ValueChanged(int value) {
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(QString("dial updata:%1").arg(wiggle_dial_4->value()), 3000);
    updataWigglePlot();
    label_dial_4->setText(QString("line width Value: %1").arg(wiggle_dial_4->value()));//更新标签数值
    label_dial_4->setText(QString("line width Value: %1").arg(wiggle_dial_4->value()));//更新标签数值
}
//wiggle中鼠标移动事件重绘
bool Qt_segy_process::eventFilter(QObject* obj, QEvent* event) {//鼠标滚轮缩放
    if (obj == wiggleView->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        int delta = wheelEvent->angleDelta().y();
        qreal factor = 1.2; // 调整缩放因子
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
//3d绘图
void Qt_segy_process::draw3DData() {
    if (dataArray_real.empty()) {//先判断数据是否初始化
    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
    return;
}
    QWidget* data_3d = new QWidget();
    data_3d->setMinimumSize(800, 600);
    // 创建 Q3DScatter
    Q3DScatter* scatter = new Q3DScatter();
    // 添加3D散点系列
    QScatter3DSeries* series = new QScatter3DSeries;
    series->setItemLabelFormat(QStringLiteral("(@xLabel @yLabel @zLabel)"));
    series->setMesh(QAbstract3DSeries::MeshSphere);
    series->setMeshSmooth(true);

    // 添加数据
    QScatterDataArray data;
    std::vector<std::vector<float>> matrixData;
    dataArray = normalized(dataArray_real);
    matrixData = dataArray_real;
    // 将 matrixData 转换为 QVector<QVector3D>
    for (int i = 0; i < dataArray_real.size(); ++i) {
        for (int j = 0; j < dataArray_real[i].size(); ++j) {

            data << QVector3D( i, j, matrixData[i][j]);
        }
    }
    series->dataProxy()->addItems(data);
    scatter->addSeries(series);
    // 设置坐标轴
    scatter->axisX()->setTitle(QStringLiteral("X Axis-trace"));
    scatter->axisY()->setTitle(QStringLiteral("Y Axis-sample"));
    scatter->axisZ()->setTitle(QStringLiteral("Z Axis-value"));
    //设置坐标轴范围
    /////判断最大值最小值是否小于1
    //float minValue = findMinMaxValue(dataArray, 0);
    //float maxValue = findMinMaxValue(dataArray, 1);//获取
    //scatter->axisX()->setRange(0, dataArray.size());
    //scatter->axisY()->setRange(0, dataArray[0].size());
    //scatter->axisZ()->setRange(minValue, maxValue);  // minZValue 和 maxZValue 是你的数据中 Z 值的最小和最大值
    //scatter->activeTheme()->setType(Q3DTheme::ThemeQt);
    // 设置视角
    scatter->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    // 设置布局
   // 使用 QPointer 或者 QVBoxLayout 添加 Q3DScatter
    QPointer<QWidget> scatterContainer = QWidget::createWindowContainer(scatter);
    QVBoxLayout* layout = new QVBoxLayout(data_3d);
    layout->addWidget(scatterContainer);

    data_3d->show();
}
//S变换
void Qt_segy_process::SF_function() {

    if (dataArray.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    vector<double> s;//存储单道数据空间
    // 生成时间序列 t
    vector<double> t;

    int data_tracei = 80;

    for (int i = 0; i < dataArray.size(); i++) {//获取指定i的单道数据

        s.push_back(dataArray[i][data_tracei]);//得到一维向量data
    }
    double dt = 0.001;
    int time_len = s.size();
    for (int i = 0; i < time_len; i++) {
        t.push_back(i * dt);
    }
    // 检查数据
    if (t.empty() || s.empty() || t.size() != s.size()) {
        cerr << "Error: Invalid input data." << endl;
        return ; // 或者采取其他合适的处理方式
    }
    for (double time : t) {
        // 以正弦波为例，频率为10 Hz，振幅为1
        double signal = sin(2 * M_PI * 10 * time);
        s.push_back(signal);
    }
    double freqlow = 1.0;
    double freqhigh = 1000.0;
    double alpha = 1.0;

    // 计算S变换
    vector<vector<complex<double>>> data_s = st(t, s, freqlow, freqhigh, alpha);

    // 获取第一个元素的实部
    double realPart = data_s[0][0].real();

    // 也可以遍历整个二维向量
    for (const auto& row : data_s) {
        for (const auto& elem : row) {
            double elemReal = elem.real();
            // 在这里使用 elemReal
        }
    }

        // 遍历整个二维向量并打印实部
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


    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//灰度图
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // 显示colorMap
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口

    

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
//绘制曲线
void Qt_segy_process::drawcurve()
{
    QChart *chart = new QChart();

    QChartView* chartview = new QChartView();

    QSplineSeries* series = new QSplineSeries();


    for (int i = 0; i <= 100; i ++){ 
        series->append(i, i*i); 
    }
        
    //添加坐标轴
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();

    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("XXX");
    axisY->setTitleText("YYY");
    axisX->setTickCount(11);//设置刻度数量
    axisY->setTickCount(11);
    chart->addAxis(axisX, Qt::AlignBottom);//设置位置
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

    //设置音频采样格式
    QAudioFormat formatAudio;
    formatAudio.setSampleRate(20000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleFormat(QAudioFormat::UInt8);
    //判断采样格式是否支持
    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    if (!info.isFormatSupported(formatAudio)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }
    else {
        ui.statusBar->showMessage(" format ok");
    }
    //设置音频源
    audio = new QAudioSource(inputDevice, formatAudio, this);
    
    QBuffer audiodata;

    audio->start();
    QTimer::singleShot(3000, this, &Qt_segy_process::stopRecording);
    //
    // 此处需要存储audio数据
    //
    //// 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    // 设置坐标轴标签
    axisX->setTitleText("time");
    axisY->setTitleText("Ampli");

    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    axisX->setRange(0, 100);
    axisY->setRange(0, 100);

    // 将系列关联到坐标轴
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

    //数据
    QScatterSeries* series1 = new QScatterSeries();
    series1->setName("scatter");
    for (int i = angularMin; i <= angularMax; i += 10)
        series1->append(i, (i / radialMax) * radialMax + 8.0);

    //模型
    QPolarChart* chart = new QPolarChart();
    chart->addSeries(series1);

    //轴
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

    //最后加载到视图上

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}
void Qt_segy_process::PolarChart2() {
    
    //const qreal angularMin = -100;
    //const qreal angularMax = 100;

    //const qreal radialMin = -100;
    //const qreal radialMax = 100;
    //模型
    QPolarChart* chart = new QPolarChart();
    
    //数据
    //QScatterSeries* series1 = new QScatterSeries();
    //series1->setName("scatter");
    //for (int i = angularMin; i <= angularMax; i += 10)
    //    series1->append(i, (i / radialMax) * radialMax + 8.0);

    QLineSeries* series = new QLineSeries();//线性
    series->setPen(QPen(QColor(Qt::blue)));
    for (int i = 0; i <= 100; i++) {
        series->append(i / 100.0 * 360.0, qSin(i / 100.0 * M_PI * 6) * 2);
    }
    QAreaSeries* series4 = new QAreaSeries();//区域
    series4->setUpperSeries(series);
    series4->setPen(QPen(QColor(255, 150, 20, 0)));
    series4->setBrush(QColor(255, 150, 20, 60));
    
    //chart->addSeries(series1);
    chart->addSeries(series);
    chart->addSeries(series4);
    //轴
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
    //最后加载到视图上
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}
//toolbar显示version
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

    QTextEdit* textEdit1 = new QTextEdit();///放置信息
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
    //状态栏变化
    ui.statusBar->setStyleSheet(style_info.styleSheet_bar);
    QString message = QString("The window has opened.Information has been shown");
    ui.statusBar->showMessage(message);

    ///slot
    connect(info_close, SIGNAL(clicked()), this, SLOT(closeVersionInfo()));//槽函数内部实现关闭;
}
void Qt_segy_process::closeVersionInfo() {
    widget_info->close();
}
///数据定义
//std::vector<std::vector<float>> dataarray

///获取单道数据
//for (int i = 0; i < dataarray_agc.size(); i++) {//获取指定i的单道数据
//
//    data.push_back(dataarray_agc[i][data_tracei]);//得到一维向量data
//}
///获取二维数据
//for (int i = 0; i < dataArray.size(); ++i) {
//    for (int j = 0; j < dataArray[i].size(); ++j) {
//         dataArray[i][j]=0
//    }
//}
///QChartView绘图
//QChartView* ChartView_widget = new QChartView();
//QChart* chart = new QChart();
//QSplineSeries* series = new QSplineSeries();
//
//// 将 std::vector<float> 中的数据添加到 QSplineSeries 中
//for (size_t i = 0; i < Freq.size(); ++i) {
//    series->append(Freq[i], Ampli[i]);
//}
//chart->addSeries(series);
//
//// 创建坐标轴
//QValueAxis* axisX = new QValueAxis;
//QValueAxis* axisY = new QValueAxis;
//
//// 设置坐标轴标签
//axisX->setTitleText("Freq");
//axisY->setTitleText("Ampli");
//
//QFont font;
//font.setPointSize(20);  // 设置字体大小
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//
//// 将坐标轴添加到 QChart 中
//chart->addAxis(axisX, Qt::AlignBottom);
//chart->addAxis(axisY, Qt::AlignLeft);
//
//// 将系列关联到坐标轴
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
///判断数据是否为空
//if (dataArray_real.empty()) {//先判断数据是否初始化
//
//    ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
//    ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
//    return;
//}
///状态栏显示消息
//ui.statusBar->showMessage(QString("disk location:%1").arg(OpenFile_segy), 3000);
//QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
//ui.statusBar->showMessage(message);
//
//QString message = QString("support");
//ui.statusBar->showMessage(message);
///新建按钮
//QPushButton* Page4_button = new QPushButton("page4_button");//open
//Page4_button->setStyleSheet(style1.button_save_style1);
//Page4_button->setMinimumSize(80, 40);
//right_layout->addWidget(Page4_button);
///新建调节数值部件
//data_trace_i = new QSpinBox();//调节fft_sample_rate数值
//data_trace_i->setToolTip("<html><font size='5' color='lightgreen'>QSpinBox</font></html>");
//data_trace_i->setMinimum(0);
//data_trace_i->setValue(500);
//data_trace_i->setMaximumWidth(200);
//data_trace_i->setMaximumHeight(50);
//data_trace_i->setStyleSheet("background-color:rgb(200,200,200)");
//page2_widget3_layout->addWidget(data_trace_i);//设置层布局
///数据转换为图片在cv窗口显示
//std::vector<std::vector<float>> temp;
//temp = dataarray;//增益过后的数据,数据存储用
//temp = normalized(temp);
//src = dataArray2image(temp);
//
//QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//灰度图
//label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
//
//cv::namedWindow("AGC", cv::WINDOW_NORMAL);
//cv::imshow("AGC", src); // 显示colorMap
//waitKey(0);
//cv::destroyAllWindows(); // 关闭所有OpenCV窗口
//
//QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
//ui.statusBar->showMessage(message);
///cv图片颜色转换
//applyColorMap(image, colorMap, cv::COLORMAP_OCEAN); // 使用Jet颜色映射，你可以选择其他映射
////COLORMAP_JET：Jet颜色映射，它是最常见的伪彩色映射之一，通常用于表示热度。
////COLORMAP_RAINBOW：彩虹颜色映射，用于表示连续数据的不同级别。
////COLORMAP_HOT：Hot颜色映射，用于表示热度，通常用于温度数据。
////COLORMAP_COOL：Cool颜色映射，用于表示温度，通常从冷到热的温度变化。
////COLORMAP_SPRING：Spring颜色映射，用于表示温度或温度变化。
////COLORMAP_SUMMER：Summer颜色映射，用于表示季节或温度。
////COLORMAP_AUTUMN：Autumn颜色映射，用于表示季节或温度。
////COLORMAP_WINTER：Winter颜色映射，用于表示季节或温度。
////COLORMAP_OCEAN：Ocean颜色映射，通常用于表示海洋或水的深度。
////COLORMAP_PINK：Pink颜色映射，通常用于表示连续数据的不同级别。
////COLORMAP_HOT：Jet颜色映射，它是最常见的伪彩色映射之一，通常用于表示热度*
//
//imshow("colormap", colorMap);
///显示一维数据
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
///一维数据绘制曲线
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
////添加坐标轴
//QValueAxis* axisX = new QValueAxis();
//QValueAxis* axisY = new QValueAxis();
//
//QFont font;
//font.setPointSize(20);  // 设置字体大小
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//axisX->setTitleText("XXX");
//axisY->setTitleText("YYY");
//axisX->setTickCount(11);//设置刻度数量
//axisY->setTickCount(11);
//chart->addAxis(axisX, Qt::AlignBottom);//设置位置
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
