#include "baseworker.h"



BaseWorker::BaseWorker()
{

}

void BaseWorker::setMaster(BaseWorker *master)
{
    this->master = master;
}

void BaseWorker::addSubordinate(BaseWorker *subordinate)
{
    subordinates.append(subordinate);
}

double BaseWorker::calculatePay(QDate date){}

void BaseWorker::setName(QString name)
{
    this->name = name;
}

void BaseWorker::setBasePay(int pay)
{
    this->basePay = pay;
}

void BaseWorker::setDate(QDate date)
{
    this->date = date;
}

QString BaseWorker::getName()
{
    return this->name;
}

int BaseWorker::getBasePay()
{
    return this->basePay;
}

QDate BaseWorker::getDate()
{
    return this->date;
}

BaseWorker *BaseWorker::getMaster()
{
    return this->master;
}

QList<BaseWorker *> BaseWorker::getSubordinates()
{
    return this->subordinates;
}
