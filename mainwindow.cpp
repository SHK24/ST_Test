#include "mainwindow.h"
#include "ui_mainwindow.h"

#define EMPLOYEE 0
#define MANAGE   1
#define SALES    2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*QDate dd(2010,2,27);
    EmployeeWorker worker("Иванов Петр Владимирович",10000,dd,10);
    EmployeeWorker worker1("Иванов Петр Иванович",20000,dd,10);
    EmployeeWorker worker2("Иванов Алексей Владимирович",30000,dd,10);

    ManagerWorker manager("Иванов Владимир Владимирович",100000,dd,10);

    manager.addSubordinate(&worker);
    manager.addSubordinate(&worker1);
    manager.addSubordinate(&worker2);

    int pay = manager.calculatePay();

    int a = 5;*/

    fillWorkersList();

    //setAdminElementsVisible(false);
    //setPersonalManageElementsVisible(false);
    //setMyPageVisible(false);

    //UserData userData = dbAdapter.getUserData("test1");
    UserData userData = dbAdapter.getUserData("admin");
    admPasswd = userData.hash;

    if(userData.userName == "")
    {
        ui->userName->setEnabled(false);
        ui->userName->setText("admin");
        ui->doLogin->setVisible(false);
    }

    ui->employeeWorkersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->manageWorkersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->salesWorkersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->usersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->subordinatesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_doLogin_clicked()
{
    QString userName = ui->userName->text();
    QString password = ui->password->text();

    UserData userData = dbAdapter.getUserData("admin");

    if(userData.userName == "") return;

    if(userName == "admin")
    {
        if(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5) == admPasswd)
        {
            setAdminElementsVisible(true);
            setPersonalManageElementsVisible(true);
            fillWorkersTable();
            fillUsersTable();
        }

        return;
    }

    if(userName == userData.userName)
    {
        if(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5) == userData.hash)
        {
            switch(userData.type.toInt())
            {
                case EMPLOYEE:
                {
                    QDate date = QDate::fromString(userData.date,"dd.MM.yyyy");

                    EmployeeWorker worker(userData.userName,userData.basePay,date,0);
                    ui->currentPayment->setText(QString::number(worker.calculatePay(),'f',3));
                }break;

                case MANAGE:
                {
                    ManagerWorker temp(userData.fio,userData.basePay,QDate::fromString(userData.date,"dd.MM.yyyy"),0);

                    //ManagerWorker * temp = new ManagerWorker(userData.fio,userData.basePay,QDate::fromString(userData.date,"dd.MM.yyyy"),0);
                    //currentWorker = (BaseWorker*)&temp;

                    QString sqlQuery = "SELECT FIO,TYPE,DATE,BASEPAY FROM workers WHERE MASTER = " + QString::number(userData.workerId);
                    DB_Table table = dbAdapter.getTable(sqlQuery,4);

                    ui->subordinatesTable->setRowCount(table.rowCount);
                    ui->subordinatesTable->setColumnCount(table.colCount);

                    for(int i = 0; i < table.rowCount;i++)
                    {
                        temp.addSubordinate(new EmployeeWorker(table.table[i][0],table.table[i][3].toInt(),QDate::fromString(table.table[i][2],"dd.MM.yyyy"),0));

                        ui->subordinatesTable->setItem(i,0,new QTableWidgetItem(table.table[i][0]));
                        ui->subordinatesTable->setItem(i,1,new QTableWidgetItem(types[table.table[1]->toInt()]));
                        ui->subordinatesTable->setItem(i,2,new QTableWidgetItem(table.table[i][2]));
                        ui->subordinatesTable->setItem(i,3,new QTableWidgetItem(table.table[i][3]));
                    }

                    ui->currentPayment->setText(QString::number(temp.calculatePay(),'f',3));

                    ui->tabWidget->setCurrentIndex(3);

                }break;

                case SALES:
                {

                }break;
            }
        }
    }
}

void MainWindow::on_setAdminPasswd_clicked()
{
    dbAdapter.addNewUser("admin",ui->password->text());
}

void MainWindow::setAdminElementsVisible(bool state)
{
    ui->warning->setVisible(!state);
    ui->newUserName_label->setVisible(state);
    ui->newPassword_label->setVisible(state);
    ui->newUserName->setVisible(state);
    ui->newPassword->setVisible(state);
    ui->usersTable->setVisible(state);
    ui->add->setVisible(state);
}

void MainWindow::setPersonalManageElementsVisible(bool state)
{
    ui->warning_2->setVisible(!state);

    ui->workerName_label->setVisible(state);
    ui->workerName->setVisible(state);

    ui->date_label->setVisible(state);
    ui->date->setVisible(state);

    ui->basePay_label->setVisible(state);
    ui->basePay->setVisible(state);

    ui->workerType_label->setVisible(state);
    ui->workerType->setVisible(state);

    ui->createUserAcc->setVisible(state);

    ui->newUserNamePM_label->setVisible(state);
    ui->newUserNamePM->setVisible(state);

    ui->newUserPasswordPM_label->setVisible(state);
    ui->newUserPasswordPM->setVisible(state);

    ui->EmployeeWorkersTable_label->setVisible(state);
    ui->employeeWorkersTable->setVisible(state);

    ui->manageWorkersTable_label->setVisible(state);
    ui->manageWorkersTable->setVisible(state);

    ui->salesWorkersTable_label->setVisible(state);
    ui->salesWorkersTable->setVisible(state);

    ui->master->setVisible(state);
    ui->master_label->setVisible(state);

    ui->addWorker->setVisible(state);
    ui->deleteWorker->setVisible(state);
}

