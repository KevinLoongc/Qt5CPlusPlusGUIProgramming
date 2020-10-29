#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

void filterAge();
void getDepartmentAndBranch();
void filterBranchAndAge();
void countFemale();
void filterName();
void filterBirthday();
void checkLog();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase     db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setUserName("yourusername");
    db.setPassword("youruserpassword");
    db.setDatabaseName("yourdatabasename");

    if (db.open())
    {
        filterAge();
        getDepartmentAndBranch();
        filterBranchAndAge();
        countFemale();
        filterName();
        filterBirthday();
        checkLog();

        db.close();
    }
    else
        qDebug() << "Failed to connect to database.";

    return a.exec();
}


void filterAge()
{
    qDebug() << "== Employees above 30 year old ============";
    QSqlQuery query;
    if (query.exec("SELECT name, age FROM employee2 WHERE age > 30"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
    qDebug() << "\n";
}

void getDepartmentAndBranch()
{
    qDebug() << "== Get employees' department and branch ==============";

    QSqlQuery query;
    if (query.exec("SELECT myEmployee.name, department.name, branch.name FROM "
                   "(SELECT name, departmentID FROM employee2) AS myEmployee INNER "
                   "JOIN department ON department.id = myEmployee.departmentID "
                   "INNER JOIN branch ON branch.id = department.branchID"))
    {
        while (query.next())
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }
    else
        qDebug() << query.lastError().text();

    qDebug() << "\n";
}

void filterBranchAndAge()
{
    qDebug() << "== Employees from Guangzhou and age below 30 ==============";

    QSqlQuery query;
    if (query.exec("SELECT myEmployee.name, myEmployee.age, department.name, branch.name "
                   "FROM (SELECT name, age, departmentID FROM employee2) AS "
                   "myEmployee INNER JOIN department ON "
                   "department.id = myEmployee.departmentID INNER JOIN branch ON "
                   "branch.id = department.branchID "
                   "WHERE branch.name = 'Guangzhou' AND age < 30"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString()
                     << query.value(2).toString() << query.value(3).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
    qDebug() << "\n";
}

void countFemale()
{
    qDebug() << "== Count female employees ==================";

    QSqlQuery query;
    if (query.exec("SELECT COUNT(gender) FROM employee2 WHERE gender = 1"))
    {
        while (query.next())
            qDebug() << query.value(0).toString();
    }
    else
        qDebug() << query.lastError().text();

    qDebug() << "\n";
}

void filterName()
{
    qDebug() << "== Employees name start with 'Ja' ===================";

    QSqlQuery query;
    if (query.exec("SELECT name FROM employee2 WHERE name LIKE '%Ja%'"))
    {
        while (query.next())
            qDebug() << query.value(0).toString();
    }
    else
        qDebug() << query.lastError().text();

    qDebug() << "\n";
}

void filterBirthday()
{
    qDebug() << "== Employee birthday in Augst ================";

    QSqlQuery query;
    if (query.exec("SELECT name, birthday FROM employee2 WHERE MONTH(birthday) = 8"))
    {
        while (query.next())
            qDebug() << query.value(0).toString() <<
                query.value(1).toDate().toString("yyyy-MM-dd");
    }
    else
        qDebug() << query.lastError().text();

    qDebug() << "\n";
}

void checkLog()
{
    qDebug() << "== Employee who logged in on 27 April 2016 =============";

    QSqlQuery query;
    if (query.exec("SELECT DISTINCT myEmployee.name FROM (SELECT id, name FROM employee2) AS "
                   "myEmployee INNER JOIN user ON user.employeeID = myEmployee.id "
                   "INNER JOIN log ON log.userID = user.id WHERE DATE(log.loginTime) = '2016-04-27'"))
    {
        while (query.next())
            qDebug() << query.value(0).toString();
    }
    else
        qDebug() << query.lastError().text();

    qDebug() << "\n";
}
