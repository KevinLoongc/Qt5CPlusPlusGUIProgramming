#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("yourusername");
    db.setPassword("youruserpassword");
    db.setDatabaseName("yourdatabasename");

    connected = db.open();      // Connect to database

    if (connected)
    {
        QSqlQuery query;
        if (query.exec("SELECT id, name, age, gender, married FROM employee"))
        {
            while (query.next())
            {
                currentID = query.value(0).toInt();
                ui->nameLineEdit->setText(query.value(1).toString());
                ui->ageLineEdit->setText(query.value(2).toString());
                ui->genderComboBox->setCurrentIndex(query.value(3).toInt());
                ui->marriedCheckBox->setChecked(query.value(4).toBool());
            }
        }
        else
        {
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
        }
    }
    else
    {
        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: Failed to connect to database.");
    }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_updateButton_clicked()
{
    if (connected)
    {
        if (currentID == 0)
        {
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Nothing to update.");
        }
        else
        {
            QString id      = QString::number(currentID);
            QString name    = ui->nameLineEdit->text();
            QString age     = ui->ageLineEdit->text();
            QString gender  = QString::number(ui->genderComboBox->currentIndex());
            QString married = QString::number(ui->marriedCheckBox->isChecked());

            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] UPDATE employee SET name = '" + name + "', age = '" + age +
                                     "', gender = " + gender + ", married = " + married + " WHERE id = " + id);

            QSqlQuery query;
            if (query.exec("UPDATE employee SET name = '" + name + "', age = '" + age +
                           "', gender = " + gender + ", married = " + married + " WHERE id = " + id))
            {
                ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Update success.");
            }
            else
            {
                ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
            }
        }
    }
    else
    {
        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: Failed to connect to database.");
    }
}

void MainWindow::on_insertButton_clicked()
{
    if (connected)
    {
        QString name    = ui->nameLineEdit->text();
        QString age     = ui->ageLineEdit->text();
        QString gender  = QString::number(ui->genderComboBox->currentIndex());
        QString married = QString::number(ui->marriedCheckBox->isChecked());

        ui->infoTextEdit->append("INSERT INTO employee (name, age, gender, married) VALUES ('"
                                 + name + "','" + age + "'," + gender + "," + married + ")");
        QSqlQuery query;
        if (query.exec("INSERT INTO employee (name, age, gender, married) VALUES ('"
                       + name + "','" + age + "'," + gender + "," + married + ")"))
        {
            currentID = query.lastInsertId().toInt();
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Insert success.");
        }
        else
        {
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
        }
    }
    else
    {
        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: Failed to connect to database.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if (connected)
    {
        if (currentID == 0)
        {
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Nothing to delete.");
        }
        else
        {
            QString   id = QString::number(currentID);
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: DELETE FROM employee WHERE id = " + id);
            QSqlQuery query;
            if (query.exec("DELETE FROM employee WHERE id = " + id))
            {
                currentID = 0;
                ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Delete success.");
            }
            else
            {
                ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
            }
        }
    }
    else
    {
        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: Failed to connect to database.");
    }
}
