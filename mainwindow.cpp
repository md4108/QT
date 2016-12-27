#include "mainwindow.h"
#include "ui_mainwindow.h"

int answer=0;
int volts=0, resol=0;
int adcval=0;

void Worker::doWork_adc()
{

    float res;
    res = pow(2, resol) - 1;
    answer = ((res/5)) * volts;
    qDebug()<<"Coming to dowork";
    //resultReady();
}

void Worker::doWork_voltage()
{
    int res;
    res = pow(2, resol) - 1;
    answer = (((adcval / res) * 5) + ((adcval % res) * 5));
    qDebug()<<"Coming to dowork";
    //resultReady();
}

Controller::Controller()
{
        qDebug()<<"Coming to Controller constructor";
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate_adc, worker, &Worker::doWork_adc);
        connect(this, &Controller::operate_voltage, worker, &Worker::doWork_voltage);
        //connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
    qDebug()<<"Coming to Controller destructor";
}

void Controller::handleResults()
{
    qDebug()<<"Coming to handleresult";
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    b_adcvolt(new QPushButton("Voltate to Count", this)),
    b_voltadc(new QPushButton("Count to Voltage", this)),
    h_welcome_buttons(new QHBoxLayout),
    g_welcome_buttons(new QGroupBox("Selection")),
    v_welcome_buttons(new QVBoxLayout),
    w_welcome_buttons(new QWidget),
    b_voltage(new QPushButton("Voltage")),
    b_resolution(new QPushButton("Resolution")),
    b_adcvalue(new QPushButton("ADC Count")),
    spin_voltage(new QSpinBox),
    spin_adcvalue(new QSpinBox),
    spin_resolution(new QSpinBox),
    h_input_buttons(new QHBoxLayout),
    g_input_buttons(new QGroupBox("Inputs")),
    b_results(new QPushButton("Calculate!")),
    h_result_buttons(new QHBoxLayout),
    g_result_buttons(new QGroupBox("Outputs")),
    spin_box(new QSpinBox),
    progress_bar(new QProgressBar),
    h_output_bars(new QHBoxLayout),
    g_output_bars(new QGroupBox("Values")),
    b_back_button(new QPushButton("Change Selection")),
    h_back_button(new QHBoxLayout),
    g_back_button(new QGroupBox("Back to selection")),
    v_main_layout(new QVBoxLayout),
    w_main_widget(new QWidget)
{
    ui->setupUi(this);
    /* Selection Window Widgets */
    h_welcome_buttons->addWidget(b_adcvolt);
    h_welcome_buttons->addWidget(b_voltadc);
    g_welcome_buttons->setLayout(h_welcome_buttons);
    v_welcome_buttons->addWidget(g_welcome_buttons);
    w_welcome_buttons->setLayout(v_welcome_buttons);

    spin_voltage->setSuffix(" volts");
    spin_adcvalue->setSuffix(" Counts");
    spin_resolution->setSuffix(" Bits");

    spin_voltage->setMaximum(5);
    spin_adcvalue->setMaximum(1023);
    spin_resolution->setMaximum(10);


    /* Connect the Slots */
    connect(b_adcvolt, SIGNAL(clicked()), this, SLOT(adcvoltwindow()));
    connect(b_voltadc, SIGNAL(clicked()), this, SLOT(voltadcwindow()));

    /* Welcome window widget setting */
    setCentralWidget(w_welcome_buttons);
    setMaximumSize(500,50);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::adcvoltwindow()
{
    b_adcvolt->setEnabled(false);
    b_voltadc->setEnabled(true);

    h_input_buttons->removeWidget(spin_adcvalue);
    h_input_buttons->removeWidget(spin_resolution);
    h_input_buttons->addWidget(spin_voltage);
    h_input_buttons->addWidget(spin_resolution);
    g_input_buttons->setLayout(h_input_buttons);

    h_result_buttons->addWidget(b_results);
    g_result_buttons->setLayout(h_result_buttons);

    h_output_bars->addWidget(progress_bar);
    spin_box->setMaximum(1023);
    h_output_bars->addWidget(spin_box);
    g_output_bars->setLayout(h_output_bars);

    connect(spin_voltage, SIGNAL(valueChanged(int)), this, SLOT(voltage()));
    connect(spin_resolution, SIGNAL(valueChanged(int)), this, SLOT(resolution()));
    disconnect(b_results, SIGNAL(clicked()), this, SLOT(results_voltage()));
    connect(b_results, SIGNAL(clicked()), this, SLOT(results_adc()));


    v_welcome_buttons->addWidget(g_input_buttons);
    v_welcome_buttons->addWidget(g_result_buttons);
    v_welcome_buttons->addWidget(g_output_bars);

}

void MainWindow::voltadcwindow()
{

    b_voltadc->setEnabled(false);
    b_adcvolt->setEnabled(true);

    h_input_buttons->removeWidget(spin_voltage);
    h_input_buttons->addWidget(spin_adcvalue);
    h_input_buttons->addWidget(spin_resolution);
    g_input_buttons->setLayout(h_input_buttons);

    h_result_buttons->addWidget(b_results);
    g_result_buttons->setLayout(h_result_buttons);

    h_output_bars->addWidget(progress_bar);
    spin_box->setMaximum(5);
    h_output_bars->addWidget(spin_box);
    g_output_bars->setLayout(h_output_bars);

    connect(spin_adcvalue, SIGNAL(valueChanged(int)), this, SLOT(adcvalue()));
    connect(spin_resolution, SIGNAL(valueChanged(int)), this, SLOT(resolution()));
    disconnect(b_results, SIGNAL(clicked()), this, SLOT(results_adc()));
    connect(b_results, SIGNAL(clicked()), this, SLOT(results_voltage()));

    v_welcome_buttons->addWidget(g_input_buttons);
    v_welcome_buttons->addWidget(g_result_buttons);
    v_welcome_buttons->addWidget(g_output_bars);

}


void MainWindow::voltage()
{
    volts = spin_voltage->value();
}


void MainWindow::resolution()
{
    resol = spin_resolution->value();
}

void MainWindow::adcvalue()
{
    adcval = spin_adcvalue->value();
}

void MainWindow::results_adc()
{

    Controller ctrl;
    ctrl.operate_adc();
    qDebug()<<"Coming to operate signal";

    for(int i=1;i<=100;i++)
    {
        progress_bar->setValue(i);
        QThread::msleep(5);
    }

    spin_box->setValue(answer);
}

void MainWindow::results_voltage()
{

    Controller ctrl;
    ctrl.operate_voltage();

    for(int i=1;i<=100;i++)
    {
        progress_bar->setValue(i);
        QThread::msleep(5);
    }

    spin_box->setValue(answer);
}






