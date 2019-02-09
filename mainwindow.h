#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employeeworker.h"
#include "managerworker.h"
#include <QPushButton>
#include "databaseadapter.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPushButton login;
    QString admPasswd = "NO_PASSWORD";
    DataBaseAdapter dbAdapter;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_doLogin_clicked();

    void on_setAdminPasswd_clicked();

    void on_add_clicked();

    void on_addWorker_clicked();

private:
    Ui::MainWindow *ui;
    QString types[3] = {"Employee","Manage","Sales"};
    BaseWorker * currentWorker;
    QList<int> workerIdList;

    void setAdminElementsVisible(bool state);
    void setPersonalManageElementsVisible(bool state);
    void setMyPageVisible(bool state);
    void fillUsersTable();
    void fillWorkersTable();
    void fillWorkersList();
};

#endif // MAINWINDOW_H
