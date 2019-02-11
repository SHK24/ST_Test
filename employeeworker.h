#ifndef EMPLOYEEWORKER_H
#define EMPLOYEEWORKER_H

#include "baseworker.h"

class EmployeeWorker : public BaseWorker
{
public:
    double calculatePay(QDate date);
    EmployeeWorker(QString name, int basePay, QDate date);
};

#endif // EMPLOYEEWORKER_H
