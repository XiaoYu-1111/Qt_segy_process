#include "Qt_segy_process.h"
#include <QtWidgets/QApplication>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <opencv2/opencv.hpp>
#include<QVBoxLayout>
#include<QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_segy_process w;
    w.show();
    return a.exec();
}
