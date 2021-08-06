#ifndef CHANGEREGISTER_H
#define CHANGEREGISTER_H
#include <QRunnable>
#include <QModbusDataUnitMap>
#include <QModbusRtuSerialSlave>
#include <QThread>
#include <QtCharts>

class ChangeRegister: public QThread
{
public:
    ChangeRegister(QModbusDataUnitMap & map, QModbusRtuSerialSlave *slaveDevice, QLineSeries * series, QChart * chart);
    void run();
private:
    template <typename T> qint32 sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
    QModbusDataUnitMap * map;
    QModbusRtuSerialSlave *slaveDevice;
    QLineSeries * series;
    QChart * chart;
};

#endif // CHANGEREGISTER_H
