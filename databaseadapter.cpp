#include "databaseadapter.h"

DataBaseAdapter::DataBaseAdapter()
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("ST_test.db");

    sdb.open();

    /*QSqlQuery query("SELECT worker_id from workers ORDER BY worker_id DESC");

    query.next();

    lastWorkerID = query.value(0).toInt();*/

}

DB_Table DataBaseAdapter::getEmployeeWorkersTable()
{
    return getTable("SELECT workerName,date,cash,master FROM EmployeeWorkers",4);
}

DB_Table DataBaseAdapter::getManageWorkersTable()
{
    return getTable("SELECT workerName,date,cash,master FROM ManageWorkers",4);
}

DB_Table DataBaseAdapter::getSalesWorkersTable()
{
    return getTable("SELECT workerName,date,cash,master FROM SalesWorkers",4);
}

DB_Table DataBaseAdapter::getUsersTable()
{
    DB_Table userTable;
    DB_Table table = getTable("SELECT userName FROM users",3);

    userTable.table = new QString * [table.rowCount];

    for(int i = 0 ; i < table.rowCount;i++)
         userTable.table[i] = new QString[4];

    UserData tempData;

    for(int i = 0; i < table.rowCount;i++)
    {
       tempData = getUserData(table.table[i][0]);

       if(tempData.userName == "NO_USER") continue;

       userTable.table[i][0] = tempData.userName;
       userTable.table[i][1] = tempData.fio;
       userTable.table[i][2] = tempData.type;
       userTable.table[i][3] = tempData.date;
    }

    userTable.rowCount = table.rowCount;
    userTable.colCount = 4;

    return userTable;
}

DB_Table DataBaseAdapter::getTable(QString queryText,int columnsCount)
{
    QString ** table;
    int rowNumber = 0;
    int rowCounter = 0;

    if (!sdb.open())
    {
        //OPEN_DATABASE_ERROR;
    }

    QSqlQuery query(queryText);
    while(query.next()) rowNumber++;

    table = new QString * [rowNumber];

    for(int i = 0 ; i < rowNumber;i++)
        table[i] = new QString[columnsCount];

    query.exec(queryText);
    while(query.next())
    {
        for(int k = 0; k < columnsCount;k++)
        table[rowCounter][k]  = query.value(k).toString();
//        table[rowCounter][FIO]  = query.value(FIO).toString();
//        table[rowCounter][TYPE] = query.value(TYPE).toString();
//        table[rowCounter][DATE] = query.value(DATE).toString();
//        table[rowCounter][BASEPAY] = query.value(BASEPAY).toString();
//        table[rowCounter][MASTER] = query.value(MASTER).toString();

        rowCounter++;
    }

    sdb.close();

    DB_Table result;

    result.table = table;
    result.rowCount = rowNumber;
    result.colCount = columnsCount;

    return result;
}

int DataBaseAdapter::addNewWorker(QString tableName,QString workerName, QString date, int basePay,int master)
{
    if (!sdb.open()) return OPEN_DATABASE_ERROR;

    QString queryText = "INSERT into %tableName%('workerName','date','cash','master') values('%workerName%', '%date%', '%basepay%','%master%')";

    QSqlQuery query;

    lastWorkerID++;

    queryText.replace("%tableName%",tableName);                    //Замена шаблона имени настоящим именем работника
    queryText.replace("%workerName%",workerName);                  //Замена шаблона имени настоящим именем работника
    queryText.replace("%date%",date);                              //Замена шаблона даты поступления настоящей датой
    queryText.replace("%basepay%",QString::number(basePay));       //Замена шаблона базовой ставки
    queryText.replace("%master%",QString::number(master));         //Замена шаблона базовой ставки

    doQuery(queryText);

    if (!sdb.open()) return OPEN_DATABASE_ERROR;
    queryText = "SELECT id FROM " + tableName + " ORDER BY id DESC";
    query.exec(queryText);
    query.next();

    if(tableName == "EmployeeWorkers") queryText = "INSERT INTO Workers (EmployeeID) VALUES('" +query.value(0).toString() + "')";
    if(tableName == "ManageWorkers")   queryText = "INSERT INTO Workers (ManageID) VALUES('" +query.value(0).toString() + "')";
    if(tableName == "SalesWorkers")    queryText = "INSERT INTO Workers (SalesID) VALUES('" +query.value(0).toString() + "')";

    if (!sdb.open()) return OPEN_DATABASE_ERROR;
    doQuery(queryText);

    return 0;
}

