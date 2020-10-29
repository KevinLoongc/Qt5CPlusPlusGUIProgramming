#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("yourusername");
    db.setPassword("youruserpassword");
    db.setDatabaseName("yourdatabasename");

    if(db.open())
    {
        QSqlQuery query;
        if(query.exec("SELECT name, age, gender, married FROM employee"))
        {
            while (query.next())
            {
                qDebug() << query.value(0) << query.value(1) << query.value(2) << query.value(3);

                ui->nameLabel->setText(query.value(0).toString());
                ui->ageLabel->setText(query.value(1).toString());
                ui->genderComboBox->setCurrentIndex(query.value(2).toInt());
                ui->marriedCheckBox->setChecked(query.value(3).toBool());
            }
        }
        else
        {
            qDebug() << query.lastError().text();
        }
        db.close();
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
