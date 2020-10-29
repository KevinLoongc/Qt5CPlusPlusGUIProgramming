#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a drop shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setXOffset(4);
    shadow->setYOffset(4);
    ui->dropLabel->setGraphicsEffect(shadow);

    // Create a colorized effect
    QGraphicsColorizeEffect *colorize = new QGraphicsColorizeEffect();
    colorize->setColor(QColor(255, 0, 0));                 // Set the color to red
    ui->imageLabel1->setGraphicsEffect(colorize);

    // Create a blur effect
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(12);                               // Set radius to 12
    ui->blurLabel->setGraphicsEffect(blur);

    // Create an alpha effect
    QGraphicsOpacityEffect *alpha = new QGraphicsOpacityEffect();
    alpha->setOpacity(0.2); // Set 20% opacity
    ui->imageLabel2->setGraphicsEffect(alpha);
}

MainWindow::~MainWindow()
{
    delete ui;
}
