#pragma once
#include<QString>

class stylesheet_QT {//样式类,导入h文件，实例化后，即可使用~

public:
    QString styleSheet_bar = "QStatusBar { color:#cbd5e1;background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #334155, stop:1 #475569);font-size:20px; }";

    QString button_main = R"(QPushButton{font-size:20px;color:#cbd5e1;
                        background-color:#334155;border-radius:8px;}
                        QPushButton:hover{background-color:#475569}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString button_15px = R"(QPushButton{font-size:20px;color:#cbd5e1;
                        background-color:#334155;border-radius:8px;}
                        QPushButton:hover{background-color:#475569}
                        QPushButton:pressed{padding-top:5px;padding-left:5px;})";

    QString widget_gray1 = "background-color: #1e293b;color:#D3E6FE;";//深色

    QString widget_gray2 = "background-color: #cbd5e1;";//浅色

    QString widget_glass = "background-color: #475569;border-radius:10px;";//半透明

    QString label1 = "color:#cbd5e1;background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #334155, stop:1 #598EF3);font-size:20px;border-radius:16px;";
    
    QString label_main= "color:#598EF3;font-size:88px;font-style: italic; font-weight: bold;";//主标签

    QString tool_bar = "color:#D3E6FE;background-color:#334155;font-size:20px;";

    QString tabStyle = "QTabBar::tab {color:#D3E6FE;background-color:#334155;border: 2px solid #598EF3;font-size:15px;width: 150px;height:30px;}";
    QString textEdit = "color:#cbd5e1;background-color: #475569;font-size:15px;border-radius:10px;";
    QString dock_widget = "background-color:#1e293b;color:#cbd5e1;";
    QString dock_textEdit = "color:#cbd5e1;background-color: #475569;font-size:15px;";
};