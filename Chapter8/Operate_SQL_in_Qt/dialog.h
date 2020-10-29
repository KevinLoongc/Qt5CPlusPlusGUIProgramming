#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_updateButton_clicked();
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_nameComboBox_currentIndexChanged(const QString &arg1);

    void Slot_moreCheckBox();
    void update_nameList();

private:
    Ui::Dialog *ui;

    QSqlDatabase db;
    bool connected;
    int currentID;
    bool hasInit;
};

#endif // DIALOG_H
