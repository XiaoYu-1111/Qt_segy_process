#include "Qt_segy_process.h"
#include"style.h"

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QString>
#include<QTextEdit>

#include <iostream>
#include <fstream>//header cpp std;
#include <cstring>
#include<cmath>
#include <vector>
#include <numeric>
#include <complex>
#include <algorithm> 

using namespace cv;
using namespace std;

Qt_segy_process::Qt_segy_process(QWidget *parent)
    : QMainWindow(parent), isWiggleViewCreated(false)
{
    ui.setupUi(this);
    this->setWindowTitle("QT-SEGY-processing software");
    
    stylesheet_QT style1;
    ui.centralWidget->setStyleSheet(style1.widget_gray1);
    this->setStyleSheet(style1.widget_gray1);
    this->setContentsMargins(0, 0, 0, 0);
    ui.centralWidget->setContentsMargins(0, 0, 0, 0);
    ui.centralWidget->setMinimumSize(900,500);
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
    main_center_Widget->setStyleSheet(style1.widget_gray1);
    main_right_Widget->setStyleSheet(style1.widget_gray1);

    main_left_Widget->setMinimumWidth(150);
    main_left_Widget->setMaximumWidth(200);
    main_center_Widget->setMinimumWidth(400);
    main_right_Widget->setMinimumWidth(150);
    main_right_Widget->setMaximumWidth(200);
#pragma region //左侧窗口
    //左侧窗口
    QVBoxLayout* left_layout = new QVBoxLayout(main_left_Widget);


    QLabel* main_label = new QLabel("SEGY-DATA");
    QPushButton* main_button = new QPushButton("MAIN");
    main_button->setText(QString::fromLocal8Bit("主页面"));
    
    left_layout->addWidget(main_label);
    left_layout->addWidget(main_button);

    main_button->setStyleSheet(style1.button_main);//main
    main_button->setToolTip("<html><font size='5' color='lightgreen'>MAIN PAGE</font></html>");
    main_button->setMinimumSize(80, 40);
    main_label->setAlignment(Qt::AlignCenter);
    main_label->setStyleSheet(style1.label1);
    main_label->setMaximumSize(200, 50);

    QPushButton* open_button = new QPushButton("open_file");//open
    open_button->setText(QString::fromLocal8Bit("打开文件"));
    open_button->setStyleSheet(style1.button_main);
    open_button->setMinimumSize(80, 40);
    left_layout->addWidget(open_button);

    QPushButton* show_button = new QPushButton("show_data");//show
    show_button->setText(QString::fromLocal8Bit("显示"));
    show_button->setStyleSheet(style1.button_main);
    show_button->setMinimumSize(80, 40);
    left_layout->addWidget(show_button);

    QPushButton* save_picture_button = new QPushButton("save_picture");//save
    save_picture_button->setText(QString::fromLocal8Bit("保存图片"));
    save_picture_button->setStyleSheet(style1.button_main);
    save_picture_button->setMinimumSize(80, 40);
    left_layout->addWidget(save_picture_button);

    QPushButton* save_button = new QPushButton("save_data");//save
    save_button->setText(QString::fromLocal8Bit("保存文件"));
    save_button->setStyleSheet(style1.button_main);
    save_button->setMinimumSize(80, 40);
    left_layout->addWidget(save_button);
#pragma endregion
#pragma region //右侧窗口
    //右侧窗口
    QVBoxLayout* right_layout = new QVBoxLayout(main_right_Widget);

    QPushButton* Page1_button = new QPushButton("page1_button");//open
    Page1_button->setText(QString::fromLocal8Bit("页面1"));
    Page1_button->setStyleSheet(style1.button_main);
    Page1_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page1_button);

    QPushButton* Page2_button = new QPushButton("2D_process");//open
    Page2_button->setText(QString::fromLocal8Bit("2D处理"));
    Page2_button->setStyleSheet(style1.button_main);
    Page2_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page2_button);

    QPushButton* Page3_button = new QPushButton("2D Page");//open
    Page3_button->setText(QString::fromLocal8Bit("2D显示"));
    Page3_button->setStyleSheet(style1.button_main);
    Page3_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page3_button);

    QPushButton* Page4_button = new QPushButton("Page4");//open
    Page4_button->setText(QString::fromLocal8Bit("3D显示"));
    Page4_button->setStyleSheet(style1.button_main);
    Page4_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page4_button);

    QPushButton* Page5_button = new QPushButton("page5");//open
    Page5_button->setText(QString::fromLocal8Bit("页面5"));
    Page5_button->setStyleSheet(style1.button_main);
    Page5_button->setMinimumSize(80, 40);
    right_layout->addWidget(Page5_button);
#pragma endregion
#pragma region //中间窗口
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
    page1->setStyleSheet(style1.widget_gray1);//21界面样式设置
    page2->setStyleSheet(style1.widget_glass);//22界面样式设置
    page3->setStyleSheet(style1.widget_glass);//23界面样式设置
    page4->setStyleSheet(style1.widget_glass);//24界面样式设置
    page5->setStyleSheet(style1.widget_glass);//25界面样式设置

    //主页面槽函数
    connect(open_button, SIGNAL(clicked()), this, SLOT(open_segy()));//打开文件
    connect(show_button, SIGNAL(clicked()), this, SLOT(show_segy()));//打开文件
    connect(save_picture_button, SIGNAL(clicked()), this, SLOT(save_segy_picture()));//打开文件
    connect(save_button, SIGNAL(clicked()), this, SLOT(save_segy()));//打开文件
    //跳转页面
    connect(main_button, SIGNAL(clicked()), this, SLOT(main_page()));// 切换到主页
    connect(Page1_button, SIGNAL(clicked()), this, SLOT(on_stackpage1_change_clicked()));// 切换到第一页
    connect(Page2_button, SIGNAL(clicked()), this, SLOT(on_stackpage2_change_clicked()));// 切换到第二页
    connect(Page3_button, SIGNAL(clicked()), this, SLOT(on_stackpage3_change_clicked()));// 切换到第三页
    connect(Page4_button, SIGNAL(clicked()), this, SLOT(on_stackpage4_change_clicked()));// 切换到第四页
    connect(Page5_button, SIGNAL(clicked()), this, SLOT(on_stackpage5_change_clicked()));
