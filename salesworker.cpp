#include "salesworker.h"

SalesWorker::SalesWorker(QString name, int basePay, QDate date)
{
    this->name           = name;
    this->basePay        = basePay;
    this->date           = date;
    this->additionalPart = additionalPart;
}

double SalesWorker::calculatePay(QDate date)
{
    double sum = 0;
    int years = this->date.daysTo(date) / 365;

    int percents = years;

    if(percents > 35) percents = 35;

    for(int i = 0; i < subordinates.count();i++)
    {
        sum += subordinates[i]->calculatePay(date);
        QList<BaseWorker*>subsubordinates = subordinates[i]->getSubordinates();
        for(int k = 0; k < subsubordinates.count();k++)
        sum += subsubordinates[k]->calculatePay(date);
    }

    return this->basePay + this->basePay/100.0 * percents + sum*0.03;
}


