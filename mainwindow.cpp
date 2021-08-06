#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogsettings.h"
#include "serialPortSettingsDialog.h"
#include <QDebug>
#include <QModbusServer>
#include <QtCharts>
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include <QTextStream>
#include <QApplication>
#include <QModbusRtuSerialSlave>

const QString strConnect="Установить соединение";
const QString strDisconnect="Разорвать соединение";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isConnected=false;
    ui->connectButton->setText(strConnect);
    ui->textEdit->setReadOnly(true);
    slaveDevice = new QModbusRtuSerialSlaveLogger(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (slaveDevice){
        slaveDevice->disconnectDevice();
        delete slaveDevice;
    }
}


void MainWindow::on_settings_dialog_accept(PortInfo * portInfo){
    this->portInfo = portInfo;
    slaveDevice->setConnectionParameter(QModbusRtuSerialSlave::SerialPortNameParameter, portInfo->getName());
    slaveDevice->setConnectionParameter(QModbusRtuSerialSlave::SerialBaudRateParameter, portInfo->getBaudRate());
    slaveDevice->setConnectionParameter(QModbusRtuSerialSlave::SerialParityParameter, portInfo->getParityControl());
    slaveDevice->setConnectionParameter(QModbusRtuSerialSlave::SerialDataBitsParameter, portInfo->getDataBits());
    slaveDevice->setConnectionParameter(QModbusRtuSerialSlave::SerialStopBitsParameter, portInfo->getStopBitsCount());
}

void MainWindow::on_actionSerialPortSettings_2_triggered()
{
    SerialPortSettingsDialog* dialog = new SerialPortSettingsDialog(this);
    connect(dialog, &SerialPortSettingsDialog::getFilledData, this, &MainWindow::on_settings_dialog_accept);
    dialog->exec();
}

void MainWindow::on_actionSlaveNumberSetting_triggered()
{
    DialogSettings* dialog=new DialogSettings();
    connect(dialog, &DialogSettings::onAcceptSignal, this, &MainWindow::on_server_number_accepted);
    dialog->exec();

}

void MainWindow::on_server_number_accepted(qint32 number){
    this->serverNumber = number;
}

void MainWindow::on_connectButton_clicked()
{
    if(isConnected){
        modbusDisconnect();
    }
    else modbusConnect();
}
void MainWindow::modbusDisconnect(){
    slaveDevice->disconnectDevice();
    if (changeRegisterThread) {
        changeRegisterThread->requestInterruption();
    }
}
void MainWindow::modbusConnect()
{
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10000 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10000 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10000 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10000 });
    slaveDevice->setMap(reg);
    connect(slaveDevice, &QModbusServer::dataWritten,
            this, &MainWindow::updateWidgets);
    connect(slaveDevice, &QModbusServer::stateChanged,
            this, &MainWindow::onStateChanged);
    connect(slaveDevice, &QModbusServer::errorOccurred,
            this, &MainWindow::handleDeviceError);
    connect(slaveDevice, &QModbusRtuSerialSlaveLogger::logRequest, this, &MainWindow::handleDeviceLog);
    bool connected = slaveDevice->connectDevice();

    isConnected = connected;
    if (!connected) {
        statusBar()->showMessage(tr("Connect failed: ") + slaveDevice->errorString(), 5000);
    } else {
        statusBar()->showMessage(tr("Connected"));
        QChartView * qChartView = new QChartView(this);
        QLineSeries * series = new QLineSeries();
        chart = new QChart();
        chart->addSeries(series);
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(-1, 1);
        chart->addAxis(axisY, Qt::AlignLeft);
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, 4);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        chart->legend()->hide();
        qChartView->setChart(chart);
        ui->graphLayout->addWidget(qChartView);
        changeRegisterThread = new ChangeRegister(this->reg, this->slaveDevice, series, chart);
        connect(changeRegisterThread, &ChangeRegister::finished, changeRegisterThread, &ChangeRegister::deleteLater);
        changeRegisterThread->start();
    }
}

void MainWindow::handleDeviceLog(QString logLine){
    ui->textEdit->append(logLine);
    ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
}

void MainWindow::handleDeviceError(QModbusDevice::Error newError)
{
    if (newError == QModbusDevice::NoError || !slaveDevice)
        return;
    statusBar()->showMessage(slaveDevice->errorString(), 5000);
}

void MainWindow::onStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
    isConnected = connected;
    if (state == QModbusDevice::UnconnectedState){
        ui->textEdit->append(QTime::currentTime().toString("hh:mm:ss") + " устройство отключено");
        ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
        ui->connectButton->setText(strConnect);
        statusBar()->showMessage(tr(""));
    }
    else if (state == QModbusDevice::ConnectedState) {
        ui->connectButton->setText(strDisconnect);
        ui->textEdit->append(QTime::currentTime().toString("hh:mm:ss") + " устройство подключено");
        ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
    }
}


void MainWindow::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; ++i) {
        quint16 value;
        QString text;
        switch (table) {
        case QModbusDataUnit::Coils:
            slaveDevice->data(QModbusDataUnit::Coils, quint16(address + i), &value);
            //coilButtons.button(address + i)->setChecked(value);
            break;
        case QModbusDataUnit::HoldingRegisters:
            slaveDevice->data(QModbusDataUnit::HoldingRegisters, quint16(address + i), &value);
            registers.value(QStringLiteral("holdReg_%1").arg(address + i))->setText(text
                .setNum(value, 16));
            break;
        default:
            break;
        }
    }
}


