#ifndef DATABASEADAPTER_H
#define DATABASEADAPTER_H

#include <QtSql>
#define OPEN_DATABASE_ERROR 1
#define QUERY_EXEC_ERROR    2
#define EMPTY_TABLE_ERROR   3

#define WORKER_NAME     0
#define DATE    1
#define CASH 2
#define MASTER  3

#define EMPLOYEE 0
#define MANAGE   1
#define SALES    2

#define IS_IMPLOYEE query.value(0).toString() != ""
#define IS_MANAGE   query.value(1).toString() != ""
#define IS_SALES    query.value(2).toString() != ""

struct DB_Table
{
    QString ** table;
    int rowCount;
    int colCount;
};

struct UserData
{
    QString userName = "NO_USER";
    QString hash;
    QString fio;
    QString type;
    QString date;
    int basePay;
    int master;
    int workerId;
};

class DataBaseAdapter
{
    QSqlDatabase sdb;
    int lastWorkerID  = - 1;

public:
    DataBaseAdapter();

    DB_Table getEmployeeWorkersTable();
    DB_Table getManageWorkersTable();
    DB_Table getSalesWorkersTable();

    DB_Table getUsersTable();

    DB_Table getTable(QString queryText, int columnsCount);

    int addNewWorker(QString tableName,QString workerName, QString date, int basePay,int master);
    int addNewUser(QString userName, QString password, int workerId);

    int doQuery(QString queryText);

    UserData getUserData(QString userName);
    UserData getWorkerData(int workerID);

    int getLastWorkerId();

    DB_Table getSubordinates(int masterID);
};

#endif // DATABASEADAPTER_H