#pragma endregion
    ///toolbar部分
    //part1
    ui.mainToolBar->setWindowTitle("My Main Toolbar");
    QFont menuFont;
    menuFont.setPointSize(15); // Set the desired font size
    QAction* myAction1 = new QAction("Main", this);//主动作行为
    myAction1->setText(QString::fromLocal8Bit("主页"));
    // 创建下拉菜单并添加格子选项
    QMenu* myMenu = new QMenu(this);//一号菜单
    QMenu* myMenu2 = new QMenu(this);//二号菜单
    QAction* option1Action = new QAction("Open file", this);//一号菜单action
    option1Action->setText(QString::fromLocal8Bit("打开文件"));
    myMenu->addAction(option1Action);
    QAction* open_segy = new QAction("open_segy", this);//子菜单
    QAction* show_data = new QAction("show data", this);//子菜单
    QAction* open_csv_action = new QAction("open_csv", this);//子菜单
    option1Action->setFont(menuFont);
    open_segy->setFont(menuFont);
    show_data->setFont(menuFont);
    open_csv_action->setFont(menuFont);

    myMenu->addAction(show_data);//子菜单行为
    myMenu->addAction("add");
    myMenu2->addAction(open_segy);
    myMenu2->addAction(open_csv_action);
    // 将下拉菜单关联到动作
    myAction1->setMenu(myMenu);
    option1Action->setMenu(myMenu2);
    ui.mainToolBar->addAction(myAction1);
    ///part1slot
    connect(open_segy, SIGNAL(triggered()), this, SLOT(open_segy()));
    connect(show_data, SIGNAL(triggered()), this, SLOT(show_segy()));
    connect(open_csv_action, SIGNAL(triggered()), this, SLOT(open_csv()));
    //part data change//part2
    QAction* myAction_datachange = new QAction("Data", this);
    myAction_datachange->setText(QString::fromLocal8Bit("内容"));
    QMenu* datachange_menu = new QMenu(this);
    QAction* option1_agcdata2dataarray = new QAction("Agc2data", this);
    QAction* option1_get_realdata = new QAction("Get_realdata", this);
    QAction* option1_csv2dataarray = new QAction("csv2dataarray", this);
    datachange_menu->addAction(option1_agcdata2dataarray);
    datachange_menu->addAction(option1_get_realdata);
    datachange_menu->addAction(option1_csv2dataarray);
    myAction_datachange->setMenu(datachange_menu);

    option1_agcdata2dataarray->setFont(menuFont);
    option1_get_realdata->setFont(menuFont);
    option1_csv2dataarray->setFont(menuFont);
    ui.mainToolBar->addAction(myAction_datachange);
    ui.mainToolBar->setStyleSheet(style1.tool_bar);
    //part view
    QAction* Action_View = new QAction("View", this);//创建View页面入口
    Action_View->setText(QString::fromLocal8Bit("显示"));
    QMenu* myMenu_View = new QMenu(this);//创建View菜单
    QAction* View_vwiggle = new QAction("View_Vwiggle", this);
    QAction* View_add = new QAction("view_other", this);
    View_vwiggle->setFont(menuFont);
    View_add->setFont(menuFont);
    myMenu_View->addAction(View_vwiggle);
    myMenu_View->addAction(View_add);
    Action_View->setMenu(myMenu_View);
    ui.mainToolBar->addAction(Action_View);//添加到toolbar
    //view slot
    connect(View_vwiggle, SIGNAL(triggered()), this, SLOT(WiggleView_show_V()));

    //part setting
    QAction* Action_Setting = new QAction("Setting", this);//创建Setting页面入口
    Action_Setting->setText(QString::fromLocal8Bit("设置"));
    QMenu* myMenu_Setting = new QMenu(this);//创建Setting菜单
    QAction* Setting_header = new QAction("Setting_header", this);
    QAction* Setting_stylesheet = new QAction("Setting_stylesheet", this);
    QAction* Setting_add = new QAction("Setting_other", this);
    Setting_header->setFont(menuFont);
    Setting_stylesheet->setFont(menuFont);
    Setting_add->setFont(menuFont);
    myMenu_Setting->addAction(Setting_header);
    myMenu_Setting->addAction(Setting_stylesheet);
    myMenu_Setting->addAction(Setting_add);
    Action_Setting->setMenu(myMenu_Setting);
    ui.mainToolBar->addAction(Action_Setting);//添加到toolbar
    //setting_slot
    connect(Setting_header, SIGNAL(triggered()), this, SLOT(setting_header()));
    connect(Setting_stylesheet, SIGNAL(triggered()), this, SLOT(changeAllStyles_widget()));

    //part_version
    QAction* myAction2 = new QAction("version", this);//创建version页面入口
    myAction2->setText(QString::fromLocal8Bit("版本"));
    QMenu* myMenu_version = new QMenu(this);//创建version菜单
    QAction* version_info = new QAction("version_info", this);
    myMenu_version->addAction(version_info);
    myMenu_version->addAction("option_2");
    version_info->setFont(menuFont);
    myAction2->setMenu(myMenu_version);
    ui.mainToolBar->addAction(myAction2);//添加到toolbar
    ///toolbar部分solt
    connect(version_info, SIGNAL(triggered()), this, SLOT(show_version_info()));
    connect(option1_agcdata2dataarray, SIGNAL(triggered()), this, SLOT(agcdata2dataarray()));
    connect(option1_get_realdata, SIGNAL(triggered()), this, SLOT(get_orignal_real()));
    connect(option1_csv2dataarray, SIGNAL(triggered()), this, SLOT(csvdata2dataarray()));
    ///statusbar
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
    ///page1
    QVBoxLayout* page1_layout = new QVBoxLayout(page1);
    label_picture = new QLabel;
    page1->setStyleSheet(style1.widget_gray1);
    // 加载图片并设置为 QLabel 的背景
    //QString  path="D:\\Code\\visual_code\\Open_Cv\\Qt_segy_process\\Qt_segy_process\\icon\\shuidi.jpg";  // 替换为你的图片路径
    //label_picture->setMinimumSize(600, 400);
    //Mat src = cv::imread(path.toStdString());
    //QImage qtImage(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888);
    //label_picture->setPixmap(QPixmap::fromImage(qtImage).scaled(label_picture->size()));
    QString widget_gray1 = "Seis Data<br>Processing";
    QString widget_gray2 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
                            "Software Developer<br>"
                            "Based on Cpp&Qt Designed by Rain!"
                            "</span>";
    QString combinedText = widget_gray1 + "<br>" + widget_gray2;
    label_picture->setStyleSheet(style1.label_main);
    label_picture->setText(QString("<html>%1</html>").arg(combinedText));
    label_picture->setMinimumSize(400, 300);
    label_picture->setAlignment(Qt::AlignCenter);
    page1_layout->addWidget(label_picture);
    ///第一页面下边窗口
    QWidget* page1_widget1 = new QWidget();
    QHBoxLayout* page1_widget1_layout = new QHBoxLayout(page1_widget1);
    page1_layout->addWidget(page1_widget1);
    page1_widget1->setStyleSheet(style1.widget_glass);
    page1_widget1->setMaximumHeight(100);
    textEdit1 = new QTextEdit();///放置信息
    textEdit1->setReadOnly(true);
    textEdit1->setStyleSheet(style1.textEdit);
    page1_widget1_layout->addWidget(textEdit1);
    textEdit1->setPlainText("version_1.0,author by rain!");
    ///dockwidget窗口
    dockWidget1 = new QDockWidget("Dock");
    dockWidget1->setStyleSheet(style1.dock_widget);
    dockWidget1->setMinimumWidth(50);
    dockWidget1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
    dockWidget1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QTextEdit* te1 = new QTextEdit();
    te1->setText(tr("This area can be used for taking notes."));
    te1->setStyleSheet(style1.dock_textEdit);
    dockWidget1->setWidget(te1);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget1);
    
    ///page2**************
    ///page2**************
    QVBoxLayout* page2_layout = new QVBoxLayout(page2);
    QSplitter* splitter_page2 = new QSplitter(Qt::Horizontal);
    page2_layout->addWidget(splitter_page2);
    QWidget* page2_left = new QWidget();
    QVBoxLayout* page2_left_layout = new QVBoxLayout(page2_left);//左边splitter
    //page2_left->setMinimumWidth(200);
    QWidget* page2_center = new QWidget();
    QVBoxLayout* page2_center_layout = new QVBoxLayout(page2_center);//中间splitter
    //page2_center->setMinimumWidth(200);
    QWidget* page2_right = new QWidget();
    QVBoxLayout* page2_right_layout = new QVBoxLayout(page2_right);//右边splitter
    //page2_right->setMinimumWidth(200);
    page2_left->setStyleSheet(style1.widget_gray1);
    page2_center->setStyleSheet(style1.widget_gray1);
    page2_right->setStyleSheet(style1.widget_gray1);

    splitter_page2->addWidget(page2_left);
    splitter_page2->addWidget(page2_center);
    splitter_page2->addWidget(page2_right);
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

    QLabel* page2_label_left = new QLabel("left splitter");
    page2_label_left->setText(QString::fromLocal8Bit("左窗"));
    page2_label_left->setMaximumSize(200, 50);
    page2_label_left->setStyleSheet(style1.label1);
    page2_label_left->setAlignment(Qt::AlignCenter);
    page2_left_layout->addWidget(page2_label_left);

    page2_left_layout->addWidget(page2_widget1);//按照加进层的顺序排布
    page2_left_layout->addWidget(page2_widget3);//添加到左边splitter层
    /*page2_left_layout->addWidget(page2_widget2);*///先取消12.15
    page2_left_layout->addWidget(page2_widget4);

    page2_widget1->setStyleSheet(style1.widget_gray1);
    page2_widget2->setStyleSheet(style1.widget_gray1);
    page2_widget3->setStyleSheet(style1.widget_gray1);
    page2_widget4->setStyleSheet(style1.widget_gray1);
    ///page2_widget1
    QPushButton* AGC_single = new QPushButton("AGC_tracei");//1d
    AGC_single->setText(QString::fromLocal8Bit("增益1"));
    AGC_single->setStyleSheet(style1.button_15px);
    AGC_single->setMaximumSize(100, 50);
    page2_widget1_layout->addWidget(AGC_single);

    QPushButton* button_AGC = new QPushButton("AGC_2D");//2d
    button_AGC->setText(QString::fromLocal8Bit("增益2"));
    button_AGC->setStyleSheet(style1.button_15px);
    button_AGC->setMaximumSize(100, 50);
    page2_widget1_layout->addWidget(button_AGC);

    QLabel* windows_size = new QLabel("windows_size");
    windows_size->setText(QString::fromLocal8Bit("win-size"));
    windows_size->setMaximumSize(100, 50);
    windows_size->setStyleSheet(style1.label1);
    page2_widget1_layout->addWidget(windows_size);

    windows_size_value = new QSpinBox();//调节windows_size数值
    windows_size_value->setToolTip("<html><font size='5' color='lightgreen'>AGC windows size!</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    windows_size_value->setMaximumWidth(100);
    windows_size_value->setMaximumHeight(50);
    windows_size_value->setStyleSheet(style1.label1);
    page2_widget1_layout->addWidget(windows_size_value);

    QLabel* label_trace_i = new QLabel("trace i");//选择数据道
    label_trace_i->setText(QString::fromLocal8Bit("trace"));
    label_trace_i->setMaximumSize(100, 50);
    label_trace_i->setStyleSheet(style1.label1);
    page2_widget1_layout->addWidget(label_trace_i);

    agc_trace_i = new QSpinBox();//调节windows_size数值
    agc_trace_i->setToolTip("<html><font size='5' color='lightgreen'>AGC trace i!</font></html>");
    /*windows_size_value->setMinimum(1);
    windows_size_value->setMaximum(dataArray.size());*/
    agc_trace_i->setMaximumWidth(100);
    agc_trace_i->setMaximumHeight(50);
    agc_trace_i->setStyleSheet(style1.label1);
    page2_widget1_layout->addWidget(agc_trace_i);

    QPushButton* AGC_save = new QPushButton("AGC_save");//agc数据保存按钮
    AGC_save->setText(QString::fromLocal8Bit("保存文件"));
    AGC_save->setStyleSheet(style1.button_15px);
    AGC_save->setMaximumSize(200, 50);
    page2_widget1_layout->addWidget(AGC_save);
    ///page2_widget2
    QPushButton* button_fft = new QPushButton("FFT_1d");//傅里叶变换按钮
    button_fft->setText(QString::fromLocal8Bit("单道fft"));
    page2_widget3_layout->addWidget(button_fft);
    button_fft->setMaximumSize(200, 50);
    button_fft->setStyleSheet(style1.button_15px);

    QPushButton* button_fft_2d = new QPushButton("FFT_2d");
    button_fft_2d->setText(QString::fromLocal8Bit("多道fft"));
    page2_widget3_layout->addWidget(button_fft_2d);
    button_fft_2d->setMaximumSize(200, 50);
    button_fft_2d->setStyleSheet(style1.button_15px);

    QLabel* label_sample_rate = new QLabel("sample_rate");//采样率标签
    label_sample_rate->setText(QString::fromLocal8Bit("采样率"));
    label_sample_rate->setMaximumSize(100, 50);
    label_sample_rate->setStyleSheet(style1.label1);
    page2_widget3_layout->addWidget(label_sample_rate);

    fft_sample_rate = new QDoubleSpinBox();//调节fft_sample_rate数值
    fft_sample_rate->setToolTip("<html><font size='5' color='lightgreen'>set sample rate!</font></html>");
    //fft_sample_rate->setMinimum(1);
    //fft_sample_rate->setValue(500);
    /*fft_sample_rate->setMaximum(1000);*/
    fft_sample_rate->setMaximumWidth(200);
    fft_sample_rate->setMaximumHeight(50);
    fft_sample_rate->setStyleSheet(style1.label1);
    page2_widget3_layout->addWidget(fft_sample_rate);

    QLabel* label_tracei2 = new QLabel("trace i");///分割标签
    label_tracei2->setMaximumSize(100, 50);
    label_tracei2->setStyleSheet(style1.label1);
    page2_widget3_layout->addWidget(label_tracei2);

    data_trace_i = new QSpinBox();//调节data_trace_i数值
    data_trace_i->setToolTip("<html><font size='5' color='lightgreen'>set data_trace_i !</font></html>");
    /*data_trace_i->setMinimum(0);*/
    /*data_trace_i->setValue(500);*/
    data_trace_i->setMaximumWidth(200);
    data_trace_i->setMaximumHeight(50);
    data_trace_i->setStyleSheet(style1.label1);
    page2_widget3_layout->addWidget(data_trace_i);

    QPushButton* button_fft_show = new QPushButton("FFT_show");
    button_fft_show->setText(QString::fromLocal8Bit("显示"));
    page2_widget3_layout->addWidget(button_fft_show);
    button_fft_show->setMaximumSize(200, 50);
    button_fft_show->setStyleSheet(style1.button_15px);
    ///page2_widget3
    QPushButton* button_filter = new QPushButton("filter");
    page2_widget2_layout->addWidget(button_filter);
    button_filter->setMaximumSize(200, 50);
    button_filter->setStyleSheet(style1.button_15px);

    QPushButton* button_dynamic = new QPushButton("dynamic");
    page2_widget2_layout->addWidget(button_dynamic);
    button_dynamic->setMaximumSize(200, 50);
    button_dynamic->setStyleSheet(style1.button_15px);

    QPushButton* button_chart2 = new QPushButton("audio imput");
    page2_widget2_layout->addWidget(button_chart2);
    button_chart2->setMaximumSize(200, 50);
    button_chart2->setStyleSheet(style1.button_15px);

    QPushButton* button_polarchart = new QPushButton("polarchart");
    page2_widget2_layout->addWidget(button_polarchart);
    button_polarchart->setMaximumSize(200, 50);
    button_polarchart->setStyleSheet(style1.button_15px);

    QPushButton* button_polarchart2 = new QPushButton("polarchart2");
    page2_widget2_layout->addWidget(button_polarchart2);
    button_polarchart2->setMaximumSize(200, 50);
    button_polarchart2->setStyleSheet(style1.button_15px);
    //slot
    connect(button_filter, SIGNAL(clicked()), this, SLOT(drawcurve()));
    connect(button_dynamic, SIGNAL(clicked()), this, SLOT(draw_dynamic_curve()));
    connect(button_chart2, SIGNAL(clicked()), this, SLOT(draw_audio_curve2()));
    connect(button_polarchart, SIGNAL(clicked()), this, SLOT(PolarChart()));
    connect(button_polarchart2, SIGNAL(clicked()), this, SLOT(PolarChart2()));
    ///page2_widget4
    QPushButton* button_ST = new QPushButton("Stock_well(ST)");
    button_ST->setText(QString::fromLocal8Bit("标准ST"));
    page2_widget4_layout->addWidget(button_ST);
    button_ST->setMaximumSize(200, 50);
    button_ST->setStyleSheet(style1.button_15px);

    QPushButton* button_CWT = new QPushButton("CWT");
    button_CWT->setText(QString::fromLocal8Bit("小波变换"));
    page2_widget4_layout->addWidget(button_CWT);
    button_CWT->setMaximumSize(200, 50);
    button_CWT->setStyleSheet(style1.button_15px);

    QPushButton* button_STFT2 = new QPushButton("STFT");//未连接到槽函数
    button_STFT2->setText(QString::fromLocal8Bit("短时傅里叶变换"));
    page2_widget4_layout->addWidget(button_STFT2);
    button_STFT2->setMaximumSize(200, 50);
    button_STFT2->setStyleSheet(style1.button_15px);

    ///function connect
    connect(button_AGC, SIGNAL(clicked()), this, SLOT(dataArrayAGC()));
    connect(AGC_save, SIGNAL(clicked()), this, SLOT(save_AGC_segy()));
    connect(AGC_single, SIGNAL(clicked()), this, SLOT(trace_i_agc()));
    ///fft1
    connect(button_fft, SIGNAL(clicked()), this, SLOT(opencv_fft_1d()));//一维傅里叶变换
    connect(button_fft_2d, SIGNAL(clicked()), this, SLOT(opencv_fft2d()));//二维傅里叶变换
    connect(button_fft_show, SIGNAL(clicked()), this, SLOT(chart_fftshow()));
    ///SF_function
    connect(button_ST, SIGNAL(clicked()), this, SLOT(STOCK_function()));
    connect(button_CWT, SIGNAL(clicked()), this, SLOT(CWT_function()));
    connect(button_STFT2, SIGNAL(clicked()), this, SLOT(STFT_function()));
    
    ///page2_center
    QLabel* page2_label_center = new QLabel("center splitter");
    page2_label_center->setText(QString::fromLocal8Bit("中间窗"));
    page2_label_center->setMaximumSize(200, 50);
    page2_label_center->setStyleSheet(style1.label1);
    page2_label_center->setAlignment(Qt::AlignCenter);
    page2_center_layout->addWidget(page2_label_center);

    QWidget* page2_center_widget1 = new QWidget();
    page2_center_widget1->setMaximumHeight(100);
    QHBoxLayout* page2_center_widget1_layout = new QHBoxLayout(page2_center_widget1);
    page2_center_widget1 -> setStyleSheet(style1.widget_gray1);
    QPushButton* dft_opencv = new QPushButton("DFT-opencv");//filter_1d按钮
    dft_opencv->setText(QString::fromLocal8Bit("cv傅里叶变换"));
    dft_opencv->setMaximumSize(200, 50);
    dft_opencv->setStyleSheet(style1.button_main);
    page2_center_widget1_layout->addWidget(dft_opencv);
    page2_center_layout->addWidget(page2_center_widget1);
    QWidget* page2_center_widget2 = new QWidget();
    page2_center_widget2->setMaximumHeight(100);
    QHBoxLayout* page2_center_widget2_layout = new QHBoxLayout(page2_center_widget2);
    page2_center_widget2->setStyleSheet(style1.widget_gray1);
    QPushButton* DFT_custom_1d = new QPushButton("DFT_custom");//filter_1d按钮
    DFT_custom_1d->setText(QString::fromLocal8Bit("离散傅里叶正变换"));
    DFT_custom_1d->setToolTip("<html><font size='5' color='lightgreen'>forward!</font></html>");
    DFT_custom_1d->setMaximumSize(200, 50);
    DFT_custom_1d->setStyleSheet(style1.button_main);
    page2_center_widget2_layout->addWidget(DFT_custom_1d);
    page2_center_layout->addWidget(page2_center_widget2);

    QPushButton* IDFT_custom_1d = new QPushButton("IDFT_custom");//逆变换按钮
    IDFT_custom_1d->setText(QString::fromLocal8Bit("离散傅里叶逆变换"));
    IDFT_custom_1d->setToolTip("<html><font size='5' color='lightgreen'>inverse!</font></html>");
    IDFT_custom_1d->setMaximumSize(200, 50);
    IDFT_custom_1d->setStyleSheet(style1.button_main);
    page2_center_widget2_layout->addWidget(IDFT_custom_1d);
    //第三层
    QWidget* page2_center_widget3 = new QWidget();
    page2_center_widget3->setMaximumHeight(100);
    QHBoxLayout* page2_center_widget3_layout = new QHBoxLayout(page2_center_widget3);
    QPushButton* button_FFT2 = new QPushButton("FFT2");//逆变换按钮
    button_FFT2->setToolTip("<html><font size='5' color='lightgreen'>fft2-fk!</font></html>");
    button_FFT2->setMaximumSize(200, 50);
    button_FFT2->setStyleSheet(style1.button_main);
    page2_center_widget3_layout->addWidget(button_FFT2);
    page2_center_layout->addWidget(page2_center_widget3);//窗口添加进层


    //slot
    connect(dft_opencv, SIGNAL(clicked()), this, SLOT(cvdft_1d_widget()));//opencv-dft
    connect(DFT_custom_1d, SIGNAL(clicked()), this, SLOT(DFT_custom_1d_widget()));//一维DFT
    connect(IDFT_custom_1d, SIGNAL(clicked()), this, SLOT(IDFT_custom_1d_widget()));//逆一维DFT
    connect(button_FFT2, SIGNAL(clicked()), this, SLOT(FFT2_FK_widget()));//fft2d-fk
    ///page2_right
    QLabel* page2_label_right = new QLabel("right splitter");
    page2_label_right->setMaximumSize(200, 50);
    page2_label_right->setStyleSheet(style1.label1);
    page2_label_right->setAlignment(Qt::AlignCenter);
    page2_right_layout->addWidget(page2_label_right);
    QWidget* page2_right_widget1 = new QWidget();
    page2_right_widget1->setMaximumHeight(100);
    QHBoxLayout* page2_right_widget1_layout = new QHBoxLayout(page2_right_widget1);
    QPushButton* fliter1 = new QPushButton("Filter");//filter_1d按钮
    fliter1->setMaximumSize(200, 50);
    fliter1->setStyleSheet(style1.button_main);
    page2_right_widget1_layout->addWidget(fliter1);
    page2_right_layout->addWidget(page2_right_widget1);
    //slot
    connect(fliter1, SIGNAL(clicked()), this, SLOT(Filter_widget()));
    ///page3********
    ///page3********
    QHBoxLayout* page3_layout = new QHBoxLayout(page3);
    QSplitter* splitter_page3 = new QSplitter(Qt::Horizontal);

    page3_layout->addWidget(splitter_page3);

    QWidget* page3_left = new QWidget();
    QVBoxLayout* page3_left_layout = new QVBoxLayout(page3_left);
    QWidget* page3_center = new QWidget();
    QVBoxLayout* page3_center_layout = new QVBoxLayout(page3_center);
    QWidget* page3_right = new QWidget();
    QVBoxLayout* page3_right_layout = new QVBoxLayout(page3_right);

    splitter_page3->addWidget(page3_left);
    splitter_page3->addWidget(page3_center);
    splitter_page3->addWidget(page3_right);
    page3_left->setStyleSheet(style1.widget_gray1);
    page3_center->setStyleSheet(style1.widget_gray1);
    page3_right->setStyleSheet(style1.widget_gray1);
    ///page3_left
    QLabel* label_left = new QLabel("left splitter");
    label_left->setText(QString::fromLocal8Bit("左窗"));
    label_left->setMaximumSize(200, 50);
    label_left->setStyleSheet(style1.label1);
    label_left->setAlignment(Qt::AlignCenter);
    page3_left_layout->addWidget(label_left);
    
    QPushButton* tableWidget = new QPushButton("table");
    tableWidget->setText(QString::fromLocal8Bit("表格"));
    tableWidget->setMaximumSize(200, 50);
    tableWidget->setStyleSheet(style1.button_main);
    page3_left_layout->addWidget(tableWidget);
    //page3显示wiggle
    QPushButton* wiggle_button_H = new QPushButton("Wiggle_H");
    wiggle_button_H->setText(QString::fromLocal8Bit("波形-H"));
    wiggle_button_H->setMaximumSize(200, 50);
    wiggle_button_H->setStyleSheet(style1.button_main);
    page3_left_layout->addWidget(wiggle_button_H);
    QPushButton* wiggle_button_V = new QPushButton("Wiggle_V");
    wiggle_button_V->setText(QString::fromLocal8Bit("波形-V"));
    wiggle_button_V->setMaximumSize(200, 50);
    wiggle_button_V->setStyleSheet(style1.button_main);
    page3_left_layout->addWidget(wiggle_button_V);
    //page3eiggle保存
    QPushButton* Save_Wiggle = new QPushButton("Save_Wiggle");
    Save_Wiggle->setText(QString::fromLocal8Bit("保存波形"));
    Save_Wiggle->setMaximumSize(200, 50);
    Save_Wiggle->setStyleSheet(style1.button_main);
    page3_left_layout->addWidget(Save_Wiggle);
    ///page3_center
    QLabel* label_center = new QLabel("center splitter");
    label_center->setText(QString::fromLocal8Bit("中窗"));
    label_center->setMaximumSize(200, 50);
    label_center->setStyleSheet(style1.label1);
    label_center->setAlignment(Qt::AlignCenter);
    page3_center_layout->addWidget(label_center);
    ///page3_right
    QLabel* label_right = new QLabel("right splitter");
    label_right->setText(QString::fromLocal8Bit("右窗"));
    label_right->setMaximumSize(200, 50);
    label_right->setStyleSheet(style1.label1);
    label_right->setAlignment(Qt::AlignCenter);
    page3_right_layout->addWidget(label_right);
    ///page3@slot
    connect(tableWidget, SIGNAL(clicked()), this, SLOT(matrix_table_show()));
    connect(wiggle_button_H, SIGNAL(clicked()), this, SLOT(WiggleView_show_H()));
    connect(wiggle_button_V, SIGNAL(clicked()), this, SLOT(WiggleView_show_V()));
    connect(Save_Wiggle, SIGNAL(clicked()), this, SLOT(saveWiggle_1()));
    ///page4*********
    ///page4*********
    QVBoxLayout* page4_layout = new QVBoxLayout(page4);
    QSplitter* splitter_page4 = new QSplitter(Qt::Horizontal);
    page4_layout->addWidget(splitter_page4);
    QWidget* page4_left = new QWidget();
    QVBoxLayout* page4_left_layout = new QVBoxLayout(page4_left);//左边splitter
    //page4_left->setMinimumWidth(200);
    QWidget* page4_center = new QWidget();
    QVBoxLayout* page4_center_layout = new QVBoxLayout(page4_center);//中间splitter
    //page4_center->setMinimumWidth(200);
    QWidget* page4_right = new QWidget();
    QVBoxLayout* page4_right_layout = new QVBoxLayout(page4_right);//右边splitter
    //page4_right->setMinimumWidth(200);
    page4_left->setStyleSheet(style1.widget_gray1);
    page4_center->setStyleSheet(style1.widget_gray1);
    page4_right->setStyleSheet(style1.widget_gray1);
    splitter_page4->addWidget(page4_left);
    splitter_page4->addWidget(page4_center);
    splitter_page4->addWidget(page4_right);
    //page4_left
    QLabel* page4_label_left = new QLabel("left splitter");
    page4_label_left->setMaximumSize(200, 50);
    page4_label_left->setStyleSheet(style1.label1);
    page4_label_left->setAlignment(Qt::AlignCenter);
    page4_left_layout->addWidget(page4_label_left);

    QPushButton* data_3d_but1 = new QPushButton("3D");
    data_3d_but1->setStyleSheet(style1.button_main);
    page4_left_layout->addWidget(data_3d_but1);
    QPushButton* data_3d_but2 = new QPushButton("3D2");
    data_3d_but2->setStyleSheet(style1.button_main);
    page4_left_layout->addWidget(data_3d_but2);
    //page4_leftslot
    connect(data_3d_but1, SIGNAL(clicked()), this, SLOT(draw3DData()));
    connect(data_3d_but2, SIGNAL(clicked()), this, SLOT(draw3Dsurface()));
    //page4_center
    QLabel* page4_label_center = new QLabel("left splitter");
    page4_label_center->setMaximumSize(200, 50);
    page4_label_center->setStyleSheet(style1.label1);
    page4_label_center->setAlignment(Qt::AlignCenter);
    page4_center_layout->addWidget(page4_label_center);
    //page4_right
    QLabel* page4_label_right = new QLabel("left splitter");
    page4_label_right->setMaximumSize(200, 50);
    page4_label_right->setStyleSheet(style1.label1);
    page4_label_right->setAlignment(Qt::AlignCenter);
    page4_right_layout->addWidget(page4_label_right);
    ///************page5
    ///************page5
    QVBoxLayout* page5_layout = new QVBoxLayout(page5);
    QTabWidget* page5_tabwidget = new QTabWidget();
    QWidget* page5_tabwidget1 = new QWidget();
    QWidget* page5_tabwidget2 = new QWidget();
    QWidget* page5_tabwidget3 = new QWidget();
    page5_tabwidget->addTab(page5_tabwidget1, QString::fromLocal8Bit("窗口1"));//添加tab
    page5_tabwidget->addTab(page5_tabwidget2, QString::fromLocal8Bit("窗口2"));
    page5_tabwidget->addTab(page5_tabwidget3, QString::fromLocal8Bit("窗口3"));
    page5_tabwidget1->setStyleSheet(style1.widget_gray1);//设置样式
    page5_tabwidget2->setStyleSheet(style1.widget_gray2);
    page5_tabwidget3->setStyleSheet(style1.widget_gray1);
    page5_tabwidget->setStyleSheet(style1.tabStyle);

    page5_tabwidget->setTabToolTip(0, QString::fromLocal8Bit("窗口1tooltip"));//设置提示
    page5_tabwidget->setTabToolTip(1, QString::fromLocal8Bit("窗口2tooltip"));
    page5_tabwidget->setTabToolTip(2, QString::fromLocal8Bit("窗口3tooltip"));
    /*page5_tabwidget->setTabEnabled(0, true);
    page5_tabwidget->setTabEnabled(1, false);
    page5_tabwidget->setTabEnabled(2, true);*///设置页面激活
    //page5_tabwidget->setTabText(0, "hello");//设置tab索引text
    QVBoxLayout* page5_tabwidget1_layout = new QVBoxLayout(page5_tabwidget1);
    QPushButton* Syn_button = new QPushButton("Syn-widget");
    const char* localStr = "褶积合成数据."; 
    Syn_button->setText(QString::fromLocal8Bit(localStr));

    Syn_button->setMinimumSize(400, 200);
    Syn_button->setStyleSheet(style1.button_main);
    page5_tabwidget1_layout->addWidget(Syn_button,0, Qt::AlignHCenter);
    //slot
    connect(Syn_button, SIGNAL(clicked()), this, SLOT(Syn_widget()));

    page5_layout->addWidget(page5_tabwidget);
}
Qt_segy_process::~Qt_segy_process()
{}
void Qt_segy_process::main_page() {
    stackedWidget1->setCurrentIndex(0);
    ui.statusBar->showMessage(" Page1-->", 5000);
    stylesheet_QT style1;
    QString widget_gray1 = "Seis Data<br>Processing";
    QString widget_gray2 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
        "Software Developer<br>"
        "Based on Cpp&Qt Designed by Rain!"
        "</span>";
    QString combinedText = widget_gray1 + "<br>" + widget_gray2;
    label_picture->setStyleSheet(style1.label_main);
    label_picture->setText(QString("<html>%1</html>").arg(combinedText));
    label_picture->setAlignment(Qt::AlignCenter);
    page1->setStyleSheet(style1.widget_gray1);
    //for (QObject* obj : this->children()) {//显示所有QDockWidget
    //    if (QDockWidget* dockWidget = qobject_cast<QDockWidget*>(obj)) {
    //        dockWidget->show();
    //    }
    //}
    ui.mainToolBar->show();//工具栏显示
    ui.mainToolBar->setWindowTitle("My Main Toolbar");
}

