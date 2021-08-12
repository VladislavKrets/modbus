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
#include "signaldialog.h"

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
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10000 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10000 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10000 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10000 });
    slaveDevice->setMap(reg);

    QChartView * chartView = new QChartView(this);
    chartView->setVisible(false);
    QChartView * chartView2 = new QChartView(this);
    chartView2->setVisible(false);
    chartDataList->append(new ChartData(chartView, new SignalCoefficientData("Синусоида", 1, QModbusDataUnit::InputRegisters, 1, 1, 0, 0)));
    chartDataList->append(new ChartData(chartView2, new SignalCoefficientData("Меандр", 3, QModbusDataUnit::InputRegisters, 1, 1, 0, 0)));

    connect(slaveDevice, &QModbusServer::dataWritten,
            this, &MainWindow::updateWidgets);
    connect(slaveDevice, &QModbusServer::stateChanged,
            this, &MainWindow::onStateChanged);
    connect(slaveDevice, &QModbusServer::errorOccurred,
            this, &MainWindow::handleDeviceError);
    connect(slaveDevice, &QModbusRtuSerialSlaveLogger::logRequest, this, &MainWindow::handleDeviceLog);
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
    SerialPortSettingsDialog* dialog = new SerialPortSettingsDialog(this, portInfo);
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
    changeRegisterThread->requestInterruption();
}
void MainWindow::modbusConnect()
{
    bool connected = slaveDevice->connectDevice();
    isConnected = connected;
    if (!connected) {
        statusBar()->showMessage(tr("Connect failed: ") + slaveDevice->errorString(), 5000);
    } else {
        statusBar()->showMessage(tr("Connected"));

        QList<ChangeRegisterThreadData *> * dataList = new QList<ChangeRegisterThreadData *>();

        foreach(ChartData * chartData, *chartDataList){
            dataList->append(addChart(chartData));
        }

        changeRegisterThread = new ChangeRegister(this->reg,
                                                  this->slaveDevice, dataList);
        connect(changeRegisterThread, &ChangeRegister::finished, changeRegisterThread, &ChangeRegister::deleteLater);
        changeRegisterThread->start();
    }
}

ChangeRegisterThreadData * MainWindow::addChart(ChartData * chartData){
    QChartView * qChartView = chartData->getQChartView();
    if(!qChartView) qChartView = new QChartView(this);
    qChartView->setVisible(true);
    SignalCoefficientData * signalCoefficientData = chartData->getSignalCoefficientData();
    QChart * chart;
    if (qChartView->chart()) chart = new QChart();
    else chart = qChartView->chart();
    QList<QAbstractSeries *> seriesData = chart->series();
    foreach (QAbstractSeries * seriesEntity, seriesData){
        chart->removeSeries(seriesEntity);
        delete seriesEntity;
    }
    QList<QAbstractAxis *> axes = chart->axes();
    foreach (QAbstractAxis * axis, axes) {
        chart->removeAxis(axis);
        delete axis;
    }

    QValueAxis * axisY = new QValueAxis();
    QValueAxis * axisX = new QValueAxis();
    QLineSeries * series = new QLineSeries();

    chart->addSeries(series);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->legend()->hide();
    qChartView->setChart(chart);
    ui->graphLayout->addWidget(qChartView);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    return new ChangeRegisterThreadData(series, signalCoefficientData, axisX, axisY);
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

void MainWindow::on_signal_dialog_accept(SignalCoefficientData * signalCoefficientData){

    delete this->chartDataList->at(0)->getSignalCoefficientData();
    this->chartDataList->at(0)->setSignalCoefficientData(signalCoefficientData);
}

void MainWindow::on_signalAction_triggered()
{
    SignalDialog * dialog = new SignalDialog(this, chartDataList);
    connect(dialog, &SignalDialog::getFilledData, this, &MainWindow::on_signal_dialog_accept);
    dialog->exec();
}

