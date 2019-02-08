#include "employeeworker.h"

EmployeeWorker::EmployeeWorker(QString name, int basePay, QDate date,int additionalPart)
{
    this->name = name;
    this->basePay = basePay;
    this->date = date;
    this->additionalPart = additionalPart;
}


void EmployeeWorker::setMaster(BaseWorker master)
{
    this->master = &master;
}

double EmployeeWorker::calculatePay()
{
    int years = QDate::currentDate().year() - this->date.year();

    int percents = years * 3;

    if(percents > 30) percents = 30;

    return this->basePay + this->basePay/100.0 * percents;
}
