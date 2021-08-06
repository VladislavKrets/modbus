#ifndef QMODBUSRTUSERIALSLAVELOGGER_H
#define QMODBUSRTUSERIALSLAVELOGGER_H
#include <QModbusRtuSerialSlave>

class QModbusRtuSerialSlaveLogger: public QModbusRtuSerialSlave
{
    Q_OBJECT
protected:
    QModbusResponse processRequest(const QModbusPdu &request);
signals:
    void logRequest(QString logLine);
public:
    explicit QModbusRtuSerialSlaveLogger(QObject *parent = nullptr);
    QModbusRtuSerialSlaveLogger();
};

#endif // QMODBUSRTUSERIALSLAVELOGGER_H
