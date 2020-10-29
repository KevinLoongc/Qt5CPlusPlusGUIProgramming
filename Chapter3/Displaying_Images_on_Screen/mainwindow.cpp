#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // Load several image files
    QImage image1;
    QImage image2;
    QImage image3;

    image1.load("://img/bule.png");
    image2.load("://img/tux.png");
    image3.load("://img/butterfly.png");

    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    painter.drawImage(QPoint(10, 10), image1);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.drawImage(QPoint(10, 10), image2);

    painter.setCompositionMode(QPainter::CompositionMode_Xor);
    painter.drawImage(QPoint(300, 10), image1);
    painter.setCompositionMode(QPainter::CompositionMode_SoftLight);
    painter.drawImage(QPoint(300, 40), image3);
}
