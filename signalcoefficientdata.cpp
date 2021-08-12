#include "signalcoefficientdata.h"

SignalCoefficientData::SignalCoefficientData(QString function, qint32 registerNumber, QModbusDataUnit::RegisterType type,  qreal A, qreal B, qreal C, qreal D)
{
    this->function = function;
    this->registerNumber = registerNumber;
    this->type = type;
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}

qint32 SignalCoefficientData::getRegisterNumber() const{
    return registerNumber;
}

QModbusDataUnit::RegisterType SignalCoefficientData::getType() const{
    return type;
}

qreal SignalCoefficientData::getA() const{
    return A;
}

qreal SignalCoefficientData::getB() const{
    return B;
}

qreal SignalCoefficientData::getC() const{
    return C;
}

qreal SignalCoefficientData::getD() const{
    return D;
}

QString SignalCoefficientData::getFunction() const{
    return function;
}
