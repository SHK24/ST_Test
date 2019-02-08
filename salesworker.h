#ifndef SALESWORKER_H
#define SALESWORKER_H

#include "managerworker.h"

class SalesWorker : BaseWorker
{
public:
    SalesWorker();
    virtual void   addSubordinate(BaseWorker subordinate);
    virtual double calculatePay();
};

#endif // SALESWORKER_H
