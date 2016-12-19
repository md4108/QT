#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <math.h>
#include <QPixmap>
#include <QProgressBar>
#include <QThread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:

    Ui::MainWindow *ui;
    int resolution;
    float voltage;
    QSlider *slider;
    QSpinBox *spinbox;
    QProgressBar *bar;

private slots:
    void getvoltage(void);
    void getresolution(void);
    void results(void);

};

#endif // MAINWINDOW_H
