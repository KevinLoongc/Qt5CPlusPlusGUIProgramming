#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QEventTransition>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QState *s1 = new QState();
    s1->assignProperty(ui->stateLabel, "text", "Current state: 1");           // Change the label's text
    s1->assignProperty(ui->pushButton, "geometry", QRect(50, 200, 100, 50));  // Change button's position and size
    QState *s2 = new QState();
    s2->assignProperty(ui->stateLabel, "text", "Current state: 2");           // Change the label's text
    s2->assignProperty(ui->pushButton, "geometry", QRect(200, 50, 140, 100)); // Change button's position and size

    QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(3000);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    QEventTransition *t1 = new QEventTransition(ui->changeStateBtn, QEvent::MouseButtonPress);
    t1->setTargetState(s2);
    t1->addAnimation(animation);
    s1->addTransition(t1);

    QEventTransition *t2 = new QEventTransition(ui->changeStateBtn, QEvent::MouseButtonPress);
    t2->setTargetState(s1);
    t2->addAnimation(animation);
    s2->addTransition(t2);

    QStateMachine *machine = new QStateMachine(this);
    machine->addState(s1);
    machine->addState(s2);

    machine->setInitialState(s1);
    machine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
