#ifndef SALESWORKER_H
#define SALESWORKER_H

#include "managerworker.h"

class SalesWorker : public BaseWorker
{
public:
    SalesWorker(QString name, int basePay, QDate date);
    virtual double calculatePay(QDate date);
};

#endif // SALESWORKER_H
