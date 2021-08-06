#ifndef SERIALPORTSETTINGSDIALOG_H
#define SERIALPORTSETTINGSDIALOG_H

#include <QDialog>
#include <QWidget>
#include "portinfo.h"

namespace Ui { class SerialPortSettingsDialog; }
/// Класс виджета настроек последовательного порта.
/// public:

enum Direction  {
    Input = 1,
    Output = 2,
    AllDirections = Input | Output
};
Q_DECLARE_FLAGS(Directions, Direction)

enum BaudRate {
    Baud1200 = 1200,
    Baud2400 = 2400,
    Baud4800 = 4800,
    Baud9600 = 9600,
    Baud19200 = 19200,
    Baud38400 = 38400,
    Baud57600 = 57600,
    Baud115200 = 115200,
    UnknownBaud = -1
};

enum DataBits {
    Data5 = 5,
    Data6 = 6,
    Data7 = 7,
    Data8 = 8,
    UnknownDataBits = -1
};

enum Parity {
    NoParity = 0,
    EvenParity = 2,
    OddParity = 3,
    SpaceParity = 4,
    MarkParity = 5,
    UnknownParity = -1
};

enum StopBits {
    OneStop = 1,
    OneAndHalfStop = 3,
    TwoStop = 2,
    UnknownStopBits = -1
};

enum FlowControl {
    NoFlowControl,
    HardwareControl,
    SoftwareControl,
    UnknownFlowControl = -1
};

enum PinoutSignal {
    NoSignal = 0x00,
    TransmittedDataSignal = 0x01,
    ReceivedDataSignal = 0x02,
    DataTerminalReadySignal = 0x04,
    DataCarrierDetectSignal = 0x08,
    DataSetReadySignal = 0x10,
    RingIndicatorSignal = 0x20,
    RequestToSendSignal = 0x40,
    ClearToSendSignal = 0x80,
    SecondaryTransmittedDataSignal = 0x100,
    SecondaryReceivedDataSignal = 0x200
};

class SerialPortSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /// Конструктор. Принимает указатель на структуру настроек последовательного порта.
    explicit SerialPortSettingsDialog(QWidget *parent = 0);
    /// Деструктор.
    ~SerialPortSettingsDialog();

signals:
    void getFilledData(PortInfo * portInfo);
public slots:
    void okAccept();

private:
    Ui::SerialPortSettingsDialog *ui; ///< GUI элементы этого виджета.

    void avianlePortsToCombo();
};

#endif // SERIALPORTSETTINGSDIALOG_H
