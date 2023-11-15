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

    windows_size_value = new QSpinBox();//����windows_size��ֵ
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

    fft_sample_rate = new QDoubleSpinBox();//����fft_sample_rate��ֵ
    fft_sample_rate->setToolTip("<html><font size='5' color='lightgreen'>set sample rate!</font></html>");
    fft_sample_rate->setMinimum(1);
    fft_sample_rate->setValue(500);
    fft_sample_rate->setMaximum(1000);
    fft_sample_rate->setMaximumWidth(200);
    fft_sample_rate->setMaximumHeight(50);
    fft_sample_rate->setStyleSheet("background-color:rgb(180,180,180)");
    page2_widget3_layout->addWidget(fft_sample_rate);

    data_trace_i = new QSpinBox();//����fft_sample_rate��ֵ
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
    connect(button_fft, SIGNAL(clicked()), this, SLOT(opencv_fft()));//һά����Ҷ�任


    connect(button_fft_show, SIGNAL(clicked()), this, SLOT(chart_fftshow()));

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

    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image); // ��ʾԭʼͼ��

    cv::namedWindow("colorMap", cv::WINDOW_NORMAL);
    cv::imshow("colorMap", colorMap); // ��ʾcolorMap

    //cv::namedWindow("Resized", cv::WINDOW_NORMAL);
    //cv::imshow("Resized", resized); // ��ʾ�������ͼ��

    float minValue = findMinMaxValue(dataArray_real, 0); // ������Сֵ
    float maxValue = findMinMaxValue(dataArray_real, 1); // �������ֵ

    QString message = QString("Min Value: %1, Max Value: %2").arg(minValue).arg(maxValue);
    ui.statusBar->showMessage(message);
    //��ҳ����ʾ����
    src = image;
    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����
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
std::vector<std::vector<float>> Qt_segy_process::normalized(std::vector<std::vector<float>> dataArray) {

    // ���� 1: �ҵ���Сֵ�����ֵ
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

    // ���� 2: ��һ������
    float newMin = 0.0f;  // �µ���Сֵ
    float newMax = 1.0f;  // �µ����ֵ

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
//AGC//agcû�����꣬���ڷ��ص���rmsֵ
void Qt_segy_process::dataArrayAGC() {//����Ӧ�������
    
    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    //std::vector<std::vector<float>>& data, int windowSize, float k
    float k = 2.0f;
    std::vector<std::vector<float>> dataarray_agc = transposeMatrix(dataArray_real);
    std::vector<std::vector<float>> dataarray_agc_rms;
    ///������ֵ
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

    // ����ÿ��ʱ�䴰�ڵľ�����ֵ��Ӧ��AGC
    for (int i = 0; i < numRows; ++i) {
        
        vector<float> row;
        for (int j = 0; j < numCols; ++j) {
            float rms = calculateRMS(dataarray_agc, i, j, windowSize);
            row.push_back(rms);
            dataarray_agc[i][j] = rms;
            dataarray_agc_rms.push_back(row);//vector��Ҫpush_back
        }
    }
    if (windowSize > dataarray_agc.size()) {

        QString message = QString("too much!");
        ui.statusBar->showMessage(message);
        ui.statusBar->setStyleSheet("color:red;font-size=20px;");
        return ;
    }

    std::vector<std::vector<float>> temp;
    temp = dataarray_agc;//������������,���ݴ洢��

    agc_save_data = temp;

    temp = normalized(temp);
    src= dataArray2image(temp);

    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));

    cv::namedWindow("AGC", cv::WINDOW_NORMAL);
    cv::imshow("AGC", src); // ��ʾcolorMap
    waitKey(0);
    cv::destroyAllWindows(); // �ر�����OpenCV����

    QString message = QString("AGC completed! Trace simple %1 ;Trace number %2;").arg(dataarray_agc.size()).arg(dataarray_agc[0].size());
    ui.statusBar->showMessage(message);

}

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
//����һά���ݵ�Ƶ��

void Qt_segy_process::opencv_fft() {

    if (dataArray_real.empty()) {//���ж������Ƿ��ʼ��

        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    
    vector<float> data;//�洢�������ݿռ�
    

    float sampling = fft_sample_rate->value();
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
        float ampli = sqrt(pow(amplite_Re[k], 2) + pow(amplite_Im[k], 2)) / L_freq;
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
    //int data_tracei = 30;
    data_trace_i->setMaximum(dataarray_agc[0].size());

    int data_tracei = data_trace_i->value();
    for (int i = 0; i < dataarray_agc.size(); i++) {//��ȡָ��i�ĵ�������

        data.push_back(dataarray_agc[i][data_tracei]);//�õ�һά����data
    }


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
///����ת��ΪͼƬ��ʾ
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