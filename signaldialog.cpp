#include "signaldialog.h"
#include "ui_signaldialog.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QPushButton>
#include <QTextStream>
#include <QChart>
#include "signaldialogwidget.h"
#include <QTextStream>

SignalDialog::SignalDialog(QWidget *parent, QList<ChartData *> * chartDataList) :
    QDialog(parent),
    ui(new Ui::SignalDialog)
{
    ui->setupUi(this);
    this->chartDataList = chartDataList;
    SignalDialogWidget * signalDialogWidget;
    for (int i = 0; chartDataList && i < chartDataList->size(); i++) {
        signalDialogWidget = new SignalDialogWidget(this);
        signalDialogWidget->functionComboBox->setCurrentIndex(signalDialogWidget->functionComboBox->findText(chartDataList->at(i)->getSignalCoefficientData()->getFunction()));
        signalDialogWidget->registerTypeCombobox->setCurrentIndex(signalDialogWidget->registerTypeCombobox->findData(chartDataList->at(i)->getSignalCoefficientData()->getType()));
        signalDialogWidget->registerNumber->setText(QString::number(chartDataList->at(i)->getSignalCoefficientData()->getRegisterNumber() + 1));
        signalDialogWidget->Acoeff->setText(QString::number(chartDataList->at(i)->getSignalCoefficientData()->getA()));
        signalDialogWidget->Bcoeff->setText(QString::number(chartDataList->at(i)->getSignalCoefficientData()->getB()));
        signalDialogWidget->Ccoeff->setText(QString::number(chartDataList->at(i)->getSignalCoefficientData()->getC()));
        signalDialogWidget->Dcoeff->setText(QString::number(chartDataList->at(i)->getSignalCoefficientData()->getD()));
        if (chartDataList->at(i)->getSignalCoefficientData()->getFunction() == "Синусоида") signalDialogWidget->functionLabel->setText("A*sin(B*x+C)+D");
        else signalDialogWidget->functionLabel->setText("sgn(A*sin(B*x+C)+D)");
        ui->signalTab->addTab(signalDialogWidget, QString("Сигнал %1").arg(i + 1));
    }
    QToolButton * tb = new QToolButton();
    tb->setStyleSheet("border:none;background:none");
    tb->setText("+");
    tb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    ui->signalTab->addTab(new QWidget(), QString());
    ui->signalTab->setTabEnabled(ui->signalTab->count() - 1, false);
    ui->signalTab->tabBar()->setTabButton(ui->signalTab->count() - 1, QTabBar::RightSide, tb);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(okAccept()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    connect(tb, &QToolButton::clicked, this, &SignalDialog::addSignal);
}

void SignalDialog::addSignal(){
    QChartView * chartView = new QChartView((QWidget *) parent());
    chartView->setVisible(false);
    SignalCoefficientData * signalCoefficientData = new SignalCoefficientData("Синусоида", 1, QModbusDataUnit::InputRegisters, 1, 1, 0, 0);
    chartDataList->append(new ChartData(chartView, signalCoefficientData));
    SignalDialogWidget * signalDialogWidget;
    signalDialogWidget = new SignalDialogWidget(this);
    signalDialogWidget->functionComboBox->setCurrentIndex(signalDialogWidget->functionComboBox->findText(signalCoefficientData->getFunction()));
    signalDialogWidget->registerTypeCombobox->setCurrentIndex(signalDialogWidget->registerTypeCombobox->findData(signalCoefficientData->getType()));
    signalDialogWidget->registerNumber->setText(QString::number(signalCoefficientData->getRegisterNumber() + 1));
    signalDialogWidget->Acoeff->setText(QString::number(signalCoefficientData->getA()));
    signalDialogWidget->Bcoeff->setText(QString::number(signalCoefficientData->getB()));
    signalDialogWidget->Ccoeff->setText(QString::number(signalCoefficientData->getC()));
    signalDialogWidget->Dcoeff->setText(QString::number(signalCoefficientData->getD()));
    if (signalCoefficientData->getFunction() == "Синусоида") signalDialogWidget->functionLabel->setText("A*sin(B*x+C)+D");
    else signalDialogWidget->functionLabel->setText("sgn(A*sin(B*x+C)+D)");
    ui->signalTab->insertTab(ui->signalTab->count() - 1, signalDialogWidget, QString("Сигнал %1").arg(chartDataList->size()));
}

void SignalDialog::okAccept(){
    if (chartDataList) {
        SignalDialogWidget * widget;
        SignalCoefficientData * data;
        QWidget * plainWidget;
        for (int i = 0; i < ui->signalTab->count() - 1; i++){
            plainWidget = ui->signalTab->widget(i);
            widget = (SignalDialogWidget *) plainWidget;
            qreal A = widget->Acoeff->text().toDouble();
            qreal B = widget->Bcoeff->text().toDouble();
            qreal C = widget->Ccoeff->text().toDouble();
            qreal D = widget->Dcoeff->text().toDouble();
            qint32 registerNumber = widget->registerNumber->text().toInt() - 1;
            QModbusDataUnit::RegisterType type = widget->registerTypeCombobox->currentData().value<QModbusDataUnit::RegisterType>();
            QString function = widget->functionComboBox->currentText();
            data = chartDataList->at(i)->getSignalCoefficientData();
            chartDataList->at(i)->setSignalCoefficientData(new SignalCoefficientData(function, registerNumber, type, A, B, C, D));
        }
    }
    //emit getFilledData(chartDataList);
    accept();
}

SignalDialog::~SignalDialog()
{
    delete ui;
}
