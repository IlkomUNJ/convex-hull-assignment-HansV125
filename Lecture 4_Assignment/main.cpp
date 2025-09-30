//#include "mainwindow.h"
#include "drawingwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    DrawingWindow dw;
    dw.show();
    return a.exec();
}
