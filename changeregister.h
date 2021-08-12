#ifndef CHANGEREGISTER_H
#define CHANGEREGISTER_H
#include <QRunnable>
#include <QModbusDataUnitMap>
#include <QModbusRtuSerialSlave>
#include <QThread>
#include <QtCharts>
#include "signalcoefficientdata.h"
#include "changeregisterthreaddata.h"

class ChangeRegister: public QThread
{
public:
    ChangeRegister(QModbusDataUnitMap & map, QModbusRtuSerialSlave *slaveDevice, QList<ChangeRegisterThreadData *> * dataList);
    void run();
    void executeChangeData(ChangeRegisterThreadData * data, qreal delta, qreal i);
private:
    template <typename T> qint32 sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
    qreal max(qreal val1, qreal val2) {
        return val1 > val2 ? val1 : val2;
    }
    qreal min(qreal val1, qreal val2) {
        return val1 < val2 ? val1 : val2;
    }
    QModbusDataUnitMap * map;
    QModbusRtuSerialSlave *slaveDevice;
    QList<ChangeRegisterThreadData *> * dataList;
};
#endif // CHANGEREGISTER_H
