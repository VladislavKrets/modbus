#include "qmodbusrtuserialslavelogger.h"
#include <QTime>
QModbusRtuSerialSlaveLogger::QModbusRtuSerialSlaveLogger(QObject *parent): QModbusRtuSerialSlave(parent)
{

}

QModbusResponse QModbusRtuSerialSlaveLogger::processRequest(const QModbusPdu &request){
    QTime currentTime =  QTime::currentTime();
    QString logLine = currentTime.toString("hh:mm:ss, запрос -> ");
    quint16 address, count;
    request.decodeData(&address, &count);
    switch (request.functionCode()) {
        case QModbusRequest::ReadCoils:
            logLine += "чтение coils";
        break;
        case QModbusRequest::ReadDiscreteInputs:
            logLine += "чтение disrete coils";
        break;
        case QModbusRequest::ReadHoldingRegisters:
            logLine += "чтение holding coils";
            break;
        case QModbusRequest::ReadInputRegisters:
            logLine += "чтение input coils";
            break;
        case QModbusRequest::WriteSingleCoil:
            logLine += "запись single coil";
            break;
        case QModbusRequest::WriteSingleRegister:
            logLine += "запись single register";
            break;
        case QModbusRequest::ReadExceptionStatus:
            logLine += "чтение статуса исключения";
            break;
        case QModbusRequest::Diagnostics:
            logLine += "";
            break;
        case QModbusRequest::GetCommEventCounter:
            logLine += "получение счетчика событий";
            break;
        case QModbusRequest::GetCommEventLog:
            logLine += "получение лога событий";
            break;
        case QModbusRequest::WriteMultipleCoils:
            logLine += "запись множества coils";
            break;
        case QModbusRequest::WriteMultipleRegisters:
            logLine += "запись множества регистров";
            break;
        case QModbusRequest::ReportServerId:
            logLine += "репорт server id";
            break;
        case QModbusRequest::MaskWriteRegister:
            logLine += "пометка регистра записи";
            break;
        case QModbusRequest::ReadWriteMultipleRegisters:
            logLine += "чтение запись множества регистров";
            break;
        case QModbusRequest::ReadFifoQueue:
            logLine += "чтение очереди FIFO";
            break;
        case QModbusRequest::EncapsulatedInterfaceTransport:
            logLine += "инкапсулированная интерфейсная передача";
            break;
        default:
            break;
        }
    logLine += ", адрес начала: %1, количество: %2";
    logLine = logLine.arg(address).arg(count);
    emit this->logRequest(logLine);
    return QModbusRtuSerialSlave::processRequest(request);
}