void MainWindow::setMyPageVisible(bool state)
{
    ui->warning_3->setVisible(!state);
    ui->currentCash->setVisible(state);
    ui->subordinates_label->setVisible(state);
    ui->subordinatesTable->setVisible(state);
}


void MainWindow::fillUsersTable()
{
    DB_Table result = dbAdapter.getUsersTable();

    ui->usersTable->setRowCount(result.rowCount);
    ui->usersTable->setColumnCount(result.colCount);

    for(int i = 0; i < result.rowCount;i++)
    {
        ui->usersTable->setItem(i,0,new QTableWidgetItem(result.table[i][0]));
        ui->usersTable->setItem(i,1,new QTableWidgetItem(result.table[i][1]));
        ui->usersTable->setItem(i,2,new QTableWidgetItem(result.table[i][2]));
        ui->usersTable->setItem(i,3,new QTableWidgetItem(result.table[i][3]));
    }
}

void MainWindow::fillWorkersTable()
{
    DB_Table result = dbAdapter.getEmployeeWorkersTable();

    ui->employeeWorkersTable->setRowCount(result.rowCount);
    ui->employeeWorkersTable->setColumnCount(result.colCount);

    for(int i = 0; i < result.rowCount;i++)
    {
        ui->employeeWorkersTable->setItem(i,0,new QTableWidgetItem(result.table[i][WORKER_NAME]));
        ui->employeeWorkersTable->setItem(i,1,new QTableWidgetItem(result.table[i][DATE]));
        ui->employeeWorkersTable->setItem(i,2,new QTableWidgetItem(result.table[i][CASH]));
        ui->employeeWorkersTable->setItem(i,3,new QTableWidgetItem(result.table[i][MASTER]));
    }

    result = dbAdapter.getManageWorkersTable();

    ui->manageWorkersTable->setRowCount(result.rowCount);
    ui->manageWorkersTable->setColumnCount(result.colCount);

    for(int i = 0; i < result.rowCount;i++)
    {
        ui->manageWorkersTable->setItem(i,0,new QTableWidgetItem(result.table[i][WORKER_NAME]));
        ui->manageWorkersTable->setItem(i,1,new QTableWidgetItem(result.table[i][DATE]));
        ui->manageWorkersTable->setItem(i,2,new QTableWidgetItem(result.table[i][CASH]));
        ui->manageWorkersTable->setItem(i,3,new QTableWidgetItem(result.table[i][MASTER]));
    }

    result = dbAdapter.getSalesWorkersTable();

    ui->salesWorkersTable->setRowCount(result.rowCount);
    ui->salesWorkersTable->setColumnCount(result.colCount);

    for(int i = 0; i < result.rowCount;i++)
    {
        ui->salesWorkersTable->setItem(i,0,new QTableWidgetItem(result.table[i][WORKER_NAME]));
        ui->salesWorkersTable->setItem(i,1,new QTableWidgetItem(result.table[i][DATE]));
        ui->salesWorkersTable->setItem(i,2,new QTableWidgetItem(result.table[i][CASH]));
        ui->salesWorkersTable->setItem(i,3,new QTableWidgetItem(result.table[i][MASTER]));
    }
}

void MainWindow::fillWorkersList()
{
    DB_Table result = dbAdapter.getTable("SELECT workerName,Workers.id FROM EmployeeWorkers,Workers WHERE EmployeeWorkers.id = Workers.EmployeeID",2);

    for(int i = 0 ; i < result.rowCount;i++)
    {
        ui->workerList->addItem("[Employee] " + result.table[i][0] + " ID:" + result.table[i][1]);
        workerIdList.append(result.table[i][1].toInt());
    }

//    result = dbAdapter.getTable("SELECT workerName,id FROM ManageWorkers",2);

//    for(int i = 0 ; i < result.rowCount;i++)
//        ui->workerList->addItem("[Manage] " + result.table[i][0]);

//    result = dbAdapter.getTable("SELECT workerName,id FROM SalesWorkers",2);

//    for(int i = 0 ; i < result.rowCount;i++)
//        ui->workerList->addItem("[Sales] " + result.table[i][0]);
}

void MainWindow::on_add_clicked()
{
    dbAdapter.addNewUser(ui->newUserName->text(), ui->newPassword->text(),workerIdList[ui->workerList->currentIndex()]);
    //addUser(ui->newUserName->text(), ui->newPassword->text());
}

void MainWindow::on_addWorker_clicked()
{
    QString tableName = "";

    switch(ui->workerType->currentIndex())
    {
        case EMPLOYEE:
        {
            tableName = "EmployeeWorkers";
        }break;

        case MANAGE:
        {
            tableName = "ManageWorkers";
        }break;

        case SALES:
        {
            tableName = "SalesWorkers";
        }break;
    }

    dbAdapter.addNewWorker(tableName,ui->workerName->text(),ui->date->text(),ui->basePay->text().toInt(),0);

    fillWorkersTable();

//    dbAdapter.addNewWorker(ui->workerName->text(),ui->workerType->currentIndex(),ui->date->text(),ui->basePay->text().toInt());
//    fillWorkersTable();

//    if(ui->createUserAcc->isChecked())
//    {
//        dbAdapter.addNewUser(ui->newUserNamePM->text(),ui->newUserPasswordPM->text(),dbAdapter.getLastWorkerId());
//        fillUsersTable();
//    }
}
