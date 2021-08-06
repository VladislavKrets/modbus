#include "changeregister.h"
#include <QtMath>
#include <QTextStream>

ChangeRegister::ChangeRegister(QModbusDataUnitMap & map, QModbusRtuSerialSlave *slaveDevice, QLineSeries * series, QChart * chart)
{
    this->map = &map;
    this->slaveDevice = slaveDevice;
    this->series = series;
    this->chart = chart;
}

void ChangeRegister::run(){
    float randNumber;
    quint32 *raw;
    quint16 high;
    quint16 low;
    QTextStream out(stdout);
    for (qreal i = 0; !QThread::currentThread()->isInterruptionRequested(); i+=0.1){
        randNumber = qSin(i);
        raw = reinterpret_cast<quint32 *>(&randNumber);
        high = *raw >> 16;
        low = *raw & 0xFFFF;
        // little endian
        (*map)[QModbusDataUnit::InputRegisters].setValue(1, low);
        (*map)[QModbusDataUnit::InputRegisters].setValue(2, high);
        slaveDevice->setMap(*map);
        series->append(i, randNumber);
        if(i >= 4) chart->scroll(chart->plotArea().width() / 47, 0);
        QThread::msleep(1000);
    }
}
