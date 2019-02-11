#ifndef MANAGERWORKER_H
#define MANAGERWORKER_H

#include "baseworker.h"

class ManagerWorker : public BaseWorker
{

public:
    ManagerWorker(QString name, int basePay, QDate date);
    double calculatePay(QDate date);
};

#endif // MANAGERWORKER_H
