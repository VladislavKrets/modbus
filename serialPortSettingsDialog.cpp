#include "serialPortSettingsDialog.h"
#include "ui_serialPortSettingsDialog.h"
#include <QSettings>
#include <QPushButton>
#include <QSerialPortInfo>


SerialPortSettingsDialog::SerialPortSettingsDialog(QWidget *parent, PortInfo * portInfo) : QDialog(parent), ui(new Ui::SerialPortSettingsDialog)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //заполняем комбобоксы вариантами выбора

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    ui->nameComboBox->addItem("", "");
    foreach (QSerialPortInfo port, ports) {
        ui->nameComboBox->addItem(port.portName(), port.systemLocation());
    }

    QString str="";

    ui->baudrateCombo->addItem(tr("1200"), Baud1200);
    ui->baudrateCombo->addItem(tr("2400"), Baud2400);
    ui->baudrateCombo->addItem(tr("4800"), Baud4800);
    ui->baudrateCombo->addItem(tr("9600"), Baud9600);
    ui->baudrateCombo->addItem(tr("19200"), Baud19200);
    ui->baudrateCombo->addItem(tr("38400"), Baud38400);
    ui->baudrateCombo->addItem(tr("57600"), Baud57600);
    ui->baudrateCombo->addItem(tr("115200"), Baud115200);

    ui->dataBitsCombo->addItem(tr("5"), Data5);
    ui->dataBitsCombo->addItem(tr("6"), Data6);
    ui->dataBitsCombo->addItem(tr("7"), Data7);
    ui->dataBitsCombo->addItem(tr("8"), Data8);

    ui->parityCombo->addItem(tr("Нет"),  NoParity);
    ui->parityCombo->addItem(tr("ODD"),  OddParity);
    ui->parityCombo->addItem(tr("EVEN"), EvenParity);
    ui->parityCombo->addItem(tr("MARK"), MarkParity);
    ui->parityCombo->addItem(tr("SPACE"),SpaceParity);

    ui->flcntrlCombo->addItem(tr("Нет"), NoFlowControl);
    ui->flcntrlCombo->addItem(tr("Аппаратный"), HardwareControl);
    ui->flcntrlCombo->addItem(tr("Программный"), SoftwareControl);

    ui->stopBitsCombo->addItem(tr("1"), OneStop);
    ui->stopBitsCombo->addItem(tr("1,5"), OneAndHalfStop);
    ui->stopBitsCombo->addItem(tr("2"), TwoStop);

    if (portInfo) {
        int index = ui->nameComboBox->findData(portInfo->getName());
        if (index != -1) ui->nameComboBox->setCurrentIndex(index);
        else {
            ui->nameComboBox->setCurrentIndex(0);
            ui->nameComboBox->setCurrentText(portInfo->getName());
        }
        ui->baudrateCombo->setCurrentIndex(ui->baudrateCombo->findData(portInfo->getBaudRate()));
        ui->dataBitsCombo->setCurrentIndex(ui->dataBitsCombo->findData(portInfo->getDataBits()));
        ui->parityCombo->setCurrentIndex(ui->parityCombo->findData(portInfo->getParityControl()));
        ui->flcntrlCombo->setCurrentIndex(ui->flcntrlCombo->findData(portInfo->getFlowControl()));
        ui->stopBitsCombo->setCurrentIndex(ui->stopBitsCombo->findData(portInfo->getStopBitsCount()));
    }

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(okAccept()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
}

void SerialPortSettingsDialog::okAccept(){
    QString name = ui->nameComboBox->currentData().toString() == "" ? ui->nameComboBox->currentText() : ui->nameComboBox->currentData().toString();
    QString baudRate = ui->baudrateCombo->currentData().toString();
    QString dataBits = ui->dataBitsCombo->currentData().toString();
    QString parity = ui->parityCombo->currentData().toString();
    QString flowControl = ui->flcntrlCombo->currentData().toString();
    QString stopBits = ui->stopBitsCombo->currentData().toString();
    PortInfo * portInfo = new PortInfo(name, baudRate, dataBits, parity, flowControl, stopBits);
    emit getFilledData(portInfo);
    accept();
}

SerialPortSettingsDialog::~SerialPortSettingsDialog()
{
    delete ui;
}
