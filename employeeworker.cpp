#include "employeeworker.h"

EmployeeWorker::EmployeeWorker(QString name, int basePay, QDate date)
{
    this->name = name;
    this->basePay = basePay;
    this->date = date;
    this->additionalPart = additionalPart;
}

double EmployeeWorker::calculatePay(QDate date)
{
    int years = this->date.daysTo(date) / 365;

    int percents = years * 3;

    if(percents > 30) percents = 30;

    return this->basePay + this->basePay/100.0 * percents;
}
