#include "mainwindow.h"
#include "mainwindow2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w; // First projects of the book "OpenCV2 Computer Vision Application programming Cookbook"
    MainWindow2 w2; // From Chapter 4 of the book
    //w.show();
    w2.show();
    return a.exec();
}
