#ifndef SIGNALCOEFFICIENTDATA_H
#define SIGNALCOEFFICIENTDATA_H
#include <QtGlobal>
#include <QString>
#include <QModbusDataUnit>

class SignalCoefficientData
{
public:
    SignalCoefficientData(QString function, qint32 registerNumber, QModbusDataUnit::RegisterType type, qreal A, qreal B, qreal C, qreal D);
    qreal getA() const;
    qreal getB() const;
    qreal getC() const;
    qreal getD() const;
    qint32 getRegisterNumber() const;
    QString getFunction() const;
    QModbusDataUnit::RegisterType getType() const;
private:
    QString function;
    qint32 registerNumber;
    QModbusDataUnit::RegisterType type;
    qreal A;
    qreal B;
    qreal C;
    qreal D;
};

#endif // SIGNALCOEFFICIENTDATA_H
