#pragma once
#include<QString>

class stylesheet_QT {//样式类,导入h文件，实例化后，即可使用~


public:
    QString styleSheet_bar = "QStatusBar { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 lightgreen, stop:1 orange);font-size:20px; }";

    QString button_main = R"(QPushButton{font-size:20px;color: rgb(153, 113, 113);
                        background-color: rgb(237, 236, 208);border-radius:8px;}
                        QPushButton:hover{background-color: rgb(220, 227, 235);}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString button_main2 = R"(QPushButton{font-size:15px;color: rgb(153, 113, 113);
                        background-color: rgb(237, 236, 208);border-radius:8px;}
                        QPushButton:hover{background-color: rgb(220, 227, 235);}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString down_left = R"(QPushButton{color: rgb(153, 113, 113);
                        background-color: lightgreen;border-radius:8px;}
                        QPushButton:hover{background-color: rgb(220, 227, 235);}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString button_save_style1 = R"(QPushButton{color: rgb(153, 113, 113);border: 2px solid rgb(255,255,255);
                        background-color: rgb(237, 236, 208);border-radius:8px;font-size:15px;}
                        QPushButton:hover{background-color: rgb(220, 227, 235);font-size:14px;}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;font-size:12px;})";

    QString button_save_style2 = R"(QPushButton{color: rgb(153, 113, 113);background-color: lightgreen;border-radius:8px;}
                        QPushButton:hover{background-color: rgb(220, 227, 235);}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString stack_save = R"(QPushButton{font-size:15px;border-radius:8px;
                        background-color: white;border: 2px solid rgb(0,0,0)}
                        QPushButton:hover{background-color: rgb(220, 227, 235);}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";
    QString widget_gray1 = "background-color: rgb(150,150,150);border-radius:10px;";

    QString widget_gray2 = "background-color: rgb(200,200,200);border-radius:10px;";

    QString widget_gray3 = "background-color: rgb(220,220,220);border-radius:10px;";

    QString label1 = "background-color:lightgreen;font-size:20px;border - radius:10px; ";

    QString label_pink = "background-color:pink;font-size:20px;border - radius:10px; ";
    QString label_orange = "background-color:orange;font-size:20px;border - radius:10px; ";

    QString  tooltip1 = "<html><font size='5' color='lightgreen'>MAIN PAGE</font></html>";

    QString  information_widget = "background-color: white;border-radius:10px; ";
};