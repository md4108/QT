#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>
#include <QSpinBox>
#include <QProgressBar>
#include <QInputDialog>
#include <QThread>
#include <QDebug>

#define RESET 0

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


        /* First Screen Widgets */
        QPushButton *b_adcvolt;
        QPushButton *b_voltadc;
        QHBoxLayout *h_welcome_buttons;
        QGroupBox *g_welcome_buttons;
        QVBoxLayout *v_welcome_buttons;
        QWidget *w_welcome_buttons;

        /* Second Screen Widgets */

        /* Input Group Box */
        QPushButton *b_voltage;
        QPushButton *b_resolution;
        QPushButton *b_adcvalue;
        QSpinBox *spin_voltage;
        QSpinBox *spin_adcvalue;
        QSpinBox *spin_resolution;
        QHBoxLayout *h_input_buttons;
        QGroupBox *g_input_buttons;

        /* Result Group Box */
        QPushButton *b_results;
        QHBoxLayout *h_result_buttons;
        QGroupBox *g_result_buttons;

        /* Output Group Box */
        QSpinBox *spin_box;
        QProgressBar *progress_bar;
        QHBoxLayout *h_output_bars;
        QGroupBox *g_output_bars;

        /* Close Group box */
        QPushButton *b_back_button;
        QHBoxLayout *h_back_button;
        QGroupBox *g_back_button;

        /* Main Vbox and Widget */
        QVBoxLayout *v_main_layout;
        QWidget *w_main_widget;

    private slots:
        void adcvoltwindow();
        void voltadcwindow();
        void voltage();
        void resolution();
        void adcvalue();
        void results_adc();
        void results_voltage();

};

class Worker : public QObject
{
    Q_OBJECT


public slots:
    void doWork_adc();
    void doWork_voltage();


signals:
   void resultReady();

};


class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    Controller();

    ~Controller();

public slots:
    void handleResults();

signals:
    void operate_adc();
    void operate_voltage();


};


#endif // MAINWINDOW_H
