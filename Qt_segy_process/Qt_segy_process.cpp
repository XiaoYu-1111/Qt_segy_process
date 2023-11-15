#include "Qt_segy_process.h"
#include"style.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QString>
#include<QTextEdit>

#include <fstream>
#include <cstring>
#include<cmath>
#include <vector>
#include <algorithm> 


using namespace cv;
using namespace std;

Qt_segy_process::Qt_segy_process(QWidget *parent)
    : QMainWindow(parent)
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

    QPushButton* Page2_button = new QPushButton("page2_button");//open
    Page2_button->setStyleSheet(style1.button_save_style1);
    Page2_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page2_button);

    QPushButton* Page3_button = new QPushButton("page3_button");//open
    Page3_button->setStyleSheet(style1.button_save_style1);
    Page3_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page3_button);

    QPushButton* Page4_button = new QPushButton("page4_button");//open
    Page4_button->setStyleSheet(style1.button_save_style1);
    Page4_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page4_button);

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
    textEdit1->setPlainText("version_1.0");


    //page2
    QVBoxLayout* page2_layout = new QVBoxLayout(page2);

    QWidget* page2_widget1 = new QWidget();
    QWidget* page2_widget2 = new QWidget();
    QWidget* page2_widget3 = new QWidget();

    QHBoxLayout* page2_widget1_layout = new QHBoxLayout(page2_widget1);
    QHBoxLayout* page2_widget2_layout = new QHBoxLayout(page2_widget2);
    QHBoxLayout* page2_widget3_layout = new QHBoxLayout(page2_widget3);

    page2_widget1->setMaximumHeight(100);
    page2_widget2->setMaximumHeight(100);
    page2_widget3->setMaximumHeight(100);

    page2_layout->addWidget(page2_widget1);
    page2_layout->addWidget(page2_widget2);
    page2_layout->addWidget(page2_widget3);


    page2_widget1->setStyleSheet("background-color:rgb(100,100,100);");
    page2_widget2->setStyleSheet("background-color:rgb(100,100,100);");
    page2_widget3->setStyleSheet("background-color:rgb(100,100,100);");
    ///page2_widget1
    QPushButton* button_AGC = new QPushButton("AGC");
    button_AGC->setStyleSheet(style1.button_save_style1);
    button_AGC->setMaximumSize(200, 50);
    page2_widget1_layout->addWidget(button_AGC);

    windows_size_value = new QSpinBox();//调节windows_size数值
    windows_size_value->setToolTip("<html><font size='5' color='lightgreen'>This is iterations</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    windows_size_value->setMaximumWidth(200);
    windows_size_value->setMaximumHeight(50);

    windows_size_value->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget1_layout->addWidget(windows_size_value);

    QPushButton* AGC_save = new QPushButton("AGC_save");
    AGC_save->setStyleSheet(style1.button_save_style1);
    AGC_save->setMaximumSize(200, 50);
    page2_widget1_layout->addWidget(AGC_save);


    ///page2_widget2
    QPushButton* button_filter = new QPushButton("filter");
    page2_widget2_layout->addWidget(button_filter);
    button_filter->setMaximumSize(200, 50);
    button_filter->setStyleSheet(style1.button_save_style1);

    ///page2_widget3
    QPushButton* button_fft = new QPushButton("FFT");
    page2_widget3_layout->addWidget(button_fft);
    button_fft->setMaximumSize(200, 50);
    button_fft->setStyleSheet(style1.button_save_style1);

    fft_sample_rate = new QDoubleSpinBox();//调节fft_sample_rate数值
    fft_sample_rate->setToolTip("<html><font size='5' color='lightgreen'>set sample rate!</font></html>");
    fft_sample_rate->setMinimum(1);
    fft_sample_rate->setValue(500);
    fft_sample_rate->setMaximum(1000);
    fft_sample_rate->setMaximumWidth(200);
    fft_sample_rate->setMaximumHeight(50);
    fft_sample_rate->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget3_layout->addWidget(fft_sample_rate);

    data_trace_i = new QSpinBox();//调节fft_sample_rate数值
    data_trace_i->setToolTip("<html><font size='5' color='lightgreen'>set data_trace_i !</font></html>");
    data_trace_i->setMinimum(0);
    data_trace_i->setValue(500);
    data_trace_i->setMaximumWidth(200);
    data_trace_i->setMaximumHeight(50);
    data_trace_i->setStyleSheet("background-color:rgb(200,200,200)");
    page2_widget3_layout->addWidget(data_trace_i);

    QPushButton* button_fft_show = new QPushButton("FFT_show");
    page2_widget3_layout->addWidget(button_fft_show);
    button_fft_show->setMaximumSize(200, 50);
    button_fft_show->setStyleSheet(style1.button_save_style1);


    ///function connect
    connect(button_AGC, SIGNAL(clicked()), this, SLOT(dataArrayAGC()));
    connect(AGC_save, SIGNAL(clicked()), this, SLOT(save_AGC_segy()));
    ///fft1
    connect(button_fft, SIGNAL(clicked()), this, SLOT(opencv_fft()));//一维傅里叶变换


    connect(button_fft_show, SIGNAL(clicked()), this, SLOT(chart_fftshow()));

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

    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image); // 显示原始图像

    cv::namedWindow("colorMap", cv::WINDOW_NORMAL);
    cv::imshow("colorMap", colorMap); // 显示colorMap

    //cv::namedWindow("Resized", cv::WINDOW_NORMAL);
    //cv::imshow("Resized", resized); // 显示调整后的图像

    float minValue = findMinMaxValue(dataArray_real, 0); // 查找最小值
    float maxValue = findMinMaxValue(dataArray_real, 1); // 查找最大值

    QString message = QString("Min Value: %1, Max Value: %2").arg(minValue).arg(maxValue);
    ui.statusBar->showMessage(message);
    //主页面显示数据
    src = image;
    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口
    /*textEdit1->setText("dataArray_real");*/
    textEdit1->append(tr("dataArray_real:trace simple:%1 ;trace number %2").arg(dataArray.size()).arg(dataArray[0].size()));

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
std::vector<std::vector<float>> Qt_segy_process::normalized(std::vector<std::vector<float>> dataArray) {

    // 步骤 1: 找到最小值和最大值
    float minValue = dataArray[0][0];
    float maxValue = dataArray[0][0];

    for (int i = 0; i < dataArray.size(); ++i)
    {
        for (int j = 0; j < dataArray[i].size(); ++j)
        {
            if (dataArray[i][j] < minValue)
                minValue = dataArray[i][j];
            if (dataArray[i][j] > maxValue)
                maxValue = dataArray[i][j];
        }
    }

    // 步骤 2: 归一化数据
    float newMin = 0.0f;  // 新的最小值
    float newMax = 1.0f;  // 新的最大值

    for (int i = 0; i < dataArray.size(); ++i)
    {
        for (int j = 0; j < dataArray[i].size(); ++j)
        {
            float dataValue = dataArray[i][j];
            float normalizedValue = (dataValue - minValue) / (maxValue - minValue) * (newMax - newMin) + newMin;
            dataArray[i][j] = normalizedValue;
        }
    }
    return dataArray;
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

// Function to calculate the root mean square (RMS) of a vector
float Qt_segy_process::calculateRMS(const std::vector<std::vector<float>>& data, int row, int col, int windowSize) {
    float sum = 0.0f;
    for (int i = std::max(0, row - windowSize / 2); i < std::min(static_cast<int>(data.size()), row + windowSize / 2 + 1); ++i) {
        for (int j = std::max(0, col - windowSize / 2); j < std::min(static_cast<int>(data[0].size()), col + windowSize / 2 + 1); ++j) {
            sum += data[i][j] * data[i][j];
        }
    }
    return std::sqrt(sum / (windowSize * windowSize));
}
//AGC//agc没有做完，现在返回的是rms值
void Qt_segy_process::dataArrayAGC() {//自适应增益控制
    
    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    //std::vector<std::vector<float>>& data, int windowSize, float k
    float k = 2.0f;
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);
    std::vector<std::vector<float>> dataarray_agc_rms;
    ///调整数值
    if (dataarray_agc.empty()){
        return ;
    }

    windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataarray_agc.size());

    //int windowSize = 3;
    int windowSize = windows_size_value->value();
    

    if (dataarray_agc.empty()) {

        QString message = QString("empty!");
        ui.statusBar->showMessage(message);
        ui.statusBar->setStyleSheet("color:red;font-size=20px;");
        return ;
    }
    else {
        QString message = QString("OK!");
        ui.statusBar->showMessage(message);
    }

    int numRows = static_cast<int>(dataarray_agc.size());
    int numCols = static_cast<int>(dataarray_agc[0].size());

    // 计算每个时间窗口的均方根值并应用AGC
    for (int i = 0; i < numRows; ++i) {
        
        vector<float> row;
        for (int j = 0; j < numCols; ++j) {
            float rms = calculateRMS(dataarray_agc, i, j, windowSize);
            row.push_back(rms);
            dataarray_agc[i][j] = rms;
            dataarray_agc_rms.push_back(row);//vector需要push_back
        }
    }
    if (windowSize > dataarray_agc.size()) {

        QString message = QString("too much!");
        ui.statusBar->showMessage(message);
        ui.statusBar->setStyleSheet("color:red;font-size=20px;");
        return ;
    }

    std::vector<std::vector<float>> temp;
    temp = dataarray_agc;//增益过后的数据,数据存储用

    agc_save_data = temp;

    temp = normalized(temp);
    src= dataArray2image(temp);

    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));

    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // 显示colorMap
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口

    QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
    ui.statusBar->showMessage(message);

}

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
//计算一维数据的频谱

void Qt_segy_process::opencv_fft() {

    if (dataArray_real.empty()) {//先判断数据是否初始化

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    
    vector<float> data;//存储单道数据空间
    

    float sampling = fft_sample_rate->value();
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
        float ampli = sqrt(pow(amplite_Re[k], 2) + pow(amplite_Im[k], 2)) / L_freq;
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
    chart->setTitle("CV_algorithm_FFT");
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);

    ChartView_widget->show();
}

void Qt_segy_process::chart_fftshow() {

    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();

    for (float i = 0; i < 100; i++) {

        series->append(i, sin(0.5 * i));
    }

    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle("test ignore");
    chart->setTheme(QChart::ChartThemeDark);

    ChartView_widget->setChart(chart);
    ChartView_widget->show();
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
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_agc[0].size());

    int data_tracei = data_trace_i->value();
    for (int i = 0; i < dataarray_agc.size(); i++) {//获取指定i的单道数据

        data.push_back(dataarray_agc[i][data_tracei]);//得到一维向量data
    }


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
///数据转换为图片显示
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