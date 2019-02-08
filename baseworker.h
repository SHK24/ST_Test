#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QList>
#include <QString>
#include <QDate>

class BaseWorker
{
protected:
    QString name;

    int basePay;
    QDate date;

    unsigned char additionalPart;
    unsigned char maxAdditionalPart;
    unsigned char years;
    BaseWorker* master;
    QList<BaseWorker*> subordinates;
private:

public:
    BaseWorker();
    virtual void   setMaster(BaseWorker master);
    virtual void   addSubordinate(BaseWorker subordinate);
    virtual double calculatePay();
};

#endif // BASEWORKER_H
