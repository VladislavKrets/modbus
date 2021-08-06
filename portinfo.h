#ifndef PORTINFO_H
#define PORTINFO_H

#include <QString>



class PortInfo
{
public:
    PortInfo(QString name, QString baudRate, QString dataBits, QString parityControl, QString flowControl, QString stopBitsCount);
    QString getName() const;
    QString getBaudRate() const;
    QString getDataBits() const;
    QString getParityControl() const;
    QString getFlowControl() const;
    QString getStopBitsCount() const;
private:
    QString name;
    QString baudRate;
    QString dataBits;
    QString parityControl;
    QString flowControl;
    QString stopBitsCount;
};

#endif // PORTINFO_H
