/****************************************************************
 Doc    :   main.cpp
 Author :   BingLee
 Date   :   2020-9-25
 Info   :   QGraphicsView auto fit.
 https://blog.csdn.net/Bing_Lee (C)All rights reserved.
******************************************************************/

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(480, 400);

    return a.exec();
}
