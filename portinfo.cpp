#include "portinfo.h"

PortInfo::PortInfo(QString name, QString baudRate, QString dataBits,
                   QString parityControl, QString flowControl, QString stopBitsCount)
{
    this->name = name;
    this->baudRate = baudRate;
    this->dataBits = dataBits;
    this->parityControl = parityControl;
    this->flowControl = flowControl;
    this->stopBitsCount = stopBitsCount;
}

QString PortInfo::getName() const{
    return this->name;
}

QString PortInfo::getBaudRate() const {
    return this->baudRate;
}

QString PortInfo::getDataBits() const{
    return this->dataBits;
}

QString PortInfo::getParityControl() const{
    return this->parityControl;
}

QString PortInfo::getFlowControl() const{
    return this->flowControl;
}

QString PortInfo::getStopBitsCount() const{
    return this->stopBitsCount;
}
