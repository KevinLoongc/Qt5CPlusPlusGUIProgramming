#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeUpdate()
{
    QLocale locale = QLocale::English;      // 指定英文显示
    QString str    = locale.toString(QDateTime::currentDateTime(), QString("dddd, yyyy-MM-dd hh:mm AP"));

    ui->Label_time->setText(str);
}
