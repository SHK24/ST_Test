#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QList>
#include <QString>
#include <QDate>
#include <../ST_test/databaseadapter.h>

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
    void   setMaster(BaseWorker * master);
    void   addSubordinate(BaseWorker * subordinate);
    virtual double calculatePay(QDate date);

    void setName(QString name);
    void setBasePay(int pay);
    void setDate(QDate date);

    QString getName();
    int     getBasePay();
    QDate   getDate();
    BaseWorker*   getMaster();
    QList<BaseWorker*> getSubordinates();
};

#endif // BASEWORKER_H
