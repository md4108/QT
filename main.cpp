#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap pixmap("D:/QT Practice/ADC3/images/bkgnd.png");
    QSplashScreen splash(pixmap);
    splash.show();

    QThread::sleep(1);

    w.setWindowTitle("ADC Converter");
    w.show();
    splash.finish(&w);

    return a.exec();
}
