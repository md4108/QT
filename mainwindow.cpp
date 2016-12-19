#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    voltage = 0;
    resolution = 0;
//    QPixmap bkgnd("svn.png");
//       bkgnd = bkgnd.scaled(1000,1000,Qt::KeepAspectRatio);
//       QPalette palette;
//       palette.setBrush(QPalette::Background, bkgnd);
//       this->setPalette(palette);

    QHBoxLayout *layout = new QHBoxLayout;
    QHBoxLayout *sliderlay = new QHBoxLayout;
    QVBoxLayout *lay = new QVBoxLayout;
    QPushButton *value = new QPushButton("Voltage", this);
    QPushButton *resolution = new QPushButton("Resolution", this);
    QPushButton *resultbutton = new QPushButton("Calculate!", this);

    QGroupBox *box = new QGroupBox("Inputs");
    QGroupBox *sliderbox = new QGroupBox("Output");
    bar = new QProgressBar;
    QGroupBox *result = new QGroupBox;
    QHBoxLayout *resultbut = new QHBoxLayout;

    box->setMaximumSize(300,100);
    spinbox = new QSpinBox;
    spinbox->setRange(0,1024);

    layout->addWidget(value);
    layout->addWidget(resolution);
    resultbut->addWidget(resultbutton);

    result->setLayout(resultbut);

    box->setLayout(layout);
    lay->addWidget(box);
    lay->addWidget(result);
    //bar->setMaximumSize(300,100);
    sliderlay->addWidget(bar);
    sliderlay->addWidget(spinbox);

    sliderbox->setLayout(sliderlay);
    lay->addWidget(sliderbox);

    connect(value, SIGNAL(clicked()), this, SLOT(getvoltage()));
    connect(resolution, SIGNAL(clicked()), this, SLOT(getresolution()));
    connect(resultbutton, SIGNAL(clicked()), this, SLOT(results()));

    QWidget *widget = new QWidget;
    widget->setLayout(lay);
    setCentralWidget(widget);
    setMaximumSize(300, 50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getvoltage()
{
    voltage = QInputDialog::getInt(this, tr("Input Voltage"), tr("Volts"), voltage,0,5,1);
    //results();
}


void MainWindow::getresolution()
{
    resolution = QInputDialog::getInt(this, tr("ADC Resolution"), tr("Bits"), resolution,0,10,1);
    //results();
}

void MainWindow::results()
{
    float res;
    res = pow(2, resolution) - 1;
    int result = ((res/5) /* + (res%5)*/) * voltage;

    for(int i=1;i<=100;i++)
    {
        bar->setValue(i);
        QThread::msleep(5);
    }
    spinbox->setValue(result);
}