int DataBaseAdapter::addNewUser(QString userName, QString password, int workerId)
{
    if (!sdb.open()) return OPEN_DATABASE_ERROR;


    QString queryText = "INSERT into users('id','userName','hash') values('%id%', '%userName%', '%hash%')";

    queryText.replace("%id%",QString::number(workerId));                                                    //Замена шаблона имени настоящим именем работника
    queryText.replace("%userName%",userName);                                                               //Замена шаблона имени настоящим именем работника
    queryText.replace("%hash%",QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5));        //Замена шаблона даты поступления настоящей датой

    doQuery(queryText);

    return 0;
}

int DataBaseAdapter::doQuery(QString queryText)
{
    QSqlQuery query;

    if(!query.exec(queryText)) return QUERY_EXEC_ERROR;
    sdb.commit();
    sdb.close();

    return 0;
}

UserData DataBaseAdapter::getUserData(QString userName)
{
    UserData userData;
    QString queryText;
    QSqlQuery query;

    userData.userName = "";
    userData.hash     = "";

    if (!sdb.open()) return userData;

    queryText = "SELECT * FROM users WHERE userName = '"+userName+"'";
    query.exec(queryText);

    if(!query.next()) return userData;

    userData.workerId = query.value(0).toInt();
    userData.userName = query.value(1).toString();
    userData.hash = query.value(2).toString();

    if(query.value(0).toString() != "")
    {
        UserData temp    = getWorkerData(query.value(0).toInt());
        userData.fio     = temp.fio;
        userData.date    = temp.date;
        userData.basePay = temp.basePay;
        userData.master  = temp.master;
        userData.type    = temp.type;
    }

    //sdb.close();

    return userData;
}

UserData DataBaseAdapter::getWorkerData(int workerID)
{
    UserData userData;
    QString queryText;
    QSqlQuery query;

    userData.userName = "";
    userData.hash     = "";

    if (!sdb.open()) return userData;

    queryText = "SELECT EmployeeID,ManageID,SalesID FROM workers WHERE id = '"+QString::number(workerID)+"'";
    query.exec(queryText);

    query.next();

    if(IS_IMPLOYEE)
    {
        queryText = "SELECT workerName, date, cash, master FROM EmployeeWorkers WHERE id=" + query.value(0).toString();
        userData.type = "0";
    }
    if(IS_MANAGE)
    {
        queryText = "SELECT workerName, date, cash, master FROM ManageWorkers WHERE id="   + query.value(1).toString();
        userData.type = "1";
    }
    if(IS_SALES)
    {
        queryText = "SELECT workerName, date, cash, master FROM SalesWorkers WHERE id="    + query.value(2).toString();
        userData.type = "2";
    }

    query.exec(queryText);

    query.next();

    userData.fio      = query.value(0).toString();
    userData.date     = query.value(1).toString();
    userData.basePay  = query.value(2).toInt();
    userData.master   = query.value(3).toInt();

    return userData;
}

int DataBaseAdapter::getLastWorkerId()
{
    return lastWorkerID;
}

DB_Table DataBaseAdapter::getSubordinates(int masterID)
{
    QString sqlQuery = "SELECT workerName,date,cash FROM EmployeeWorkers WHERE EmployeeWorkers.master = %masterID% UNION SELECT workerName,date,cash FROM SalesWorkers WHERE SalesWorkers.master = %masterID% UNION SELECT workerName,date,cash FROM ManageWorkers WHERE ManageWorkers.master = %masterID%";
    sqlQuery = sqlQuery.replace("%masterID%",QString::number(masterID));

    return getTable(sqlQuery,3);
}
