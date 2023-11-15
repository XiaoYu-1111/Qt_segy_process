#pragma once
#include<QString>

class stylesheet_QT {//样式类,导入h文件，实例化后，即可使用~


public:
    QString styleSheet_bar = "QStatusBar { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 orange);font-size:20px; }";

    QString button_main = "QPushButton{font-size:20px;color: rgb(153, 113, 113);background-color: rgb(237, 236, 208);border-radius:8px;}QPushButton:hover{background-color: rgb(220, 227, 235);}QPushButton:pressed{padding-top:5px;padding-left:5px;}";

    QString button_main2 = "QPushButton{font-size:15px;color: rgb(153, 113, 113);background-color: rgb(237, 236, 208);border-radius:8px;}QPushButton:hover{background-color: rgb(220, 227, 235);}QPushButton:pressed{padding-top:5px;padding-left:5px;}";

    QString down_left = "QPushButton{color: rgb(153, 113, 113);background-color: lightgreen;border-radius:8px;}QPushButton:hover{background-color: rgb(220, 227, 235);}QPushButton:pressed{padding-top:5px;padding-left:5px;}";

    QString button_save_style1 = "QPushButton{color: rgb(153, 113, 113);background-color: rgb(237, 236, 208);border-radius:8px;}QPushButton:hover{background-color: rgb(220, 227, 235);}QPushButton:pressed{padding-top:5px;padding-left:5px;}";

    QString button_save_style2 = "QPushButton{color: rgb(153, 113, 113);background-color: lightgreen;border-radius:8px;}QPushButton:hover{background-color: rgb(220, 227, 235);}QPushButton:pressed{padding-top:5px;padding-left:5px;}";

    QString widget_gray1 = "background-color: rgb(150,150,150);border-radius:10px;";

    QString widget_gray2 = "background-color: rgb(200,200,200);border-radius:10px;";

    QString widget_gray3 = "background-color: rgb(220,220,220);border-radius:10px;";

    QString label1 = "background-color:lightgreen;font-size:20px;border - radius:10px; ";

    QString  tooltip1 = "<html><font size='5' color='lightgreen'>MAIN PAGE</font></html>";
};