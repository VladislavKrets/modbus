#include "changeregister.h"
#include <QtMath>

ChangeRegister::ChangeRegister(QModbusDataUnitMap & map, QModbusRtuSerialSlave *slaveDevice, QList<ChangeRegisterThreadData *> * dataList)
{
    this->map = &map;
    this->slaveDevice = slaveDevice;
    this->dataList = dataList;
}

void ChangeRegister::run(){
    qreal delta = 0.1;
    for (qreal i = 0; !QThread::currentThread()->isInterruptionRequested(); i+=delta){
        foreach (ChangeRegisterThreadData * data, *dataList) {
            executeChangeData(data, delta, i);
            QThread::msleep(1000);
        }
    }
}

void ChangeRegister::executeChangeData(ChangeRegisterThreadData *changeData, qreal delta, qreal i){
    QLineSeries * series = changeData->getSeries();
    SignalCoefficientData * data = changeData->getData();
    QValueAxis *axisX = changeData->getAxisX();
    QValueAxis * axisY = changeData->getAxisY();
    PrevValues * values = changeData->getPrevValues();
    float functionValue;
    quint32 *raw;
    quint16 high;
    quint16 low;

    if (data->getFunction() == "Синусоида") functionValue = data->getA() * qSin(data->getB() * i + data->getC()) + data->getD();
    else functionValue = sgn(data->getA() * qSin(data->getB() * i + data->getC()) + data->getD());
    if (i > values->prevMaxX) {
        values->prevMaxX = i + delta;
        values->prevMinX += delta;
    }
    if (functionValue > values->prevMaxY) values->prevMaxY = functionValue + 0.1;
    if (functionValue < values->prevMinY) values->prevMinY = functionValue - 0.1;
    axisX->setRange(values->prevMinX, values->prevMaxX);
    axisY->setRange(values->prevMinY, values->prevMaxY);
    raw = reinterpret_cast<quint32 *>(&functionValue);
    high = *raw >> 16;
    low = *raw & 0xFFFF;
    // little endian
    (*map)[data->getType()].setValue(data->getRegisterNumber(), low);
    (*map)[data->getType()].setValue(data->getRegisterNumber() + 1, high);
    slaveDevice->setMap(*map);
    series->append(i, functionValue);
}
