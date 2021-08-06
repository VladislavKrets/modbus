#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QDialogButtonBox>
#include <QPushButton>

DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    for(int i=1; i<=247; i++){
        ui->comboNumbesServers->addItem(QString::number(i));
    }
    ui->label->setBuddy(ui->comboNumbesServers);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &DialogSettings::onAcceptSlot);
}

DialogSettings::~DialogSettings()
{
    delete ui;
}


void DialogSettings::onAcceptSlot(){
    emit onAcceptSignal(ui->comboNumbesServers->currentText().toUInt());
    accept();
}
