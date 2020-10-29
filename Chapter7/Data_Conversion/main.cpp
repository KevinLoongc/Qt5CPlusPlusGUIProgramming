#include <QCoreApplication>
#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QTextCodec>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // String to number
    int     numberA = 2;
    QString numberB = "5";

    qDebug() << "1) String to number:";
    qDebug() << "   2 + 5 =" << numberA + numberB.toInt();

    // Number to string
    float   numberC = 10.25;
    float   numberD = 2;
    QString result  = QString::number(numberC * numberD);
    qDebug() << "2) Number to string:";
    qDebug() << "   10.25 * 2 =" << result;

    // Round down a value
    float numberE = 10.3;
    float numberF = qFloor(numberE);
    qDebug() << "3) " << "Floor of 10.3 is" << numberF;

    // Round a number to the smallest intergral vaue not smaller than its initial value
    float numberG = 10.3;
    float numberH = qCeil(numberG);
    qDebug() << "4) " << "Ceil of 10.3 is" << numberH;

    // Date time from string
    QString   dateTimeAString = "2020-10-22 16:50:00";
    QDateTime dateTimeA       = QDateTime::fromString(dateTimeAString, "yyy-MM-dd hh:mm:ss");
    qDebug() << "5) Date time from string:";
    qDebug() << "   " << dateTimeA;

    // Date time to string
    QDateTime dateTimeB       = QDateTime::currentDateTime();
    QString   dateTimeBString = dateTimeB.toString("dd/MM/yy hh:mm");
    qDebug() << "6) Date time to string:";
    qDebug() << "   " << dateTimeBString;

    // String to all uppercase
    QString hello = "hello world!";
    qDebug() << "7) String to all uppercase:";
    qDebug() << "   " << hello.toUpper();

    // String to all lowercase
    QString hello2 = "HELLO WORLD!";
    qDebug() << "8) String to all lowercase:";
    qDebug() << "   " << hello2.toLower();;

    // QVariant to double
    QVariant aNumber = QVariant(3.14159);
    double   aResult = 12.5 * aNumber.toDouble();
    qDebug() << "9) QVariant to double:";
    qDebug() << "   12.5 * 3.14159 =" << aResult;

    // QVariant to different types
    qDebug() << "10) QVariant to different types:";
    QVariant myData = QVariant(10);
    qDebug() << "   " << myData;
    myData = myData.toFloat() / 2.135;
    qDebug() << "   " << myData;
    myData = true;
    qDebug() << "   " << myData;
    myData = QDateTime::currentDateTime();
    qDebug() << "   " << myData;
    myData = "Good bye!";
    qDebug() << "   " << myData;

    return a.exec();
}
