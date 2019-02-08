#ifndef MANAGERWORKER_H
#define MANAGERWORKER_H

#include "employeeworker.h"

class ManagerWorker : BaseWorker
{

public:
    void   setMaster(BaseWorker master);
    void   addSubordinate(BaseWorker *subordinate);
    double calculatePay();
    ManagerWorker(QString name, int basePay, QDate date,int additionalPart);
};

#endif // MANAGERWORKER_H