void Qt_segy_process::on_stackpage1_change_clicked()//按钮点击切换到第一页槽函数内容
{
    stackedWidget1->setCurrentIndex(0);
    ui.statusBar->showMessage(" Page1-->", 5000);
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
    //for (QObject* obj : this->children()) {//显示所有QDockWidget
    //    if (QDockWidget* dockWidget = qobject_cast<QDockWidget*>(obj)) {
    //        dockWidget->show();
    //    }
    //}
    ui.mainToolBar->show();//工具栏显示
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
        "data Files(*.segy *.sgy );;All(*.*)");

    if (OpenFile_segy.isEmpty()) {
        qDebug() << "No file is selected!";
        return;
    }
    std::string filePath_orignal = OpenFile_segy.toStdString();//get file_path

    dataArray_real = getsegyarray(filePath_orignal);
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
    dataArray_real = getsegyarray(filePath);
    dataArray = normalized(dataArray_real);
    dataArray = transposeMatrix(dataArray);
    
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
    label_picture->setStyleSheet(style2.widget_gray2);

    ui.mainToolBar->show();//此处运行显示dock窗口页面。
    dockWidget1->show();

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
//获取局部数据
std::vector<std::vector<float>>Qt_segy_process::get_partsegyarray(int row,int col) {
    ui.statusBar->showMessage(tr("part segy data!"), 5000);
    if (dataArray_real.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return std::vector<std::vector<float>>();//返回默认vector
    }
    std::vector<std::vector<float>> temp = transposeMatrix(dataArray_real);
    // Allocate space for part_segy_data
    std::vector<std::vector<float>> part_segy_data(row, std::vector<float>(col, 0.0f));
    for (int i = 0; i < row; ++i) 
    {
        for (int j = 0; j < col; ++j) 
        {
            part_segy_data[i][j] = temp[i][j];
        }
    }
    return  part_segy_data;
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
// 函数返回二维向量最小值或最大值
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
//double型返回一维
double Qt_segy_process::findExtremeValue(const std::vector<double>& s, int flag) {
    if (s.empty()) {
        std::cerr << "Vector is empty." << std::endl;
        return 0; // or throw an exception, depending on your requirements
    }

    double result = s[0]; // Initialize with the first element

    for (int i = 1; i < s.size(); i++) {
        if (flag == 1 && result > s[i]) {
            result = s[i]; // Return minimum value
        }
        else if (flag == 2 && result < s[i]) {
            result = s[i]; // Return maximum value
        }
    }

    return result;
}
//float型
float Qt_segy_process::findExtremeValue(const std::vector<float>& s, int flag) {
    if (s.empty()) {
        std::cerr << "Vector is empty." << std::endl;
        // You might want to throw an exception or handle this case differently.
        return 0.0f; // Default return value for float type
    }
    auto result = s[0]; // Initialize with the first element
    for (int i = 1; i < s.size(); i++) {
        if (flag == 1 && result > s[i]) {
            result = s[i]; // Return minimum value
        }
        else if (flag == 2 && result < s[i]) {
            result = s[i]; // Return maximum value
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
            image_temp.at<uchar>(i, j) = dataArray[i][j] * 255;
        }
    }
    return image_temp;
    ui.statusBar->showMessage(tr("dataarray2image complete!"), 3000);
}
//open_csv
void Qt_segy_process::open_csv() {
    qDebug() << "input data!";
    ui.statusBar->showMessage(tr("Loading data!"), 5000);
    //QString OpenFile;
    OpenFile_csv = QFileDialog::getOpenFileName(this,//OpenFile_csv中存储的是路径;
        "please choose a file",
        "",
        "data Files(*.csv );;All(*.*)");
    if (OpenFile_csv.isEmpty()) {
        qDebug() << "No file is selected!";
        return;
    }
    ui.statusBar->showMessage(tr("Loading complet!"), 2000);
    ui.statusBar->showMessage(QString("disk location:%1").arg(OpenFile_csv), 3000);
    stylesheet_QT style2;
    ui.statusBar->setStyleSheet(style2.styleSheet_bar);
    std::ifstream file;
    std::string filePath = OpenFile_csv.toStdString();//get file_path
    file.open(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return ;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<float> row;
        std::istringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            // Convert the cell value to double
            float value = std::stod(cell);
            row.push_back(value);
        }
       dataArray_csv.push_back(row);
       ui.statusBar->showMessage(QString("csv data open sucessful").arg(OpenFile_csv), 3000);
    }
    file.close();
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
//计算数据能量分布
std::vector<float> Qt_segy_process::calculate_energy(std::vector<std::vector<float>> matrix,int calculateFor) {

    std::vector<float> temp;
    int title_par = calculateFor;
    // Assuming the matrix is not empty
    if (!matrix.empty() && !matrix[0].empty()) {
        if (calculateFor == 0) {
            // Calculate energy for each row
            for (int i = 0; i < matrix.size(); ++i) {
                float energy = 0.0;

                for (int j = 0; j < matrix[i].size(); ++j) {
                    energy += std::pow(matrix[i][j], 2.0);
                }

                temp.push_back(energy);
            }
        }
        else if (calculateFor == 1) {
            // Calculate energy for each column
            // Assuming all rows have the same number of columns
            int numColumns = matrix[0].size();

            for (int j = 0; j < numColumns; ++j) {
                float energy = 0.0;

                for (int i = 0; i < matrix.size(); ++i) {
                    energy += std::pow(matrix[i][j], 2.0);
                }

                temp.push_back(energy);
            }
        }
    }
    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();
    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (size_t i = 0; i < temp.size(); ++i) {
        series->append(i, temp[i]);
    }
    chart->addSeries(series);
    // 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;
    // 设置坐标轴标签
    axisX->setTitleText("series");
    axisY->setTitleText("energy(**2)");
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
    QString title1 = QString("matrix energy calculateFor%1").arg(title_par);
    chart->setTitle(title1);
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);
    ChartView_widget->show();
    return temp;
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
//单道数据agc
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
//agc保存
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
//切除极小值，防止数据超出范围
std::vector<std::vector<float>> Qt_segy_process::Exc_min(std::vector<std::vector<float>> matrix) 
{
    float cut_min = 1e-10;
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
    float maxDataValue = *std::max_element(Ampli.begin(), Ampli.end());

    // 设置Y轴最大值为data数据最大值的1.2倍
    axisY->setMax(maxDataValue * 1.2);
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
//数据的频谱函数重载
std::vector<std::vector<float>> Qt_segy_process::opencv_fft_1d(std::vector<std::vector<float>> matrix, int tracei,int sampling) {
    if (matrix.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return matrix;
    }
    vector<float> data;//存储单道数据空间
    std::vector<std::vector<float>> dataarray_fft = transposeMatrix(matrix);//取出要处理的segy数据
    int data_tracei = tracei;
    for (int i = 0; i < dataarray_fft.size(); i++) {//获取指定i的单道数据
        data.push_back(dataarray_fft[i][data_tracei]);
    }
    data1d_2chartview(data);
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
    opencv_fft_1d_Ampli.clear();
    int L_freq = floor(data.size() / 2);
    for (int k = 1; k < L_freq + 1; k++)
    {
        float ampli = sqrt(pow(amplite_Re[k - 1], 2) + pow(amplite_Im[k - 1], 2)) / L_freq;
        Ampli.push_back(ampli);//FFT幅值
        opencv_fft_1d_Ampli.push_back(ampli);
        float freq = ((float)sampling) / data.size() * k;
        Freq.push_back(freq);//频率值
    }
    QString message = QString("vector fft completed!");
    ui.statusBar->showMessage(message);
    std::vector<std::vector<float>> fft_return;

    fft_return.push_back(Freq);//将fft的频率插入return第一行
    fft_return.push_back(Ampli);//将fft的幅值插入return第二行
    ///QChartView
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();
    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (size_t i = 0; i < fft_return[0].size(); ++i) {
        series->append(fft_return[0][i], fft_return[1][i]);
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
    // 计算数据的最大值
    float maxDataValue = *std::max_element(fft_return[1].begin(), fft_return[1].end());
    // 设置Y轴最大值为data数据最大值的1.2倍
    axisY->setMax(maxDataValue * 1.2);
    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    // 将系列关联到坐标轴
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->legend()->hide();
    QString title1 = QString("opencv_fft:number  %1  trace").arg(data_trace_i->value());
    chart->setTitle(title1);
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);
    ChartView_widget->show();

    return fft_return;
}
//手动计算离散傅里叶变换
std::vector<std::complex<float>> Qt_segy_process::discrete_fourier_transform(const std::vector<float> x) {
    int N = x.size();
    std::vector<std::complex<float>> X(N, std::complex<float>(0.0f, 0.0f));//存储计算结果
    
    for (int k = 0; k < N; ++k) {
        float angle_factor = -2.0f * M_PI * k / N; // 频率因子
        std::complex<float> sum(0.0f, 0.0f);
        for (int n = 0; n < N; ++n) {
            float angle = angle_factor * n; // 频率因子 * 时间点
            std::complex<float> exp_term = std::polar<float>(1.0, angle);
            sum += exp_term * x[n];
        }
        X[k] = sum;
    } 
    return X;
}
//反傅里叶变换
std::vector<float> Qt_segy_process::inverse_discrete_fourier_transform(std::vector<std::complex<float>> x) {
   
    int N = x.size();
    const double PI = 3.14159265358979323846;
    std::vector<std::complex<float>> X(N, std::complex<float>(0.0f, 0.0f));//存储计算结果

    for (int k = 0; k < N; ++k) {
        float angle_factor = 2.0f * M_PI * k / N; // 频率因子
        std::complex<float> sum(0.0f, 0.0f);
        for (int n = 0; n < N; ++n) {
            float angle = angle_factor * n; // 频率因子 * 时间点
            std::complex<float> exp_term = std::polar<float>(1.0, angle);
            sum += exp_term * x[n];
        }
        X[k] = sum/static_cast<float>(2* PI);
    }
    std::vector<float> result;

    for (int k = 0; k < N; ++k) {

        result.push_back((X[k].real()));
    }


    return result;

}
//计算二维数据的频谱并显示
void Qt_segy_process::opencv_fft2d() {
    if (dataArray_real.empty()) {//先判断数据是否初始化
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
    QString message = QString("agcdata2dataarray loaded! Trace simple %1 ;Trace number %2;").arg(agc_save_data.size()).arg(agc_save_data[0].size());
    ui.statusBar->showMessage(message);
}

void Qt_segy_process::csvdata2dataarray() {
    if (dataArray_csv.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    dataArray_real = transposeMatrix(dataArray_csv);
    QString message = QString("data loaded! Trace simple %1 ;Trace number %2;").arg(dataArray_csv.size()).arg(dataArray_csv[0].size());
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
    dataArray_real = getsegyarray(filePath);
    QString message = QString("Real data loaded! Trace simple %1 ;Trace number %2;").arg(dataArray_real.size()).arg(dataArray_real[0].size());
    ui.statusBar->showMessage(message);
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
//S变换
void Qt_segy_process::STOCK_function() {
    if (dataArray.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    widget_stockwell_fun = new QWidget();//建立显示窗口
    //widget_stockwell_fun->setWindowFlags(Qt::WindowStaysOnTopHint);//通过flag允许始终在其他窗口上方
    widget_stockwell_fun->setMinimumSize(800, 600);
    stylesheet_QT style_button;
    widget_stockwell_fun->setStyleSheet(style_button.widget_gray1);
    QChartView* chartView_stock = new QChartView();
    chart_s_data = new QChart();
    
    series_stock = new QSplineSeries();//1
    chart_s_data->addSeries(series_stock);//2
    QVBoxLayout* layout_stock = new QVBoxLayout(widget_stockwell_fun);
    
    chartView_stock->setChart(chart_s_data);
    chartView_stock->setMaximumHeight(400);
    widget_stockwell_fun->show();

    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    //vector<double> s;//存储单道数据空间
    //vector<double> t;// 存储生成时间序列 t
    //tracei_widget
    QWidget* widget_tracei = new QWidget();
    QHBoxLayout* widget_tracei_layout = new QHBoxLayout(widget_tracei);
    QLabel* label_trace = new QLabel("trace_i");
    StockTF_trace_i = new QSpinBox();
    QString mess_tip1 = "<html><font size='5' color='lightgreen'>StockTF_trace_i!</font></html>";
    StockTF_trace_i->setToolTip(mess_tip1);
    label_trace->setStyleSheet(style_button.label1);
    StockTF_trace_i->setStyleSheet(style_button.label1);
    label_trace->setMaximumSize(200, 50);
    StockTF_trace_i->setMaximumSize(200, 50);
    StockTF_trace_i->setValue(20);

    StockTF_trace_samplerate = new QSpinBox();
    QString mess_tip_sample = "<html><font size='5' color='lightgreen'>samplerate_us!</font></html>";
    StockTF_trace_samplerate->setToolTip(mess_tip_sample);
    StockTF_trace_samplerate->setStyleSheet(style_button.label1);
    StockTF_trace_samplerate->setMaximumSize(200, 50);
    StockTF_trace_samplerate->setMaximum(100000);//设置最大值
    StockTF_trace_samplerate->setValue(500);

    widget_tracei_layout->addWidget(label_trace);
    widget_tracei_layout->addWidget(StockTF_trace_i);
    widget_tracei_layout->addWidget(StockTF_trace_samplerate);
    layout_stock->addWidget(widget_tracei);
    //parmetar_widget
    QWidget* widget_parmeter = new QWidget();
    QHBoxLayout* widget_parmeter_layout = new QHBoxLayout(widget_parmeter);
    QLabel* label_widget_parmetar = new QLabel("widget_parmetar");
    freqlow_st = new QSpinBox();
    freqhigh_st = new QSpinBox();
    alpha_st = new QSpinBox();

    label_widget_parmetar->setStyleSheet(style_button.label1);
    freqlow_st->setStyleSheet(style_button.label1);
    freqhigh_st->setStyleSheet(style_button.label1);
    alpha_st->setStyleSheet(style_button.label1);
    QString mess_tip2= "<html><font size='5' color='lightgreen'>freqlow_st!</font></html>";
    QString mess_tip3 = "<html><font size='5' color='lightgreen'> freqhigh_st!</font></html>";
    QString mess_tip4 = "<html><font size='5' color='lightgreen'> alpha_st!</font></html>";
    freqlow_st->setToolTip(mess_tip2);
    freqhigh_st->setToolTip(mess_tip3);
    alpha_st->setToolTip(mess_tip4);
    label_widget_parmetar->setMaximumSize(200, 50);
    freqlow_st->setMaximumSize(200, 50); freqlow_st->setValue(1);
    freqhigh_st->setMaximumSize(200, 50); freqhigh_st->setValue(400);

    freqlow_st->setMaximum(freqhigh_st->value());
    freqhigh_st->setMaximum(10000);
    alpha_st->setMaximumSize(200, 50); alpha_st->setValue(1);
    alpha_st->setMaximum(freqhigh_st->value());

    widget_parmeter_layout->addWidget(label_widget_parmetar);
    widget_parmeter_layout->addWidget(freqlow_st);
    widget_parmeter_layout->addWidget(freqhigh_st);
    widget_parmeter_layout->addWidget(alpha_st);
    layout_stock->addWidget(widget_parmeter);

    double freqlow = freqlow_st->value();
    double freqhigh = freqhigh_st->value();
    double alpha = alpha_st->value();

    int data_tracei = StockTF_trace_i->value();//道数
    signal_st_i.clear();
    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_st_i.push_back(data[i][data_tracei]);//得到一维向量data
    }
    series_stock->clear();
    for (int i = 0; i < signal_st_i.size(); i++) {//添加道数据显示
        series_stock->append(i, signal_st_i[i]);
    }
    QValueAxis* axisX = new QValueAxis();//添加坐标轴
    QValueAxis* axisY = new QValueAxis();
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("sample");
    axisY->setTitleText("Amp");
    axisX->setTickCount(11);//设置刻度数量
    axisY->setTickCount(11);
    chart_s_data->addAxis(axisX, Qt::AlignBottom);//设置位置
    chart_s_data->addAxis(axisY, Qt::AlignLeft);
    series_stock->attachAxis(axisX);
    series_stock->attachAxis(axisY);
    chartView_stock->setChart(chart_s_data);
    if (signal_st_i.empty()) {
        std::cout << "Vector is empty." << std::endl;
        return;
    }
    auto minElement = std::min_element(signal_st_i.begin(), signal_st_i.end());
    auto maxElement = std::max_element(signal_st_i.begin(), signal_st_i.end());
    double min = *minElement;
    double max = *maxElement;
    axisX->setRange(0, signal_st_i.size());
    axisY->setRange(min * 1.2, max * 1.2);
    axisY->setLabelFormat("%.1f"); // 显示一位小数
    QString chartTitle = QString("Chart-Trace Parameter %1").arg(data_tracei);
    chart_s_data->setTitle(chartTitle);
    chart_s_data->setTitleFont(font);
    chartView_stock->setRenderHint(QPainter::Antialiasing);
    layout_stock->addWidget(chartView_stock);
    //widget_ST
    QPushButton* ST_button = new QPushButton("ST-transform-run");
    ST_button->setText(QString::fromLocal8Bit("标准S变换"));
    ST_button->setMinimumSize(200, 50);
    ST_button->setMaximumSize(400, 100);
    ST_button->setStyleSheet(style_button.button_main);
    layout_stock->addWidget(ST_button, 0, Qt::AlignHCenter);
    connect(ST_button, SIGNAL(clicked()), this, SLOT(calculate_st_main()));
    //widget_save
    QWidget* widget_button = new QWidget();
    QHBoxLayout* widget_button_layout = new QHBoxLayout(widget_button);
    stack_save = new QPushButton("ST_save_picture");
    stack_save->setText(QString::fromLocal8Bit("保存图片"));
    QPushButton* stack_save_data = new QPushButton("ST_save_csv");
    stack_save_data->setText(QString::fromLocal8Bit("保存文件"));
    stack_close = new QPushButton("ST_close");
    stack_close->setText(QString::fromLocal8Bit("Close"));
    layout_stock->addWidget(widget_button);
    widget_button_layout->addWidget(stack_save);
    widget_button_layout->addWidget(stack_save_data);
    widget_button_layout->addWidget(stack_close);
    stack_save->setMinimumSize(100, 30);
    stack_save->setMaximumSize(200, 50);
    stack_save_data->setMinimumSize(100, 30);
    stack_save_data->setMaximumSize(200, 50);
    stack_close->setMinimumSize(100, 30);
    stack_close->setMaximumSize(200, 50);
    
    stack_save->setStyleSheet(style_button.button_main);
    stack_save_data->setStyleSheet(style_button.button_main);
    stack_close->setStyleSheet(style_button.button_main);
    ///slot
    connect(stack_save, SIGNAL(clicked()), this, SLOT(save_stackimage()));//槽函数内部实现关闭;
    connect(stack_save_data, SIGNAL(clicked()), this, SLOT(save_stacked_data()));
    connect(stack_close, SIGNAL(clicked()), this, SLOT(close_stackwindow()));
}
//st按钮计算函数
void Qt_segy_process::calculate_st_main() {
    
    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    signal_st_i.clear();
    int data_tracei = StockTF_trace_i->value();//道数
    QString chartTitle = QString("Chart-Trace Parameter %1").arg(data_tracei);
    chart_s_data->setTitle(chartTitle);//更新图表标题
    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_st_i.push_back(data[i][data_tracei]);//得到一维向量data
    }
    series_stock->clear();
    for (int i = 0; i < signal_st_i.size(); i++) {//添加道数据显示
        series_stock->append(i, signal_st_i[i]);
    }

    int samplerate_st;
    samplerate_st = StockTF_trace_samplerate->value();
    double dt = samplerate_st / static_cast<double>((1000)) / 1000;//采样率500us
    int time_len = signal_st_i.size();
    t.clear();
    for (int i = 0; i < time_len; i++) {
        t.push_back(i * dt);
    }
    // 检查数据
    if (t.empty() || signal_st_i.empty() || t.size() != signal_st_i.size()) {
        cerr << "Error: Invalid input data." << endl;
        return; // 或者采取其他合适的处理方式
    }
    double freqlow = freqlow_st->value();
    double freqhigh = freqhigh_st->value();
    double alpha = alpha_st->value();
    /// 计算S变换
    std::vector<vector<complex<double>>>data_s = myst(t, signal_st_i, freqlow, freqhigh, alpha);//计算出的是复数
    std::vector<std::vector<float>> temp(data_s.size(), std::vector<float>(data_s[0].size()));//存储绝对值部分
    stocked_data.clear();//多次处理之前需要清除原有的数据。clear
    for (size_t i = 0; i < data_s.size(); ++i) {
        vector<float> row;
        for (size_t j = 0; j < data_s[i].size(); ++j) {
            temp[i][j] = std::abs(data_s[i][j]);
            row.push_back(std::abs(data_s[i][j]));
        }
        stocked_data.push_back(row);
    }
    ///图片显示
    //temp = normalized(temp);
    //src = dataArray2image(temp);
    //QString message = QString("stock_transform completed! fre %1 ; number %2;").arg(temp.size()).arg(temp[0].size());
    //ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
    //ui.statusBar->showMessage(message);
    //qtImage2= new QImage(src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8);//灰度图
    //label_picture->setPixmap(QPixmap::fromImage(*qtImage2).scaled(label_picture->size()));
    //cv::namedWindow("STOCKWELL_transform", cv::WINDOW_NORMAL);
    //cv::imshow("STOCKWELL_transform", src); // 显示colorMap
    //waitKey(0);
    //cv::destroyAllWindows(); // 关闭所有OpenCV窗口
    data2d2image(transposeMatrix(temp));//调用函数直接显示
}
//计算s变换主程序
std::vector<std::vector<std::complex<double>>> Qt_segy_process::myst(const std::vector<double> t, const std::vector<double> Sig,
    double freqlow, double freqhigh, double alpha) {
    const double PI = 3.14159265358979323846;
    // 计算频率数量
    int nLevel = static_cast<int>((freqhigh - freqlow) / alpha) + 1;
    // 时间和信号的长度
    int TimeLen = t.size();
    int SigLen = Sig.size();
    double dt = t[1] - t[0];
    // 产生频率范围
    std::vector<double> fre;
    for (int m = 0; m < nLevel; ++m) {
        fre.push_back(freqlow + m * alpha);
    }
    // 分配计算结果的存储单元
    std::vector<std::vector<std::complex<double>>> wcoefs;
    std::vector<std::complex<double>> temp(TimeLen, std::complex<double>(0.0, 0.0));
    // 循环计算
    int progressValue;
    stylesheet_QT style_bar;
    progress_bar = new QProgressBar();//设置进度条
    progress_bar->setMinimumSize(800, 100);
    progress_bar->setWindowTitle("Qt_segy_process::myst progress");
    progress_bar->setStyleSheet(style_bar.style_bar);
    progress_bar->setRange(0, 100); // 设置进度条的范围为0到100
    progress_bar->show();
    for (int m = 0; m < nLevel; ++m) {
        QApplication::processEvents();
        progressValue = m * 100 / nLevel; // 计算整数进度值
        progress_bar->setValue(progressValue);
        qDebug() << progressValue;//输出窗口显示处理进度
        if (progressValue == 98) {
            // 进度达到100，隐藏或关闭进度条
            progress_bar->hide(); // 或 progress->close();
        }
        // 提取频率参数
        double f = fre[m];
        // 计算高斯窗口宽度
        double sigma_f = 1 / f;
        std::vector<complex<double>> Gauss_st;
        std::complex<double>  Gauss_st0;
        std::vector<complex<double>> temp;
        for (int n = 0; n < TimeLen; ++n) {
            // 计算高斯窗口
            std::complex<double> temp0;
            for (int k = 0; k < TimeLen; ++k) {//每个t点进行计算时间移动计算。

                double exponent = -0.5 * pow((n * dt - t[k]), 2) / pow(sigma_f, 2);
                double real_part = 1.0 / (sqrt(2 * PI) * sigma_f);
                double imag_part = -2 * PI * f * t[k];
                Gauss_st0 = std::polar(1.0, imag_part) * (real_part * exp(exponent));//n*dt固定，t[k]变化  
                //qDebug() << Gauss_st0.real();//这一步计算正确，保持不动 
                temp0 += (Sig[k] * Gauss_st0);
            }
            //qDebug() << temp0.real();//这一步计算正确，保持不动
            temp.push_back(temp0 * dt);
        }
        /*for (int i = 0; i < 1; i++) {
            qDebug() << temp[i].real();
        }*/
        wcoefs.push_back(temp);
    }

    return wcoefs;
}
//存储stackwell结果
void   Qt_segy_process::save_stackimage() {

    if (stocked_data.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    // 显示保存对话框
    std::vector<std::vector<float>> temp(stocked_data.size(), std::vector<float>(stocked_data[0].size()));
    temp = normalized(stocked_data);
    src = dataArray2image(temp);
    //qtImage2 = new QImage(src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8);//灰度图
    //
    cv::Mat colorMap;
    applyColorMap(src, colorMap, cv::COLORMAP_JET);//转换为jet彩色
    cv::Mat rgbImage;
    cv::cvtColor(colorMap, rgbImage, cv::COLOR_BGR2RGB);
    qtImage2=new QImage(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);

    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Image", "", "Images (*.png *.jpg)");
    // 如果用户点击了保存按钮
    if (!filePath.isEmpty()) {
        // 保存QPixmap到用户选择的文件路径
        if (qtImage2->save(filePath)) {
            qDebug() << "Image saved successfully!";
        }
        else {
            qDebug() << "Failed to save image!";
        }
    }
    ui.statusBar->showMessage(QString("image saved successfully!"),3000);
}
void  Qt_segy_process::save_stacked_data() {
    save_2d_data(stocked_data);
}
//关闭stackwell窗口
void  Qt_segy_process::close_stackwindow() {
    widget_stockwell_fun->close();
    ui.statusBar->showMessage("stackwindow closed!");
}
//获取线性序列
std::vector<double> linspace(double start, double end, int num) {//代替np.linsapce
    std::vector<double> result(num);
    double step = (end - start) / (num - 1);
    std::iota(result.begin(), result.end(), start);
    return result;
}
//CWT
void Qt_segy_process::CWT_function() {
    if (dataArray.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    QWidget*widget_cwt_fun = new QWidget();//建立显示窗口
    widget_cwt_fun->setMinimumSize(800, 600);
    stylesheet_QT style_button;
    widget_cwt_fun->setStyleSheet(style_button.widget_gray1);
    QChartView* chartView_cwt = new QChartView();
    QChart*chart_cwt_data = new QChart();

    QSplineSeries*series_cwt = new QSplineSeries();//1显示地震数据series
    chart_cwt_data->addSeries(series_cwt);//2
    QVBoxLayout* layout_cwt = new QVBoxLayout(widget_cwt_fun);
    chartView_cwt->setChart(chart_cwt_data);
    chartView_cwt->setMaximumHeight(400);
    widget_cwt_fun->show();
    signal_cwt_i.clear();
    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    int data_tracei = 30;
    for (int i = 0; i < data.size(); i++) {//添加道数据显示
        signal_cwt_i.push_back(data[i][data_tracei]);
    }
    for (int i = 0; i < signal_cwt_i.size(); i++) {//添加道数据显示
        series_cwt->append(i, signal_cwt_i[i]);
    }
    
    QValueAxis* axisX = new QValueAxis();//添加坐标轴
    QValueAxis* axisY = new QValueAxis();
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("sample");
    axisY->setTitleText("Amp");
    axisX->setTickCount(11);//设置刻度数量
    axisY->setTickCount(11);
    chart_cwt_data->addAxis(axisX, Qt::AlignBottom);//设置位置
    chart_cwt_data->addAxis(axisY, Qt::AlignLeft);
    series_cwt->attachAxis(axisX);
    series_cwt->attachAxis(axisY);
    chartView_cwt->setChart(chart_cwt_data);
   
    if (signal_cwt_i.empty()) {
        std::cout << "Vector is empty." << std::endl;
        return;
    }
    axisX->setRange(0, signal_cwt_i.size());

    auto minElement = std::min_element(signal_cwt_i.begin(), signal_cwt_i.end());
    auto maxElement = std::max_element(signal_cwt_i.begin(), signal_cwt_i.end());
    double min = *minElement;
    double max = *maxElement;

    axisY->setRange(min * 1.2, max * 1.2);
    axisY->setLabelFormat("%.1f"); // 显示一位小数
    QString chartTitle = QString("Chart-Trace Parameter %1").arg(data_tracei);
    chart_cwt_data->setTitle(chartTitle);
    chart_cwt_data->setTitleFont(font);
    chartView_cwt->setRenderHint(QPainter::Antialiasing);
    layout_cwt->addWidget(chartView_cwt);

    //tracei
    QWidget* widget_cwt_tracei = new QWidget();
    QHBoxLayout* layout_tracei = new QHBoxLayout(widget_cwt_tracei);

    QLabel* label_trace = new QLabel("trace_i");
    label_trace->setStyleSheet(style_button.label1);
    label_trace->setMaximumSize(200, 50);

    cwt_trace_i = new QSpinBox();
    QString mess_tip1 = "<html><font size='5' color='lightgreen'>cwt_trace_i!</font></html>";
    cwt_trace_i->setToolTip(mess_tip1);
    cwt_trace_i->setStyleSheet(style_button.label1);
    cwt_trace_i->setMaximumSize(200, 50);
    cwt_trace_i->setValue(20);

    layout_tracei->addWidget(label_trace);
    layout_tracei->addWidget(cwt_trace_i);

    QWidget* widget_fre = new QWidget();
    QHBoxLayout* layout_fre = new QHBoxLayout(widget_fre);

    QLabel* label_fre = new QLabel("fre");
    label_fre->setStyleSheet(style_button.label1);
    label_fre->setMaximumSize(200, 50);

    QSpinBox*fre1 = new QSpinBox();
    QString mess_tip2 = "<html><font size='5' color='lightgreen'>cwt_fre!</font></html>";
    fre1->setToolTip(mess_tip2);
    fre1->setStyleSheet(style_button.label1); 
    fre1->setMaximumSize(200, 50);
    fre1->setValue(20);

    layout_fre->addWidget(label_fre);
    layout_fre->addWidget(fre1);

    QPushButton* CWT_button = new QPushButton("CWT-run");
    CWT_button->setMinimumSize(200, 50);
    CWT_button->setMaximumSize(400, 100);
    CWT_button->setStyleSheet(style_button.button_main);
    

    QWidget* widget_save_button = new QWidget();
    QHBoxLayout* layout_save = new QHBoxLayout(widget_save_button);

    QPushButton* CWT_save = new QPushButton("Save");
    CWT_save->setMinimumSize(200, 50);
    CWT_save->setMaximumSize(400, 100);
    CWT_save->setStyleSheet(style_button.button_main);

    QPushButton* CWT_close = new QPushButton("Close");
    CWT_close->setMinimumSize(200, 50);
    CWT_close->setMaximumSize(400, 100);
    CWT_close->setStyleSheet(style_button.button_main);

    layout_cwt->addWidget(widget_cwt_tracei);
    layout_cwt->addWidget(widget_fre);

    layout_cwt->addWidget(CWT_button, 0, Qt::AlignHCenter);
    layout_save->addWidget(CWT_save, 0, Qt::AlignHCenter);
    layout_save->addWidget(CWT_close, 0, Qt::AlignHCenter);

    layout_cwt->addWidget(widget_save_button);
    //slot
    
    connect(CWT_button, SIGNAL(clicked()), this, SLOT(CWT_calcualte()));
    connect(CWT_close, SIGNAL(clicked()), widget_cwt_fun, SLOT(close()));
}
void Qt_segy_process::CWT_calcualte() {
    QString message = QString("run_cwt_main");
    ui.statusBar->showMessage(message);
    qDebug("CWT_calcualte_start!");
    return;
}
//STFT
void Qt_segy_process::STFT_function() {

    if (dataArray.empty()) {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    QWidget* widget_stft_fun = new QWidget();//建立显示窗口
    widget_stft_fun->setMinimumSize(800, 600);
    stylesheet_QT style_button;
    widget_stft_fun->setStyleSheet(style_button.widget_gray1);
    QChartView* chartView_stft = new QChartView();
    QChart* chart_stft_data = new QChart();

    series_stft = new QSplineSeries();//1
    chart_stft_data->addSeries(series_stft);//2
    QVBoxLayout* layout_stft = new QVBoxLayout(widget_stft_fun);

    chartView_stft->setChart(chart_stft_data);
    chartView_stft->setMaximumHeight(400);
    widget_stft_fun->show();

    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    
    QWidget* widget_tracei = new QWidget();
    QHBoxLayout* widget_tracei_layout = new QHBoxLayout(widget_tracei);
    QLabel* label_trace = new QLabel("trace_i");
    stft_trace_i = new QSpinBox();
    QString mess_tip1 = "<html><font size='5' color='lightgreen'>StockTF_trace_i!</font></html>";
    stft_trace_i->setToolTip(mess_tip1);
    label_trace->setStyleSheet(style_button.label1);
    stft_trace_i->setStyleSheet(style_button.label1);
    label_trace->setMaximumSize(200, 50);
    stft_trace_i->setMaximumSize(200, 50);
    stft_trace_i->setValue(20);

    QSpinBox*stft_trace_samplerate = new QSpinBox();
    QString mess_tip_sample = "<html><font size='5' color='lightgreen'>samplerate_us!</font></html>";
    stft_trace_samplerate->setToolTip(mess_tip_sample);
    stft_trace_samplerate->setStyleSheet(style_button.label1);
    stft_trace_samplerate->setMaximumSize(200, 50);
    stft_trace_samplerate->setMaximum(100000);//设置最大值
    stft_trace_samplerate->setValue(500);

    widget_tracei_layout->addWidget(label_trace);
    widget_tracei_layout->addWidget(stft_trace_i);
    widget_tracei_layout->addWidget(stft_trace_samplerate);
    layout_stft->addWidget(widget_tracei);
    //parmetar_widget
    QWidget* widget_parmeter = new QWidget();
    QHBoxLayout* widget_parmeter_layout = new QHBoxLayout(widget_parmeter);
    QLabel* label_widget_parmetar = new QLabel("widget_parmetar");
    stft_windows_size = new QSpinBox();
    stft_hop_length = new QSpinBox();
    stft_windows_size->setMaximumSize(200, 50);
    QString tooltip_windows_size = "<html><font size='5' color='lightgreen'>windows_size!</font></html>";
    stft_windows_size->setToolTip(tooltip_windows_size);
    stft_windows_size->setMaximum(data.size());
    stft_windows_size->setValue(100);
    stft_windows_size->setStyleSheet(style_button.label1);

    stft_hop_length->setValue(1);
    stft_hop_length->setMaximumSize(200, 50);
    QString tooltip_hop_length = "<html><font size='5' color='lightgreen'>hop_length</font></html>";
    stft_hop_length->setToolTip(tooltip_hop_length);
    stft_hop_length->setMaximum(stft_windows_size->value());
    stft_hop_length->setStyleSheet(style_button.label1);

    label_widget_parmetar->setMaximumSize(200, 50);
    
    widget_parmeter_layout->addWidget(label_widget_parmetar);
    widget_parmeter_layout->addWidget(stft_windows_size);
    widget_parmeter_layout->addWidget(stft_hop_length);

    layout_stft->addWidget(widget_parmeter);

    int data_tracei = stft_trace_i->value();//道数
    signal_stft_i.clear();

    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_stft_i.push_back(data[i][data_tracei]);//得到一维向量data
    }
    series_stft->clear();
    for (int i = 0; i < signal_stft_i.size(); i++) {//添加道数据显示
        series_stft->append(i, signal_stft_i[i]);
    }
    QValueAxis* axisX = new QValueAxis();//添加坐标轴
    QValueAxis* axisY = new QValueAxis();
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("sample");
    axisY->setTitleText("Amp");
    axisX->setTickCount(11);//设置刻度数量
    axisY->setTickCount(11);
    chart_stft_data->addAxis(axisX, Qt::AlignBottom);//设置位置
    chart_stft_data->addAxis(axisY, Qt::AlignLeft);
    series_stft->attachAxis(axisX);
    series_stft->attachAxis(axisY);
    chartView_stft->setChart(chart_stft_data);

    if (signal_stft_i.empty()) {
        std::cout << "Vector is empty." << std::endl;
        return;
    }
    auto minElement = std::min_element(signal_stft_i.begin(), signal_stft_i.end());
    auto maxElement = std::max_element(signal_stft_i.begin(), signal_stft_i.end());
    double min = *minElement;
    double max = *maxElement;
    axisX->setRange(0, signal_stft_i.size());
    axisY->setRange(min * 1.2, max * 1.2);
    axisY->setLabelFormat("%.1f"); // 显示一位小数

    QString chartTitle = QString("Chart-Trace Parameter %1").arg(data_tracei);
    chart_stft_data->setTitle(chartTitle);
    chart_stft_data->setTitleFont(font);
    chartView_stft->setRenderHint(QPainter::Antialiasing);
    layout_stft->addWidget(chartView_stft);
    //widget_stft
    QPushButton* STFT_button = new QPushButton("STFT-run");
    STFT_button->setMinimumSize(200, 50);
    STFT_button->setMaximumSize(400, 100);
    STFT_button->setStyleSheet(style_button.button_main);
    layout_stft->addWidget(STFT_button, 0, Qt::AlignHCenter);
    
    //widget_save
    QWidget* widget_button = new QWidget();
    QHBoxLayout* widget_button_layout = new QHBoxLayout(widget_button);

    QPushButton* button_save = new QPushButton("STFT-save");
    button_save->setMinimumSize(200, 50);
    button_save->setMaximumSize(200, 100);
    button_save->setStyleSheet(style_button.button_main);
    widget_button_layout->addWidget(button_save, 0, Qt::AlignHCenter);
    layout_stft->addWidget(widget_button);

    ///slot
    connect(STFT_button, SIGNAL(clicked()), this, SLOT(calculate_stft_main()));
}
//stft计算主体
void Qt_segy_process::calculate_stft_main() {


    textEdit1->append(tr("window_size:%1 ").arg(stft_windows_size->value()));//增加信息
    textEdit1->append(tr("hop_length:%1 ").arg(stft_hop_length->value()));//增加信息
    int window_size = stft_windows_size->value();

    int hop_length = stft_hop_length->value();
    const double PI = 3.14159265358979323846;
    //定义汉宁窗函数
    std::vector<double> hann_window(window_size);
    for (int i = 0; i < window_size; ++i) {
        hann_window[i] = 0.5 - 0.5 * std::cos(2 * PI * i / (window_size - 1));
    }
    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    int data_tracei = stft_trace_i->value();
    signal_stft_i.clear();

    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_stft_i.push_back(data[i][data_tracei]);//得到一维向量data
    }
    series_stft->clear();
    for (int i = 0; i < signal_stft_i.size(); i++) {//添加道数据显示
        series_stft->append(i, signal_stft_i[i]);
    }

    auto stft_result = stft(signal_stft_i, window_size, hop_length, hann_window);//这里计算
    std::vector<std::vector<float>> abs_stft_result;
    abs_stft_result.clear();
    abs_stft_result.clear();
    for (const auto& frame : stft_result) {
        std::vector<float> abs_frame;
        for (const auto& freq : frame) {
            abs_frame.push_back(std::abs(freq));
        }
        abs_stft_result.push_back(abs_frame);
    }
    data2d2image(abs_stft_result);
    textEdit1->append(tr("stft_shape:time%1 fre%2").arg(abs_stft_result.size()).arg(abs_stft_result[0].size()));//增加信息
    QString message = QString("run_stft_completed");
    ui.statusBar->showMessage(message,3000);
}
double Qt_segy_process::abs(std::complex<double> z) {//返回复数的模长
    return std::sqrt(z.real() * z.real() + z.imag() * z.imag());
}
//stft函数
std::vector<std::vector<std::complex<double>>> Qt_segy_process::stft(const std::vector<double> signal, int window_size, int hop_length, const std::vector<double> window_fn) {
    const double PI = 3.14159265358979323846;
    // 计算频率轴上的分辨率
    double freq_resolution = 1.0 / window_size;
    // 计算需要进行STFT的帧数
    int num_frames = (signal.size() - window_size) / hop_length + 1;
    // 初始化输出结果数组
    std::vector<std::vector<std::complex<double>>> result(num_frames,
        std::vector<std::complex<double>>(window_size / 2 + 1));
    stylesheet_QT style_bar;
    int progressValue;
    progress_bar = new QProgressBar();//设置进度条
    progress_bar->setMinimumSize(800, 100);
    progress_bar->setWindowTitle("Qt_segy_process::myst progress");
    progress_bar->setStyleSheet(style_bar.style_bar);
    progress_bar->setRange(0, 100); // 设置进度条的范围为0到100
    progress_bar->show();
    for (int i = 0; i < num_frames; ++i) {
        QApplication::processEvents();
        progressValue = (i+1) * 100 / num_frames; // 计算整数进度值
        progress_bar->setValue(progressValue);
        qDebug() << progressValue;//输出窗口显示处理进度
        if (progressValue == 100) {
            // 进度达到100，隐藏或关闭进度条
            progress_bar->hide(); // 或 progress->close();
        }
        // 获取当前窗口中的数据样本，并将其乘以窗函数
        std::vector<double> frame(window_size);
        for (int j = 0; j < window_size; ++j) {
            frame[j] = signal[i * hop_length + j] * window_fn[j];
        }
        // 对当前窗口进行FFT计算，并将结果存储在输出数组中
        for (int k = 0; k <= window_size / 2; ++k) {
            std::complex<double> sum(0);
            for (int n = 0; n < window_size; ++n) {
                double angle = -2 * PI * k * n / window_size;
                sum += frame[n] * std::polar(1.0, angle);
            }
            result[i][k] = sum;
        }
    }
    return result;

}
//绘制曲线
void Qt_segy_process::drawcurve()
{
    QChart* chart = new QChart();
    QChartView* chartview = new QChartView();
    QSplineSeries* series = new QSplineSeries();//1
    chart->addSeries(series);//2

    for (int i = 0; i <= 10; i++) {
        series->append(i, i * i);
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

    chartview->setChart(chart);

    axisX->setRange(0, 10);
    axisY->setRange(0, 10);

    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->show();}
///音频输入读取并显示
void Qt_segy_process::draw_audio_curve2() {

    const QAudioDevice inputDevice = QMediaDevices::defaultAudioInput();//检查设备是否可以使用
    if (inputDevice.isNull()) {
        QMessageBox::warning(nullptr, "audio",
            "There is no audio input device available.");
        return;
    }
    else {
        ui.statusBar->showMessage("ok");
    }
    m_chart = new QChart();
    m_series = new QSplineSeries();//1
    m_chart->addSeries(m_series);//2

    QWidget* widget = new QWidget();
    widget->setMinimumWidth(600);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    auto chartview = new QChartView(m_chart);
    chartview->setMinimumHeight(400);
    chartview->setStyleSheet("backgroung-color:black");
    QTextEdit* textedit = new QTextEdit();

    QString message = QString("inputDevice%1").arg(inputDevice.description());
    textedit->setText(message);
    textedit->setMaximumHeight(200);
    textedit->setStyleSheet("background-color:rgb(255,255,255);font-size:20px; ");

    layout->addWidget(chartview);
    layout->addWidget(textedit);

    //设置音频采样格式
    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleFormat(QAudioFormat::UInt8);
    //判断采样格式是否支持
    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    //if (!info.isFormatSupported(formatAudio)) {
    //    qWarning() << "Raw audio format not supported by backend, cannot play audio.";
    //    ui.statusBar->showMessage(" format mistake! error!");
    //    return;
    //}
    //else {
    //    ui.statusBar->showMessage(" format ok");
    //}
    //// 创建坐标轴
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    auto axisX = new QValueAxis;
    axisX->setTitleText("time"); // 设置坐标轴标签
    axisX->setTitleFont(font);
    axisX->setRange(0, XYSeriesIODevice::sampleCount);
    auto axisY = new QValueAxis;
    axisY->setTitleText("Audio level");
    axisY->setTitleFont(font);
    axisY->setRange(-0.5, 0.5);
    m_chart->addAxis(axisX, Qt::AlignBottom);// 将坐标轴添加到 QChart 中
    m_series->attachAxis(axisX);// 将系列关联到坐标轴
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    m_chart->setTitle("Data from the microphone(" + inputDevice.description() + ")");

    m_chart->setTitleFont(font);
    m_chart->createDefaultAxes();
    m_chart->setTheme(QChart::ChartThemeLight);
    //设置音频源
    m_audioSource = new QAudioSource(inputDevice, formatAudio);
    m_audioSource->setBufferSize(500);
    //QTimer::singleShot(3000, this, &Qt_segy_process::stopRecording);//连接到记录时长
    m_device = new XYSeriesIODevice(m_series);
    m_device->open(QIODevice::WriteOnly);
    m_audioSource->start(m_device);
    //
    // 此处需要存储audio数据
    //
    widget->show();

}
void Qt_segy_process::draw_dynamic_curve() {

    QChartView* chartview = new QChartView();
    QChart* chart = new QChart();
    chartview->setChart(chart);

    axisX_dynamic = new QValueAxis();
    axisY_dynamic = new QValueAxis();

    axisX_dynamic->setTickCount(11);
    axisX_dynamic->setRange(0, 10);
    axisY_dynamic->setRange(-5, 20);

    chart->addAxis(axisX_dynamic, Qt::AlignBottom);
    chart->addAxis(axisY_dynamic, Qt::AlignLeft);

    series_dynamic = new QSplineSeries();//1顺序很重要，切记
    chart->addSeries(series_dynamic);//2
    series_dynamic->attachAxis(axisX_dynamic);//3
    series_dynamic->attachAxis(axisY_dynamic);
    /*series_dynamic->append(0, 0);*/
    QTimer* timer = new QTimer(this);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(Timeout_handler()));//已经链接起来

    timer->setInterval(100);
    chartview->show();
}
void Qt_segy_process::Timeout_handler()
{
    QDateTime dt;
    QString current_dt = dt.currentDateTime().toString("yyyy:MM:dd:hh:mm:ss:zzz");
    int rand1 = QRandomGenerator::global()->bounded(0, 10);//产生随机数

    series_dynamic->append(x_index, rand1);

    axisX_dynamic->setRange(0, x_index + 10);
    //axisY_dynamic->setRange(0, 10);
    qDebug() << x_index << rand1;
    ui.statusBar->showMessage(QString("time: %1  ").arg(current_dt), 3000);
    x_index++;
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
void  Qt_segy_process::show_data2image() {//测试输出图像

    if (dataArray_real.empty()) {//先判断数据是否初始化
        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    QWidget* data2image = new QWidget();
    QHBoxLayout* layput1 = new QHBoxLayout(data2image);
    data2image->setMinimumSize(800, 600);
    QLabel* label = new QLabel();
    label->setMinimumSize(1200, 800);
    std::vector<std::vector<float>> temp;
    temp = dataArray_real;//增益过后的数据,数据存储用
    temp = normalized(temp);
    temp = transposeMatrix(temp);
    src = dataArray2image(temp);

    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//灰度图
    label->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));

    layput1->addWidget(label);

    cv::namedWindow("dataArray_real", cv::WINDOW_NORMAL);
    cv::imshow("dataArray_real", src); // 显示colorMap
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口

    QString message = QString("dataArray_real! Trace simple %1 ;Trace number %2;").arg(dataArray_real.size()).arg(dataArray_real[0].size());
    ui.statusBar->showMessage(message);
    data2image->show();

}
///page2_center_widget_filter 包含测试部分test
void Qt_segy_process::cvdft_1d_widget() {
    
    QWidget* widget_1 = new QWidget();
    stylesheet_QT style_info;
    widget_1->setMinimumSize(600, 400);
    widget_1->setStyleSheet(style_info.widget_gray1);
    widget_1->setWindowTitle("opencv_algorithm_1dfft!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    QLabel* info_label = new QLabel("widget_hello");
    info_label->setFixedSize(200, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_info.label1);
    widget_1_layout->addWidget(info_label, 0, Qt::AlignHCenter);

    QPushButton* refresh = new  QPushButton("refresh");
    refresh->setMaximumSize(200, 50);
    refresh->setMinimumSize(200, 50);
    refresh->setStyleSheet(style_info.button_main);

    QPushButton* data_save = new  QPushButton("Save");
    data_save->setMaximumSize(200, 50);
    data_save->setMinimumSize(200, 50);
    data_save->setStyleSheet(style_info.button_main);

    QPushButton* button_close = new  QPushButton("close");
    button_close->setMaximumSize(200, 50);
    button_close->setMinimumSize(200, 50);
    button_close->setStyleSheet(style_info.button_main);

    widget_1_layout->addWidget(fft_sample_rate,0,Qt::AlignHCenter);
    fft_sample_rate->setMinimumSize(200, 50);
    fft_sample_rate->setMaximum(10000);
    fft_sample_rate->setValue(500);
    widget_1_layout->addWidget(data_trace_i, 0, Qt::AlignHCenter);
    data_trace_i->setMinimumSize(200, 50);
    data_trace_i->setMaximum(dataArray_real.size());
    data_trace_i->setValue(20);
    widget_1_layout->addWidget(refresh, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(data_save, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(button_close,0,Qt::AlignHCenter);

    //lowThresholdSlider = new QSlider(Qt::Horizontal); //可以运行但有bug，滑条移动太大会爆内存
    //lowThresholdSlider->setRange(0, dataArray_real.size());
    //lowThresholdSlider->setValue(lowThreshold);
    //highThresholdSlider = new QSlider(Qt::Horizontal);
    //highThresholdSlider->setRange(0, dataArray_real[0].size());
    //highThresholdSlider->setValue(highThreshold);
    //connect(lowThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(updateLowThreshold_row(int)));
    //connect(highThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(updateHighThreshold_col(int)));
    //widget_1_layout->addWidget(lowThresholdSlider);
    //widget_1_layout->addWidget(highThresholdSlider);
    widget_1->show();
    connect(refresh, SIGNAL(clicked()), this, SLOT(updata_opencv_fft_1d()));
    connect(data_save, SIGNAL(clicked()), this, SLOT(save_opencv_dft_i_real()));
    connect(button_close, SIGNAL(clicked()), widget_1, SLOT(close()));
}
void Qt_segy_process::save_opencv_dft_i_real() {
    save_1d_data(opencv_fft_1d_Ampli);
}
//更新低值
void Qt_segy_process::updata_opencv_fft_1d() {
    if (dataArray_real.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    int trace = data_trace_i->value();
    int sample_rate = fft_sample_rate->value();
    opencv_fft_1d(dataArray_real, trace, sample_rate);//调用opencv_fft_1d函数
}
void Qt_segy_process::updateLowThreshold_row(int value) {
    lowThreshold = value;
    // 调用Canny边缘检测并更新显示
    qDebug() << "Low Threshold: " << lowThreshold; // 添加调试输出
    update_partsegydata();
    ui.statusBar->showMessage(tr("updateCanny-LowThreshold!"), 1000);
    ui.statusBar->showMessage("updateCanny->Low Threshold: " + QString::number(value), 2000);
}
//更新高值
void Qt_segy_process::updateHighThreshold_col(int value) {
    highThreshold = value;
    // 调用Canny边缘检测并更新显示
    qDebug() << "High Threshold: " << highThreshold; // 添加调试输出
    update_partsegydata();
    ui.statusBar->showMessage(tr("updateCanny-HighThreshold!"), 1000);
    ui.statusBar->showMessage("updateCanny->High Threshold: " + QString::number(value), 2000);
}
//update局部数据更新
void Qt_segy_process::update_partsegydata() {
    std::vector<std::vector<float>> temp;
    temp = get_partsegyarray(lowThreshold, highThreshold);
    temp = normalized(temp);
    src = dataArray2image(temp);
    QImage qtImage2(src.data, src.cols, src.rows, src.step, QImage::Format_Alpha8);//灰度图
    label_picture->setPixmap(QPixmap::fromImage(qtImage2).scaled(label_picture->size()));
    cv::namedWindow("part", cv::WINDOW_NORMAL);
    cv::imshow("part", src); // 显示colorMap
    waitKey(0);
    cv::destroyAllWindows(); // 关闭所有OpenCV窗口
}
///page2_center_widget---+++++-----
void Qt_segy_process::DFT_custom_1d_widget() {
    stylesheet_QT style_dft;
    QWidget* widget_1 = new QWidget();
    stylesheet_QT style_info;
    widget_1->setMinimumSize(600, 400);
    widget_1->setStyleSheet(style_info.widget_gray1);
    widget_1->setWindowTitle("DFT_custom_1d!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    QLabel* info_label = new QLabel("Hello! Welcom to DFT_custom_1d");
    info_label->setMaximumSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_dft.label1);
    dft_trace_i = new QSpinBox();//调节windows_size数值
    dft_trace_i->setToolTip("<html><font size='4' color='black'>dft trace i!</font></html>");
    dft_trace_i->setValue(20);//default value
    dft_trace_i->setStyleSheet(style_dft.label1);
    dft_trace_i->setFixedSize(200, 50);
    dft_trace_i->setMinimum(0);
    dft_trace_i->setMaximum(1000);

    dft_trace_sample = new QSpinBox();//调节windows_size数值
    dft_trace_sample->setToolTip("<html><font size='4' color='black'>dft sample!</font></html>");
    dft_trace_sample->setValue(500);//default value
    dft_trace_sample->setStyleSheet(style_dft.label1);
    dft_trace_sample->setFixedSize(200, 50);
    dft_trace_sample->setMinimum(0);
    dft_trace_sample->setMaximum(10000);//现在没有将采样率和x轴的频谱链接，

    QPushButton* refresh = new QPushButton("Refresh");
    refresh->setFixedSize(200, 50);
    refresh->setStyleSheet(style_dft.button_main);

    QPushButton* save_data = new QPushButton("Save");
    save_data->setFixedSize(200, 50);
    save_data->setStyleSheet(style_dft.button_main);

    QPushButton* Close_button = new QPushButton("Close");
    Close_button->setFixedSize(200, 50);
    Close_button->setStyleSheet(style_dft.button_main);

    widget_1_layout->addWidget(info_label,0,Qt::AlignHCenter);
    widget_1_layout->addWidget(dft_trace_i, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(dft_trace_sample, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(refresh, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(save_data, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(Close_button, 0, Qt::AlignHCenter);
    widget_1->show();
    connect(refresh, SIGNAL(clicked()), this, SLOT(display_dft_chart_window()));
    connect(save_data, SIGNAL(clicked()), this, SLOT(save_trace_i_dft_real()));
    connect(Close_button, SIGNAL(clicked()), widget_1, SLOT(close()));
}

void Qt_segy_process::display_dft_chart_window() {
    if (dataArray_real.empty()) {//计算得到dft数据
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    std::vector<std::vector<float>>temp = dataArray_real;
    temp = transposeMatrix(temp);//T
    std::vector<float> trace_i_data;
    /*std::vector<std::complex<float>> trace_i_data_dft_result;*/
    /*std::vector<float> trace_i_data_dft_real;*/
    for (int i = 0; i < temp.size(); i++) 
    {//获取指定i的单道数据
        trace_i_data.push_back(temp[i][dft_trace_i->value()]);//得到一维向量data
    }
    trace_i_data_dft_result = discrete_fourier_transform(trace_i_data);
    
    for (int i = 0; i <= trace_i_data_dft_result.size()/2; i++)//获取一半数据，数据是对称共轭的。 
    {
        trace_i_data_dft_real.push_back(std::abs(trace_i_data_dft_result[i].real()));
    }
    data1d_2chartview(trace_i_data);
    data1d_2chartview(trace_i_data_dft_real);//傅里叶比那换结果
    trace_i_data_dft_real.clear();
}
void Qt_segy_process::save_trace_i_dft_real() {
    save_1d_data(trace_i_data_dft_real);
}
//傅里叶逆变换
void Qt_segy_process::IDFT_custom_1d_widget() {
    qDebug("IDFT");
    stylesheet_QT style_dft;
    QWidget* widget_1 = new QWidget();
    stylesheet_QT style_info;
    widget_1->setMinimumSize(600, 400);
    widget_1->setStyleSheet(style_info.widget_gray1);
    widget_1->setWindowTitle("DFT_custom_1d!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    QLabel* info_label = new QLabel("Hello! Welcom to IDFT_custom_1d");
    info_label->setMaximumSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_dft.label1);
    dft_trace_i = new QSpinBox();//调节windows_size数值
    dft_trace_i->setToolTip("<html><font size='4' color='black'>dft trace i!</font></html>");
    dft_trace_i->setValue(20);//default value
    dft_trace_i->setStyleSheet(style_dft.label1);
    dft_trace_i->setFixedSize(200, 50);
    dft_trace_i->setMinimum(0);
    dft_trace_i->setMaximum(1000);
    QPushButton* refresh = new QPushButton("Refresh");
    refresh->setFixedSize(200, 50);
    refresh->setStyleSheet(style_dft.button_main);

    QPushButton* save_data = new QPushButton("Save");
    save_data->setFixedSize(200, 50);
    save_data->setStyleSheet(style_dft.button_main);

    QPushButton* Close_button = new QPushButton("Close");
    Close_button->setFixedSize(200, 50);
    Close_button->setStyleSheet(style_dft.button_main);

    widget_1_layout->addWidget(info_label, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(dft_trace_i, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(refresh, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(save_data, 0, Qt::AlignHCenter);
    widget_1_layout->addWidget(Close_button, 0, Qt::AlignHCenter);
    widget_1->show();

    connect(refresh, SIGNAL(clicked()), this, SLOT(display_idft_chart_window()));
}
void Qt_segy_process::display_idft_chart_window() {
    if (dataArray_real.empty()) {//计算得到dft数据
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    std::vector<float> signal_real;
    std::vector<float> signal_abs;
    std::vector<float> orignal;

    signal_abs = inverse_discrete_fourier_transform(trace_i_data_dft_result);

    data1d_2chartview(signal_abs);
}

void Qt_segy_process::FFT2_FK_widget() {
    stylesheet_QT style;
    QWidget* fft_fk_widget = new QWidget();
    QVBoxLayout* fft_fk_widget_layout = new QVBoxLayout(fft_fk_widget);
    fft_fk_widget->setMinimumSize(600, 400);
    fft_fk_widget->setStyleSheet(style.widget_gray1);
    fft_fk_widget->setWindowTitle("DFT_custom_1d!");
    QLabel* info_label = new QLabel("Hello! Welcom to fft2d-fk widget");
    info_label->setMaximumSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style.label1);

    QPushButton* refresh = new QPushButton("fft2d-FK-T");
    refresh->setFixedSize(200, 50);
    refresh->setStyleSheet(style.button_main);

    QPushButton* Save = new QPushButton("Save");
    Save->setFixedSize(200, 50);
    Save->setStyleSheet(style.button_main);

    QPushButton* Close_button = new QPushButton("Close");
    Close_button->setFixedSize(200, 50);
    Close_button->setStyleSheet(style.button_main);

    fft_fk_widget_layout->addWidget(info_label, 0, Qt::AlignHCenter);
    fft_fk_widget_layout->addWidget(refresh, 0, Qt::AlignHCenter);
    fft_fk_widget_layout->addWidget(Save, 0, Qt::AlignHCenter);
    fft_fk_widget_layout->addWidget(Close_button, 0, Qt::AlignHCenter);
    fft_fk_widget->show();
    connect(refresh, SIGNAL(clicked()), this, SLOT(FFT2_FK()));
    connect(Close_button, SIGNAL(clicked()), fft_fk_widget, SLOT(close()));
    connect(Save, SIGNAL(clicked()), this, SLOT(FFT2_FK_save()));

}
//fk-main
void Qt_segy_process::FFT2_FK() { 

    if (dataArray_real.empty()) {//计算得到dft数据
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    std::vector<std::vector<float>> step_t;
    std::vector<std::vector<float>> step_x;
    step_t = FFT2_FK_t((dataArray_real));
    data2d2image(step_t);
    step_x = FFT2_FK_t(transposeMatrix(step_t));
    data2d2image(transposeMatrix(step_x));
    FFT2_FK_data = step_t;
}
//run-fk
std::vector<std::vector<float>> Qt_segy_process::FFT2_FK_t(std::vector<std::vector<float>> data_2d) {

    std::vector<std::vector<float>> temp = data_2d;
    temp = transposeMatrix(temp); // Assuming transposeMatrix is properly implemented
    std::vector<float> trace_i_data;
    std::vector<std::complex<float>> trace_i_data_fft2;
    std::vector<std::vector<std::complex<float>>> fft2;
    std::vector<std::vector<float>> fft2_real(temp[0].size(), std::vector<float>(temp.size(), 0.0));
    stylesheet_QT style_bar;
    int progressValue;
    progress_bar = new QProgressBar();//设置进度条
    progress_bar->setMinimumSize(800, 100);
    progress_bar->setWindowTitle("Qt_segy_process::myst progress");
    progress_bar->setStyleSheet(style_bar.style_bar);
    progress_bar->setRange(0, 100); // 设置进度条的范围为0到100
    progress_bar->show();
    for (int j = 0; j < temp[0].size(); j++) { // Loop through each channel
        //
        QApplication::processEvents();
        progressValue = (j + 1) * 100 / temp[0].size(); // 计算整数进度值
        progress_bar->setValue(progressValue);
        qDebug() << progressValue;//输出窗口显示处理进度
        if (progressValue == 100) {
            // 进度达到100，隐藏或关闭进度条
            progress_bar->hide(); // 或 progress->close();
        }
        trace_i_data.clear(); // Clear trace_i_data for the next iteration
        for (int i = 0; i < temp.size(); i++) { // Loop through each trace
            trace_i_data.push_back(temp[i][j]);
        }
        trace_i_data_fft2 = discrete_fourier_transform(trace_i_data);
        fft2.push_back(trace_i_data_fft2); 
    }
    for (int j = 0; j < temp[0].size(); ++j) { // Loop through each channel
        for (int i = 0; i < temp.size(); ++i) {
            fft2_real[j][i] = std::abs(fft2[j][i].real());
        }
    }
    ui.statusBar->showMessage(tr("%1<->%2").arg(fft2_real.size()).arg(fft2_real[0].size()));
    QString message = tr("fft2_t%1<->%2").arg(fft2_real.size()).arg(fft2_real[0].size());
    textEdit1->append(message);
    return fft2_real;
}
//save fk
void Qt_segy_process::FFT2_FK_save() {
    save_2d_data(FFT2_FK_data);
    
}
///page2_right_widget--------+++++
//滤波
void Qt_segy_process::Filter_widget() {
    if (dataArray_real.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    QWidget* widget_1 = new QWidget();
    stylesheet_QT style_info;
    widget_1->setMinimumSize(600, 400);
    widget_1->setStyleSheet(style_info.widget_gray1);
    widget_1->setWindowTitle("Filter_widget!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    QString widget_gray1 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
        "Filter_widget"
        "</span>";
    QLabel* info_label = new QLabel(QString("<html>%1</html>").arg(widget_gray1));
    info_label->setFixedSize(200, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_info.label1);
    widget_1_layout->addWidget(info_label, 0, Qt::AlignHCenter);

    //chartview
    QChartView* chartView_signal = new QChartView();//orignal
    chartView_signal->setMinimumHeight(300);
    QChart*chart_signal_orignal = new QChart();
   
    series_signal_filter1d = new QSplineSeries();//1
    chart_signal_orignal->addSeries(series_signal_filter1d);//2

    QChartView* chartView_result = new QChartView();//result
    chartView_result->setMinimumHeight(300);
    QChart* chart_signal_result = new QChart();

    filter1d_signal_result = new QSplineSeries();//1
    chart_signal_result->addSeries(filter1d_signal_result);//2

    widget_1_layout->addWidget(chartView_signal);
    widget_1_layout->addWidget(chartView_result);

    //parameter
    QWidget* parameter_widget = new QWidget();//设置参数窗口
    parameter_widget->setMinimumHeight(100);
    QHBoxLayout* parameter_layout = new QHBoxLayout(parameter_widget);

    filter1d_tracei = new QSpinBox();
    filter1d_tracei->setToolTip("tracei");
    filter1d_tracei->setMaximumSize(200, 50);
    filter1d_tracei->setValue(20);

    filter1d_tracei->setMaximum(data.size());
    filter1d_tracei->setStyleSheet(style_info.label1);

    ComboBox_filter1d_type = new QComboBox();//添加滤波类型选项
    ComboBox_filter1d_type->setStyleSheet(style_info.label1);
    ComboBox_filter1d_type->setMaximumSize(200, 50);
    ComboBox_filter1d_type->addItem("medianFilter");
    ComboBox_filter1d_type->addItem("type2");
    ComboBox_filter1d_type->addItem("type3");

    kernelsize_filter1d = new QSpinBox();//kernelsize
    kernelsize_filter1d->setToolTip("kernelsize");
    kernelsize_filter1d->setMaximumSize(200, 50);
    kernelsize_filter1d->setValue(5);
    kernelsize_filter1d->setStyleSheet(style_info.label1);

    parameter_layout->addWidget(filter1d_tracei);
    parameter_layout->addWidget(ComboBox_filter1d_type);
    parameter_layout->addWidget(kernelsize_filter1d);
    //setchart
    int tracei = filter1d_tracei->value();
    signal_filter1d_tracei.clear();
    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_filter1d_tracei.push_back(data[i][tracei]);//得到一维向量data
    }
    for (int i = 0; i < signal_filter1d_tracei.size(); i++) {//添加道数据显示
        series_signal_filter1d->append(i, signal_filter1d_tracei[i]);
        filter1d_signal_result->append(i, signal_filter1d_tracei[i]);
    }
    chartView_signal->setChart(chart_signal_orignal);
    chartView_result->setChart(chart_signal_result);

    QValueAxis* axisX = new QValueAxis();//添加坐标轴
    QValueAxis* axisY = new QValueAxis();
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("sample");
    axisY->setTitleText("Amp");
    axisX->setTickCount(11);//设置刻度数量
    axisY->setTickCount(11);

    chart_signal_orignal->addAxis(axisX, Qt::AlignBottom);//设置原始信号
    chart_signal_orignal->addAxis(axisY, Qt::AlignLeft);
    series_signal_filter1d->attachAxis(axisX);
    series_signal_filter1d->attachAxis(axisY);

    QValueAxis* axisX2 = new QValueAxis();//添加坐标轴
    QValueAxis* axisY2 = new QValueAxis();
    QFont font2;
    font.setPointSize(20);  // 设置字体大小
    axisX2->setTitleFont(font2);
    axisY2->setTitleFont(font2);
    axisX2->setTitleText("sample");
    axisY2->setTitleText("Amp");
    axisX2->setTickCount(11);//设置刻度数量
    axisY2->setTickCount(11);
    
    chart_signal_result->addAxis(axisX2, Qt::AlignBottom);//设置处理后信号
    chart_signal_result->addAxis(axisY2, Qt::AlignLeft);
    filter1d_signal_result->attachAxis(axisX2);
    filter1d_signal_result->attachAxis(axisY2);

    auto minElement = std::min_element(signal_filter1d_tracei.begin(), signal_filter1d_tracei.end());
    auto maxElement = std::max_element(signal_filter1d_tracei.begin(), signal_filter1d_tracei.end());
    double min = *minElement;
    double max = *maxElement;
    axisX->setRange(0, signal_filter1d_tracei.size());
    axisY->setRange(min * 1.2, max * 1.2);
    axisY->setLabelFormat("%.1f"); // 显示一位小数
    QString chartTitle = QString("Chart-Trace original %1").arg(tracei);
    chart_signal_orignal->setTitle(chartTitle);
    chart_signal_orignal->setTitleFont(font);
    chartView_signal->setRenderHint(QPainter::Antialiasing);

    axisX2->setRange(0, signal_filter1d_tracei.size());
    axisY2->setRange(min * 1.2, max * 1.2);
    axisY2->setLabelFormat("%.1f"); // 显示一位小数
    QString chartTitle2 = QString("Chart-Filtered %1").arg(tracei);
    chart_signal_result->setTitle(chartTitle2);
    chart_signal_result->setTitleFont(font2);
    chartView_result->setRenderHint(QPainter::Antialiasing);
    

    QWidget* button_widget = new QWidget();
    button_widget->setMinimumHeight(100);
    QHBoxLayout* button_layout = new QHBoxLayout(button_widget);

    QPushButton* run = new  QPushButton("run");
    run->setMaximumSize(200, 50);
    run->setMinimumSize(200, 50);
    run->setStyleSheet(style_info.button_main);
    QPushButton* button_save = new  QPushButton("save");
    button_save->setMaximumSize(200, 50);
    button_save->setMinimumSize(200, 50);
    button_save->setStyleSheet(style_info.button_main);
    
    button_layout->addWidget(button_save, 0, Qt::AlignHCenter);
    QPushButton* button_close = new  QPushButton("close");
    button_close->setMaximumSize(200, 50);
    button_close->setMinimumSize(200, 50);
    button_close->setStyleSheet(style_info.button_main);
    button_layout->addWidget(run, 0, Qt::AlignHCenter);
    button_layout->addWidget(button_save, 0, Qt::AlignHCenter);
    button_layout->addWidget(button_close, 0, Qt::AlignHCenter);

    widget_1_layout->addWidget(parameter_widget);
    widget_1_layout->addWidget(button_widget);

    widget_1->show();
    connect(run, SIGNAL(clicked()), this, SLOT(filter1d_process()));
    connect(button_save, SIGNAL(clicked()), this, SLOT(save_filter1d_data()));
    connect(button_close, SIGNAL(clicked()), widget_1, SLOT(close()));
}
void Qt_segy_process::filter1d_process() {

    if (dataArray_real.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;//返回默认vector
    }
    vector<std::vector<float>> data;
    data = transposeMatrix(dataArray_real);
    int tracei=filter1d_tracei->value();


    signal_filter1d_tracei.clear();
    for (int i = 0; i < data.size(); i++) {//获取指定i的单道数据
        signal_filter1d_tracei.push_back(data[i][tracei]);//得到一维向量data
    }
    series_signal_filter1d->clear();
    for (int i = 0; i < signal_filter1d_tracei.size(); i++) {//添加道数据显示
        series_signal_filter1d->append(i, signal_filter1d_tracei[i]);
    }
    int filter1dType = ComboBox_filter1d_type->currentIndex();
    if (filter1dType == 0) {
        filter1d_signal_result->clear();

        std::vector<double> resultData;
        resultData.reserve(signal_filter1d_tracei.size());
        if (kernelsize_filter1d->value() % 2 == 0) {
            kernelsize_filter1d->setValue(kernelsize_filter1d->value() + 1);
            QString message = QString("kernelsize must be odd ,changed to %1").arg(kernelsize_filter1d->value());
            ui.statusBar->showMessage(message);
        }
        resultData=medianFilter(signal_filter1d_tracei, kernelsize_filter1d->value());

        for (int i = 0; i < signal_filter1d_tracei.size(); i++) {//添加道数据显示

            filter1d_signal_result->append(i, resultData[i]);
        }
    }
    else if (filter1dType == 1) {
        filter1d_signal_result->clear();
        for (int i = 0; i < signal_filter1d_tracei.size(); i++) {//添加道数据显示

            filter1d_signal_result->append(i, signal_filter1d_tracei[i]*2);
        }
    }
}
void Qt_segy_process::save_filter1d_data() {

    std::vector<float> floatVector(signal_filter1d_tracei.size());
    std::transform(signal_filter1d_tracei.begin(), signal_filter1d_tracei.end(), floatVector.begin(), [](double d) {
        return static_cast<float>(d);
        });//double->floata
    save_1d_data(floatVector);
}
//Filter-中值滤波
std::vector<double> Qt_segy_process::medianFilter(std::vector<double> inputSignal, int kernelSize) {
    std::vector<double> resultData;
    resultData.reserve(inputSignal.size());
    for (int i = 0; i < inputSignal.size(); ++i) {
        // 计算邻域的起始和结束索引
        int startIdx = std::max(0, i - kernelSize / 2);
        int endIdx = std::min(static_cast<int>(inputSignal.size()) - 1, i + kernelSize / 2);
        // 从邻域中提取数据
        std::vector<double> neighborhood(inputSignal.begin() + startIdx, inputSignal.begin() + endIdx + 1);
        // 对邻域进行排序
        std::sort(neighborhood.begin(), neighborhood.end());//排序取中间值，而不是平均数。

        // 计算中值并添加到结果中
        double medianValue = neighborhood[neighborhood.size() / 2];//取中间索引
        resultData.push_back(medianValue);
    }

    return resultData;
}
//page3
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
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
    std::vector<std::vector<float>> matrix;
    if (dataArray_real.empty())
    {//先判断数据是否初始化

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
void Qt_segy_process::WiggleView_show_V() {//地震道垂直放置，常规方式
    stylesheet_QT style1;
    ui.statusBar->setStyleSheet(style1.styleSheet_bar);
    std::vector<std::vector<float>> matrix;
    if (dataArray_real.empty()) {//判断数据
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
    label_dial_1 = new QLabel("trace space");
    label_dial_1->setAlignment(Qt::AlignHCenter);

    wiggle_dial_2 = new QDial();
    wiggle_dial_2->setRange(1, 5);  wiggle_dial_2->setSingleStep(1); wiggle_dial_2->setValue(1);//设置初始值
    wiggle_dial_2->setNotchesVisible(true);
    label_dial_2 = new QLabel("height Value");
    label_dial_2->setAlignment(Qt::AlignHCenter);

    wiggle_dial_3 = new QDial();
    wiggle_dial_3->setNotchesVisible(true);
    wiggle_dial_3->setRange(0, 100);  wiggle_dial_3->setSingleStep(1); wiggle_dial_3->setValue(20);//设置初始值
    label_dial_3 = new QLabel("max Value");
    label_dial_3->setAlignment(Qt::AlignHCenter);

    wiggle_dial_4 = new QDial();
    wiggle_dial_4->setNotchesVisible(true);
    wiggle_dial_4->setRange(1, 10);  wiggle_dial_4->setSingleStep(1); wiggle_dial_4->setValue(1);//设置初始值
    label_dial_4 = new QLabel("ine width");
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
    traceSpacing = wiggle_dial_1->value();//道间距
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
//保存QGraphicsView* view图像,已封装
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
//page4//part_left_3d绘图
void Qt_segy_process::draw3DData() {
    if (dataArray_real.empty()) {//先判断数据是否初始化
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
    series->setItemSize(0.05);
    series->setBaseColor(Qt::darkBlue);
    // 添加数据
    QScatterDataArray data;
    std::vector<std::vector<float>> matrixData;
    dataArray = normalized(dataArray_real);
    matrixData = dataArray;
    // 将 matrixData 转换为 QVector<QVector3D>
    for (int i = 0; i < dataArray_real.size(); ++i) {
        for (int j = 0; j < dataArray_real[i].size(); ++j) {
            data << QVector3D(i, j, matrixData[i][j]*10);
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
QColor getColorBasedOnValue(float value) {
    // 你可以根据具体的需求来定义颜色映射逻辑
    // 这里是一个简单的例子，将数据值映射到蓝色到红色的渐变色
    // 设置颜色映射范围
    float minValue = 0.0;
    float maxValue = 100.0;

    // 映射数据值到 [0, 1] 范围
    float normalizedValue = (value - minValue) / (maxValue - minValue);
    
    // 计算颜色
    int r = static_cast<int>((1.0 - normalizedValue) * 255);
    int b = static_cast<int>(normalizedValue * 255);

    // 返回颜色
    return QColor(r, 0, b);
}
void Qt_segy_process::draw3Dsurface() {
   // // 创建 Q3DSurface
   //Q3DSurface* surface = new Q3DSurface();
   // // 创建数据代理
   // QSurfaceDataProxy* dataProxy = new QSurfaceDataProxy();
   // // 创建曲面系列
   // QSurface3DSeries* series = new QSurface3DSeries(dataProxy);
   // 

   // // 创建数据
   // int rows = 100;
   // int columns = 100;

   // for (int i = 0; i < rows; ++i) {
   //     QSurfaceDataRow* dataRow = new QSurfaceDataRow();
   //     for (int j = 0; j < columns; ++j) {
   //         float x = static_cast<float>(i);
   //         float y = static_cast<float>(j);
   //         float z = static_cast<float>(qSin(qDegreesToRadians(x)) + qCos(qDegreesToRadians(y))); // 你的高程数据计算方式
   //         *dataRow << QVector3D(x, y, z);
   //     }
   //     dataProxy->addRow(dataRow);
   // }
   // surface->addSeries(series);
   // qDebug() << "OpenGL Version:" << QSurfaceFormat::defaultFormat().version();

   // // 设置坐标轴标题
   // surface->axisX()->setTitle("X Axis");
   // surface->axisY()->setTitle("Y Axis");
   // surface->axisZ()->setTitle("Z Axis");
   // surface->show();
    QString message = "unopen";
    ui.statusBar->showMessage(message);
    
}
//page5
void Qt_segy_process::Syn_widget() {

    QWidget *widget_syn = new QWidget();
    stylesheet_QT style_info;

    widget_syn->setMinimumSize(600, 400);
    widget_syn->setStyleSheet(style_info.widget_gray1);
    widget_syn->setWindowTitle("widget_syn");

    QVBoxLayout* widget_syn_layout = new QVBoxLayout(widget_syn);

    QLabel* info_label = new QLabel("widget_syn");
    info_label->setFixedSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_info.label1);

    QWidget* widget_1 = new QWidget();
    widget_1->setMinimumHeight(200);
    widget_1->setStyleSheet(style_info.widget_gray1);
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);



    widget_syn_layout->addWidget(info_label, 0, Qt::AlignHCenter);
    widget_syn_layout->addWidget(widget_1);


    QPushButton*info_close = new QPushButton("close");
    info_close->setMinimumSize(100, 30);
    info_close->setMaximumSize(160, 50);
    info_close->setStyleSheet(style_info.button_main);

    widget_syn_layout->addWidget(info_close, 0, Qt::AlignHCenter);
    widget_syn->show();
    //状态栏变化
    ui.statusBar->setStyleSheet(style_info.styleSheet_bar);
    QString message = QString("The window has opened.Information has been shown");
    ui.statusBar->showMessage(message);
    ///slot
    connect(info_close, SIGNAL(clicked()), widget_syn, SLOT(close()));//槽函数内部实现关闭;

}
///packed_start*****************packed_start
//对保存一维数据函数进行封装
void Qt_segy_process::save_1d_data(std::vector<float> data_1d) {
    //将需要存储的数据传入
    if (data_1d.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;
    }
    std::ofstream fileout;
    QString SaveFile_segy = QFileDialog::getSaveFileName(this,//对话框得到存储路径
        "Save data",
        "",
        "Data Files(*.txt*.csv);;All(*.*)");
    std::string filePath = SaveFile_segy.toStdString();//Qstring-->string

    fileout.open(filePath);  // Open the output file
    if (!fileout.is_open())
    {
        std::cout << "Can not open File " << filePath << std::endl;
        return;
    }
    
    // Write the 1D vector to the output file
    for (int i = 0; i < data_1d.size(); i++)
    {
        fileout << data_1d[i];
        fileout << std::endl;
    }
    fileout.close();
    ui.statusBar->showMessage(tr("saved data successfully!"));
}
//对保存二维数据函数进行封装
void Qt_segy_process::save_2d_data(std::vector<std::vector<float>> data_2d) {
    if (data_2d.empty()) {
        qDebug() << "data is empty. Make sure to load data first!";
        ui.statusBar->showMessage(tr("data is empty. Make sure to load data first!"), 3000);
        return;
    }
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
    dataArray_save = data_2d;//将需要存储的数据传入
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
    ui.statusBar->showMessage(tr("saved 2d data successfully!"));
}
//数据转图表data1d_2chartview封装
void Qt_segy_process::data1d_2chartview(std::vector<float> data) {
    if (data.empty())
    {//先判断数据是否初始化
        ui.statusBar->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 red);font-size:20px;");
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    ///QChartView绘图
    QChartView* ChartView_widget = new QChartView();
    QChart* chart = new QChart();
    QSplineSeries* series = new QSplineSeries();
    // 将 std::vector<float> 中的数据添加到 QSplineSeries 中
    for (size_t i = 0; i < data.size(); ++i) {
        series->append(i, data[i]);
    }
    chart->addSeries(series);
    // 创建坐标轴
    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;
    // 设置坐标轴标签
    axisX->setTitleText("X");
    axisY->setTitleText("Y");
    QFont font;
    font.setPointSize(20);  // 设置字体大小
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);

    // 计算数据的最大值
    float maxDataValue = *std::max_element(data.begin(), data.end());
    float minDataValue = *std::min_element(data.begin(), data.end());
    // 设置Y轴最大值为data数据最大值的1.2倍
    axisY->setMax(maxDataValue * 1.2);
    axisY->setMin(minDataValue * 1.2);
    // 将坐标轴添加到 QChart 中
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将系列关联到坐标轴
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();
    QString message = QString("series %1").arg(data.size());

    chart->setTitle(message);
    chart->setTitleFont(font);
    //chart->createDefaultAxes();
    chart->setTheme(QChart::ChartThemeLight);
    ChartView_widget->setChart(chart);
    ChartView_widget->show();
    return;
}
//二维数据直接转换为图像cv显示封装
void Qt_segy_process::data2d2image(std::vector<std::vector<float>> dataArray) {
    if (dataArray.empty())
    {//先判断数据是否初始化
        ui.statusBar->showMessage(tr("Data is not initialized, please load the data first."), 3000);
        return;
    }
    dataArray = normalized(dataArray);
    dataArray = transposeMatrix(dataArray);
    cv::Mat image_temp(dataArray.size(), dataArray[0].size(), CV_8U);//获取到二维数组的行和列；
    for (int i = 0; i < dataArray.size(); ++i) {
        for (int j = 0; j < dataArray[i].size(); ++j) {
            // 假设 dataArray 的元素是 [0, 1] 范围内的浮点数
            image_temp.at<uchar>(i, j) = dataArray[i][j] * 255;
        }
    }
    cv::Mat colorMap;
    applyColorMap(image_temp, colorMap, cv::COLORMAP_JET); // 使用Jet颜色映射，你可以选择其他映射
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
    // 添加标签
    /*cv::putText(image_temp, "Original Image", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.1, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
    cv::putText(colorMap, "Color Mapped Image", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.1, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);*/

    // 将OpenCV图像转换为Qt图像
    stylesheet_QT style1;
    QWidget* label_widget = new QWidget();
    label_widget->setMaximumSize(900, 700);
    label_widget->setStyleSheet("background-color:#ffffff");
    QVBoxLayout* lable_layout = new QVBoxLayout(label_widget);

    QLabel* label_Xaxis = new QLabel("---------Axis---------->");
    label_Xaxis->setMaximumHeight(40);
    label_Xaxis->setMinimumWidth(800);
    // 设置字体垂直居中对齐
    label_Xaxis->setAlignment(Qt::AlignHCenter);
    label_Xaxis->setStyleSheet("color:#FFFFFF;background-color:#374357;font-size:20px;padding: 5px;font-style: italic;font-weight: bold;");

    QWidget* label_widget2 = new QWidget();
    QVBoxLayout* lable_layout2 = new QVBoxLayout(label_widget2);

    QLabel* label = new QLabel();
    label->setMinimumSize(800, 600);
    cv::Mat rgbImage;
    cv::cvtColor(colorMap, rgbImage, cv::COLOR_BGR2RGB);
    QImage qtImage(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);

    label->setPixmap(QPixmap::fromImage(qtImage).scaled(label->size()));

    lable_layout2->addWidget(label,0, Qt::AlignHCenter);
    lable_layout->addWidget(label_Xaxis,0, Qt::AlignHCenter);
    lable_layout -> addWidget(label_widget2, 0, Qt::AlignHCenter);
    label_widget->show();

    //cv::namedWindow("Original", cv::WINDOW_NORMAL);
    //cv::imshow("Original", image_temp); // 显示原始图像
    //cv::namedWindow("colormap", cv::WINDOW_NORMAL);
    //cv::imshow("colormap", colorMap); // 显示原始图像
    //waitKey(0);
    //cv::destroyAllWindows(); // 关闭所有OpenCV窗口
    ui.statusBar->showMessage(tr("dataarray2image complete!"), 2000);
}
void Qt_segy_process::drawAxes(QImage& image) {//在图片上绘制西那段，并返回
    QPainter painter(&image);

    // 设置坐标轴颜色和宽度
    painter.setPen(QPen(Qt::blue, 2));

    // 绘制横轴
    painter.drawLine(0, image.height() / 2, image.width(), image.height() / 2);

    // 绘制纵轴
    painter.drawLine(image.width() / 2, 0, image.width() / 2, image.height());
}
//Mat转Qimage
QImage Qt_segy_process::Mat2QImage(const cv::Mat& mat) {
    if (mat.empty()) {
        qDebug() << "Error: Input image is empty";
        return QImage();
    }
    // Convert the OpenCV image to a QImage
    QImage image(mat.cols, mat.rows, QImage::Format_Grayscale8);
    for (int y = 0; y < mat.rows; ++y) {
        for (int x = 0; x < mat.cols; ++x) {
            // Assuming that the pixel values in the cv::Mat are uchar (8-bit)
            image.setPixel(x, y, mat.at<uchar>(y, x));
        }
    }

    return image;
}
//Qimage转Mat
cv::Mat Qt_segy_process::QImage2Mat(const QImage& image) {
    cv::Mat mat(image.height(), image.width(), CV_8U);
    uchar* matData = mat.data;
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            matData[y * image.width() + x] = qRed(image.pixel(x, y));
        }
    }
    return mat;
}
///packed_end*****************packed_end
//toolbar setting
void  Qt_segy_process::setting_header() {
    stylesheet_QT style_setting;
    QWidget* widget_setting_main = new QWidget();
    stylesheet_QT style_info;
    widget_setting_main->setMinimumSize(600, 400);
    /*widget_1->setMaximumSize(800, 600);*/
    widget_setting_main->setStyleSheet(style_info.widget_gray1);
    widget_setting_main->setWindowTitle("DFT_custom_1d!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_setting_main);
    QLabel* info_label = new QLabel("Hello! Welcom to Setting_widget");
    info_label->setMaximumSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_setting.label1);
    //header_sample
    QWidget* header_sample_widget = new QWidget();
    QHBoxLayout* header_sample_widget_layout = new QHBoxLayout(header_sample_widget);
    header_sample_widget->setStyleSheet(style_setting.widget_glass);
    header_sample_widget->setMaximumHeight(100);
    QLabel* info_samplerate = new QLabel("sample_rate-value");
    info_samplerate->setMaximumSize(400, 50);
    info_samplerate->setAlignment(Qt::AlignCenter);
    info_samplerate->setStyleSheet(style_setting.label1);
    header_samplerate = new QSpinBox();//调节windows_size数值
    header_samplerate->setToolTip("<html><font size='4' color='black'>header_sample!</font></html>");
    header_samplerate->setValue(500);//default value
    header_samplerate->setStyleSheet(style_setting.label1);
    header_samplerate->setMaximumSize(400, 50);
    header_samplerate->setMinimum(0);
    header_samplerate->setMaximum(100000);
    header_sample_widget_layout->addWidget(info_samplerate);
    header_sample_widget_layout->addWidget(header_samplerate);

    //header_trace_
    QWidget* header_samplenumber_widget = new QWidget();
    QHBoxLayout* header_samplenumber_widget_layout = new QHBoxLayout(header_samplenumber_widget);
    header_samplenumber_widget->setStyleSheet(style_setting.widget_glass);
    header_samplenumber_widget->setMaximumHeight(100);
    QLabel* info_samplenumber = new QLabel();
    QString message_header_samplenumber = "sample number";
    QLabel* info_tracenumber = new QLabel();
    QString message_header_tracenumber = "trace number";
    if (dataArray.empty()) {//添加判断
        info_samplenumber->setText("null");
        info_tracenumber->setText("null");
    }
    else {
        info_samplenumber->setText(tr("samplenumber:%1").arg(dataArray.size()));
        info_tracenumber->setText(tr("samplenumber:%1").arg(dataArray[0].size()));
    }
    info_samplenumber->setMaximumSize(400, 50);
    info_tracenumber->setMaximumSize(400, 50);
    /*info_samplenumber->setAlignment(Qt::AlignCenter);*/
    info_samplenumber->setStyleSheet(style_setting.label1);
    info_tracenumber->setStyleSheet(style_setting.label1);
 
    header_samplenumber_widget_layout->addWidget(info_samplenumber);
    header_samplenumber_widget_layout->addWidget(info_tracenumber);

    QPushButton* button_confirm = new QPushButton("confirm");
    button_confirm->setFixedSize(200, 50);
    button_confirm->setStyleSheet(style_setting.button_main);
    QPushButton* button_close = new QPushButton("close");
    button_close->setFixedSize(200, 50);
    button_close->setStyleSheet(style_setting.button_main);

    widget_1_layout->addWidget(info_label,0,Qt::AlignHCenter);
    widget_1_layout->addWidget(header_sample_widget,Qt::AlignHCenter);
    widget_1_layout->addWidget(header_samplenumber_widget,Qt::AlignHCenter);
    widget_1_layout->addWidget(button_confirm,0,Qt::AlignHCenter);
    widget_1_layout->addWidget(button_close,0,Qt::AlignHCenter);
    widget_setting_main->show();
    
    connect(button_confirm, SIGNAL(clicked()), this, SLOT(confirm_header()));
    connect(button_close, SIGNAL(clicked()), widget_setting_main, SLOT(close()));
}
void Qt_segy_process::confirm_header() {//确认
    QString message_header_confirm = "@confirm header";
    ui.statusBar->showMessage(message_header_confirm);
    textEdit1->append(tr("sample_rate_value:%1 ").arg(header_samplerate->value()));
    if (!dataArray.empty()) {//添加判断
        textEdit1->append(tr("info_samplenumber:%1 ").arg(dataArray.size()));
        textEdit1->append(tr("info_tracenumber:%1 ").arg(dataArray[0].size()));
    }
}
void Qt_segy_process::changeAllStyles_widget() {
    stylesheet_QT style_setting;
    QWidget* widget_setting_main = new QWidget();
    
    widget_setting_main->setMinimumSize(600, 400);
    /*widget_1->setMaximumSize(800, 600);*/
    widget_setting_main->setStyleSheet(style_setting.widget_gray1);
    widget_setting_main->setWindowTitle("Styles_widget!");
    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_setting_main);
    QLabel* info_label = new QLabel("Hello! Welcom to Styles_widget");
    info_label->setMaximumSize(600, 50);
    info_label->setAlignment(Qt::AlignCenter);
    info_label->setStyleSheet(style_setting.label1);
    //header_sample
    QWidget* header_sample_widget = new QWidget();
    QHBoxLayout* header_sample_widget_layout = new QHBoxLayout(header_sample_widget);
    QPushButton* button1 = new QPushButton("color1");
    button1->setText(QString::fromLocal8Bit("深色"));
    button1->setMaximumSize(600, 50);
    button1->setStyleSheet(style_setting.button_main);

    QPushButton* button2 = new QPushButton("color2");
    button2->setText(QString::fromLocal8Bit("浅色"));
    button2->setMaximumSize(600, 50);
    button2->setStyleSheet(style_setting.button_main);

    header_sample_widget_layout->addWidget(button1, Qt::AlignHCenter);
    header_sample_widget_layout->addWidget(button2, Qt::AlignHCenter);

    QPushButton* button_close = new QPushButton("close");
    button_close->setText(QString::fromLocal8Bit("Close"));
    button_close->setMaximumSize(600, 50);
    button_close->setStyleSheet(style_setting.button_main);

    widget_1_layout->addWidget(info_label);
    widget_1_layout->addWidget(header_sample_widget);
    widget_1_layout->addWidget(button_close, Qt::AlignHCenter);
    //slot
    connect(button1, SIGNAL(clicked()), this, SLOT(stylesheet_change_1()));
    connect(button2, SIGNAL(clicked()), this, SLOT(stylesheet_change_2()));
    connect(button_close, SIGNAL(clicked()), widget_setting_main, SLOT(close()));
    widget_setting_main->show();
}
void Qt_segy_process::stylesheet_change_1() {//样式1

    QString newStyle = "background-color:#F0F5F9;color:#1E2022;font-size:20px;border-radius:5px;border: 2px solid #C9D6DF;";
    changeAllStyles(this, newStyle);
}
void Qt_segy_process::stylesheet_change_2() {//样式2

    QString newStyle = "background-color:#1E2022;color:#F0F5F9;font-size:20px;border-radius:5px;border: 2px solid #788189;";
    changeAllStyles(this, newStyle);
}
void Qt_segy_process::changeAllStyles(QWidget* widget, const QString& newStyle) {
    widget->setStyleSheet(newStyle);
    // 遍历所有子控件
    QList<QWidget*> childWidgets = widget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
    for (QWidget* child : childWidgets) {
        changeAllStyles(child, newStyle);
    }
}
//toolbar显示version
void Qt_segy_process::show_version_info() {

    widget_info = new QWidget();
    stylesheet_QT style_info;

    widget_info->setMinimumSize(600, 400);
    widget_info->setStyleSheet(style_info.widget_gray1);
    widget_info->setWindowTitle("version!");

    QVBoxLayout* widget_info_layout = new QVBoxLayout(widget_info);

    QLabel* info_label = new QLabel("Software Information");
    info_label->setMaximumSize(600, 50);
    info_label->setStyleSheet(style_info.label1);

    QWidget* widget_1 = new QWidget();
    widget_1->setMinimumHeight(200);
    widget_1->setStyleSheet(style_info.widget_gray1);

    QVBoxLayout* widget_1_layout = new QVBoxLayout(widget_1);
    widget_info_layout->addWidget(info_label);
    widget_info_layout->addWidget(widget_1);

    QTextEdit* textEdit1 = new QTextEdit();///放置信息
    textEdit1->setReadOnly(true);
    textEdit1->setStyleSheet(style_info.textEdit);
    widget_1_layout->addWidget(textEdit1);
    textEdit1->setPlainText("Version_1.0,author by Rain!\n"
                            "Warning: This computer program is protected by copyright laws and international treaties.");
    info_close = new QPushButton("ok");
    info_close->setMinimumSize(100, 30);
    info_close->setMaximumSize(160, 50);
    info_close->setStyleSheet(style_info.button_main);

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

#pragma region //可重复利用代码块
///完成封装
//data1d_2chartview 一维数据转图表
//data2d2image二维数据转图像
//save_1d_data保存1维数据
//save_2d_data保存二维数据
//saveWiggleViewImage保存wiggle图像
///数据处理函数
//getsegyarray获取segy数据
//STStock变换计算时频谱
//Exc_min切除极小值
//opencvfft_1d
//opencvfft_2d
//discrete_fourier_transform离散傅里叶变换
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
///Qchart绘图2
//QChart* chart_s_data = new QChart();
//QWidget* widget_stockwell_fun = new QWidget();
//
//QChartView* chartView_stock = new QChartView();
//
//QVBoxLayout* layout_stock = new QVBoxLayout(widget_stockwell_fun);
//
//chartView_stock->setChart(chart_s_data);
//QSplineSeries* series_stock = new QSplineSeries();//1
//chart_s_data->addSeries(series_stock);//2
//
//for (int i = 0; i < s.size(); i++) {
//    series_stock->append(i, s[i]);
//}
////添加坐标轴
//QValueAxis* axisX = new QValueAxis();
//QValueAxis* axisY = new QValueAxis();
//QFont font;
//font.setPointSize(20);  // 设置字体大小
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//axisX->setTitleText("sample");
//axisY->setTitleText("Amp");
//axisX->setTickCount(11);//设置刻度数量
//axisY->setTickCount(11);
//chart_s_data->addAxis(axisX, Qt::AlignBottom);//设置位置
//chart_s_data->addAxis(axisY, Qt::AlignLeft);
//series_stock->attachAxis(axisX);
//series_stock->attachAxis(axisY);
//
//chartView_stock->setChart(chart_s_data);
//
//if (s.empty()) {
//    std::cout << "Vector is empty." << std::endl;
//    return;
//}
//double min = s[0];// Initialize min with the first element
//double max = s[0]; // Initialize max with the first element
//for (int i = 0; i < s.size(); i++) {
//    if (min > s[i]) {
//        min = s[i];
//    }
//    if (max < s[i]) {
//        max = s[i];
//    }
//    qDebug() << "min" << min;
//    qDebug() << "max" << max;
//    axisX->setRange(0, s.size());
//    axisY->setRange(min * 2, max * 2);
//    axisY->setLabelFormat("%.1f"); // 显示一位小数
//
//    chartView_stock->setRenderHint(QPainter::Antialiasing);
//    layout_stock->addWidget(chartView_stock);
//
//    widget_stockwell_fun->show();
///chart显示
//QChart* chart_s_data = new QChart();
//QWidget* widget_stockwell_fun = new QWidget();
//
//QChartView* chartView_stock = new QChartView();
//
//QVBoxLayout* layout_stock = new QVBoxLayout(widget_stockwell_fun);
//
//chartView_stock->setChart(chart_s_data);
//QSplineSeries* series_stock = new QSplineSeries();//1
//chart_s_data->addSeries(series_stock);//2
//
//for (int i = 0; i < s.size(); i++) {
//    series_stock->append(i, s[i]);
//}
////添加坐标轴
//QValueAxis* axisX = new QValueAxis();
//QValueAxis* axisY = new QValueAxis();
//QFont font;
//font.setPointSize(20);  // 设置字体大小
//axisX->setTitleFont(font);
//axisY->setTitleFont(font);
//axisX->setTitleText("sample");
//axisY->setTitleText("Amp");
//axisX->setTickCount(11);//设置刻度数量
//axisY->setTickCount(11);
//chart_s_data->addAxis(axisX, Qt::AlignBottom);//设置位置
//chart_s_data->addAxis(axisY, Qt::AlignLeft);
//series_stock->attachAxis(axisX);
//series_stock->attachAxis(axisY);
//
//chartView_stock->setChart(chart_s_data);
//
//if (s.empty()) {
//    std::cout << "Vector is empty." << std::endl;
//    return;
//}
//double min = s[0];// Initialize min with the first element
//double max = s[0]; // Initialize max with the first element
//for (int i = 0; i < s.size(); i++) {
//    if (min > s[i]) {
//        min = s[i];
//    }
//    if (max < s[i]) {
//        max = s[i];
//    }
//    qDebug() << "min" << min;
//    qDebug() << "max" << max;
//    axisX->setRange(0, s.size());
//    axisY->setRange(min * 2, max * 2);
//    axisY->setLabelFormat("%.1f"); // 显示一位小数
//
//    chartView_stock->setRenderHint(QPainter::Antialiasing);
//    layout_stock->addWidget(chartView_stock);
//
//    widget_stockwell_fun->show();
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
///找出一维向量最小值最大值
//if (s.empty()) {
//    std::cout << "Vector is empty." << std::endl;
//    return;
//}
//double min = s[0];// Initialize min with the first element
//double max = s[0]; // Initialize max with the first element
//for (int i = 0; i < s.size(); i++) {
//    if (min > s[i]) {
//        min = s[i];
//    }
//    if (max < s[i]) {
//        max = s[i];
//    }
//
//    axisX->setRange(0, s.size());
//    axisY->setRange(min, max);
///炫酷标签
//QString widget_gray1 = "Seis Data<br>Processing";
//QString widget_gray2 = "<span style='color:#94a3b8;font-size: 15pt;font-weight: normal;font-style:normal'>"
//"Software Developer<br>"
//"Based on Cpp&Qt Designed by Rain!"
//"</span>";
//QString combinedText = widget_gray1 + "<br>" + widget_gray2;
//label_picture->setStyleSheet(style1.label_main);
//label_picture->setText(QString("<html>%1</html>").arg(combinedText));
///提取邻域数据计算signal+kernelsize
//std::vector<double> Qt_segy_process::medianFilter(std::vector<double> inputSignal, int kernelSize) {
//    std::vector<double> resultData;
//    resultData.reserve(inputSignal.size());
//    for (int i = 0; i < inputSignal.size(); ++i) {
//        // 计算邻域的起始和结束索引
//        int startIdx = std::max(0, i - kernelSize / 2);
//        int endIdx = std::min(static_cast<int>(inputSignal.size()) - 1, i + kernelSize / 2);
//        // 从邻域中提取数据
//        std::vector<double> neighborhood(inputSignal.begin() + startIdx, inputSignal.begin() + endIdx + 1);
//        // 对邻域进行排序
//        std::sort(neighborhood.begin(), neighborhood.end());//排序取中间值，而不是平均数。
//
//        // 计算中值并添加到结果中
//        double medianValue = neighborhood[neighborhood.size() / 2];//取中间索引
//        resultData.push_back(medianValue);
//    }
//
//    return resultData;
//}

#pragma endregion
