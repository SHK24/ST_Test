#ifndef EMPLOYEEWORKER_H
#define EMPLOYEEWORKER_H

#include "baseworker.h"

class EmployeeWorker : public BaseWorker
{
public:
    void setMaster(BaseWorker master);
    double calculatePay();
    EmployeeWorker(QString name, int basePay, QDate date,int additionalPart);
};

#endif // EMPLOYEEWORKER_H
