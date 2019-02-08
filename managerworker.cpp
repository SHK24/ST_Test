#include "managerworker.h"

void ManagerWorker::setMaster(BaseWorker master)
{

}

void ManagerWorker::addSubordinate(BaseWorker * subordinate)
{
    subordinates.append(subordinate);
}

double ManagerWorker::calculatePay()
{
    int sum = 0;

    int percents = (QDate::currentDate().year() - this->date.year()) * 5;

    if(percents > 40) percents = 40;

    for(int i = 0; i < subordinates.count();i++)
    sum += subordinates[i]->calculatePay();


    return this->basePay + this->basePay/100.0 * percents + sum*0.05;
}

ManagerWorker::ManagerWorker(QString name, int basePay, QDate date, int additionalPart)
{
    this->name           = name;
    this->basePay        = basePay;
    this->date           = date;
    this->additionalPart = additionalPart;
}
