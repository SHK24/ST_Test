#include "managerworker.h"

double ManagerWorker::calculatePay(QDate date)
{
    double sum = 0;
    int years = this->date.daysTo(date) / 365;

    int percents = years * 5;

    if(percents > 40) percents = 40;

    for(int i = 0; i < subordinates.count();i++)
    sum += subordinates[i]->calculatePay(QDate::currentDate());


    return this->basePay + this->basePay/100.0 * percents + sum*0.005;
}

ManagerWorker::ManagerWorker(QString name, int basePay, QDate date)
{
    this->name           = name;
    this->basePay        = basePay;
    this->date           = date;
}
