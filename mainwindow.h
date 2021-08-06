#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QModbusRtuSerialSlave>
#include <QModbusRtuSerialMaster>
#include <portinfo.h>
#include <QLineEdit>
#include <changeregister.h>

#if defined(QT_DEBUG)
#define QDEBUG(X) qDebug() << X;
#else
#define QDEBUG(X) ;
#endif
#include "qmodbusrtuserialslavelogger.h"
namespace Ui {
class MainWindow;
}
class QModbusSlave;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionSerialPortSettings_2_triggered();
    void on_actionSlaveNumberSetting_triggered();
    void on_connectButton_clicked();
    void on_settings_dialog_accept(PortInfo * portInfo);
    void on_server_number_accepted(qint32 serverNumber);
    void handleDeviceError(QModbusDevice::Error newError);
    void onStateChanged(int state);
    void updateWidgets(QModbusDataUnit::RegisterType table, int address, int size);
    void handleDeviceLog(QString logLine);

private:
    Ui::MainWindow *ui;
    QAction* setAction;
    void modbusConnect();
    void modbusDisconnect();
    bool isConnected;
    QModbusRtuSerialSlaveLogger *slaveDevice = nullptr;
    PortInfo * portInfo;
    QHash<QString, QLineEdit *> registers;
    qint32 serverNumber = 1;
    QModbusDataUnitMap & reg = *(new QModbusDataUnitMap());
    ChangeRegister * changeRegisterThread = nullptr;
    QChart * chart;
};

#endif // MAINWINDOW_H
