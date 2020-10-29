#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->pushButton, "geometry");
    animation1->setDuration(3000);                   // animation duration
    animation1->setStartValue(ui->pushButton->geometry());
    animation1->setEndValue(QRect(50, 50, 100, 50)); // target position:x:50,y:50, Change button size: width:100,height:50

    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->pushButton_2, "geometry");
    animation2->setDuration(3000);                    // animation duration
    animation2->setStartValue(ui->pushButton_2->geometry());
    animation2->setEndValue(QRect(150, 50, 100, 50)); // target position:x:150,y:50, Change button size: width:100,height:50

    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->pushButton_3, "geometry");
    animation3->setDuration(3000);                    // animation duration
    animation3->setStartValue(ui->pushButton_3->geometry());
    animation3->setEndValue(QRect(250, 50, 100, 50)); // target position:x:250,y:50, Change button size: width:100,height:50

    QPropertyAnimation *animation4 = new QPropertyAnimation(ui->pushButton_4, "geometry");
    animation4->setDuration(3000);                    // animation duration
    animation4->setStartValue(ui->pushButton_4->geometry());
    animation4->setEndValue(QRect(50, 200, 100, 50)); // target position:x:50,y:200, Change button size: width:100,height:50

    QPropertyAnimation *animation5 = new QPropertyAnimation(ui->pushButton_5, "geometry");
    animation5->setDuration(3000);                     // animation duration
    animation5->setStartValue(ui->pushButton_5->geometry());
    animation5->setEndValue(QRect(150, 200, 100, 50)); // target position:x:150,y:200, Change button size: width:100,height:50

    QPropertyAnimation *animation6 = new QPropertyAnimation(ui->pushButton_6, "geometry");
    animation6->setDuration(3000);                     // animation duration
    animation6->setStartValue(ui->pushButton_6->geometry());
    animation6->setEndValue(QRect(250, 200, 100, 50)); // target position:x:250,y:200, Change button size: width:100,height:50

    QEasingCurve curve;
    curve.setType(QEasingCurve::OutBounce);
    curve.setAmplitude(1.00);
    curve.setOvershoot(1.70);
    curve.setPeriod(0.30);

    animation1->setEasingCurve(curve);
    animation2->setEasingCurve(curve);
    animation3->setEasingCurve(curve);
    animation4->setEasingCurve(curve);
    animation5->setEasingCurve(curve);
    animation6->setEasingCurve(curve);

    QParallelAnimationGroup *group1 = new QParallelAnimationGroup;     // at the same time
    group1->addAnimation(animation1);
    group1->addAnimation(animation2);
    group1->addAnimation(animation3);

    QParallelAnimationGroup *group2 = new QParallelAnimationGroup;     // at the same time
    group2->addAnimation(animation4);
    group2->addAnimation(animation5);
    group2->addAnimation(animation6);

    QSequentialAnimationGroup *groupAll = new QSequentialAnimationGroup;     // in sequence
    groupAll->addAnimation(group1);
    groupAll->addAnimation(group2);
    groupAll->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
