#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("SQL Manager");
    ui->moreWidget->hide();
    hasInit = false;

    connect(ui->moreCheckBox, SIGNAL(clicked(bool)), this, SLOT(Slot_moreCheckBox()));

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
	db.setUserName("yourusername");
    db.setPassword("youruserpassword");
    db.setDatabaseName("yourdatabasename");

    connected = db.open();      // Connect to database

    if (connected)
    {
        QSqlQuery query;
        if (query.exec("SELECT name, age, gender, married FROM employee"))
        {
            while (query.next())
            {
                ui->nameComboBox->addItem(query.value(0).toString());
                ui->ageLabel->setText(query.value(1).toString());

                if (query.value(2).toInt() == 0)
                    ui->genderLabel->setText("Male");
                else
                    ui->genderLabel->setText("Female");

                if (query.value(3).toInt() == 0)
                    ui->marriedLabel->setText("No");
                else
                    ui->marriedLabel->setText("Yes");
            }
            hasInit = true;
            ui->nameComboBox->setCurrentIndex(1);
            ui->nameComboBox->setCurrentIndex(0);
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

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

void Dialog::on_updateButton_clicked()
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
                update_nameList();
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

void Dialog::on_insertButton_clicked()
{
    if (connected)
    {
        QString name    = ui->nameLineEdit->text();
        QString age     = ui->ageLineEdit->text();
        QString gender  = QString::number(ui->genderComboBox->currentIndex());
        QString married = QString::number(ui->marriedCheckBox->isChecked());

        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: INSERT INTO employee (name, age, gender, "
                                 "married) VALUES ('" + name + "','" + age + "'," + gender + "," + married + ")");

        QSqlQuery query;
        if (query.exec("INSERT INTO employee (name, age, gender, married) VALUES ('"
                       + name + "','" + age + "'," + gender + "," + married + ")"))
        {
//            currentID = query.lastInsertId().toInt();
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] INFO: Insert success.");
            update_nameList();
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

void Dialog::on_deleteButton_clicked()
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
                update_nameList();
                ui->nameComboBox->setCurrentIndex(1);
                ui->nameComboBox->setCurrentIndex(0);
            }
            else
                ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
        }
    }
    else
        ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: Failed to connect to database.");
}

void Dialog::on_nameComboBox_currentIndexChanged(const QString &arg1)
{
    if (hasInit && connected)
    {
        QSqlQuery query;
        if (query.exec("SELECT id, name, age, gender, married FROM employee"))
        {
            while (query.next())
            {
                if (query.value(1).toString() == arg1)
                {
                    currentID = query.value(0).toInt();
                    ui->ageLabel->setText(query.value(2).toString());

                    if (query.value(3).toInt() == 0)
                        ui->genderLabel->setText("Male");
                    else
                        ui->genderLabel->setText("Female");

                    if (query.value(4).toInt() == 0)
                        ui->marriedLabel->setText("No");
                    else
                        ui->marriedLabel->setText("Yes");

                    if (ui->moreCheckBox->isChecked())
                    {
                        ui->nameLineEdit->setText(query.value(1).toString());
                        ui->ageLineEdit->setText(query.value(2).toString());
                        ui->genderComboBox->setCurrentIndex(query.value(3).toInt());
                        ui->marriedCheckBox->setChecked(query.value(4).toBool());
                    }
                }
            }
        }
        else
            ui->infoTextEdit->append("[" + QTime::currentTime().toString() + "] ERROR: " + query.lastError().text());
    }
}

void Dialog::Slot_moreCheckBox()
{
    if (ui->moreCheckBox->isChecked())
    {
        ui->moreWidget->show();
        ui->nameLineEdit->setText(ui->nameComboBox->currentText());
        ui->ageLineEdit->setText(ui->ageLabel->text());
        ui->genderComboBox->setCurrentIndex(ui->genderLabel->text().toInt());
        if (ui->marriedLabel->text() == "Yes")
            ui->marriedCheckBox->setChecked(1);
        else
            ui->marriedCheckBox->setChecked(0);
    }
    else
    {
        ui->nameLineEdit->setText("");
        ui->ageLineEdit->setText("");
        ui->moreWidget->hide();
    }
}

void Dialog::update_nameList()
{
    int       num = 0;
    QSqlQuery query;

    hasInit = false;
    ui->nameComboBox->clear();  // Clear name list

    if (query.exec("SELECT id, name, age, gender, married FROM employee"))
    {
        while (query.next())
        {
            num++;
            ui->nameComboBox->addItem(query.value(1).toString());

            if (query.value(1).toString() == ui->nameLineEdit->text())
            {
                currentID = query.value(0).toInt();
                ui->nameComboBox->setCurrentIndex(num - 1);
                ui->ageLabel->setText(query.value(2).toString());

                if (query.value(3).toInt() == 0)
                    ui->genderLabel->setText("Male");
                else
                    ui->genderLabel->setText("Female");

                if (query.value(4).toInt() == 0)
                    ui->marriedLabel->setText("No");
                else
                    ui->marriedLabel->setText("Yes");
            }
        }
        hasInit = true;
    }
}
