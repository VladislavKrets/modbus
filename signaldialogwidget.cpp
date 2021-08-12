#include "signaldialogwidget.h"
#include <QModbusDataUnit>

SignalDialogWidget::SignalDialogWidget(QWidget *parent) : QWidget(parent)
{
    verticalLayout = new QVBoxLayout();
    verticalLayout->setContentsMargins(10, 10, 10, 10);
    functionLabel = new QLabel();

    verticalLayout->addWidget(functionLabel);

    functionComboBox = new QComboBox();

    verticalLayout->addWidget(functionComboBox);

    formLayout = new QFormLayout();
    label = new QLabel();

    formLayout->setWidget(2, QFormLayout::LabelRole, label);

    Acoeff = new QLineEdit();

    formLayout->setWidget(2, QFormLayout::FieldRole, Acoeff);

    label_2 = new QLabel();

    formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

    Bcoeff = new QLineEdit();

    formLayout->setWidget(3, QFormLayout::FieldRole, Bcoeff);

    label_3 = new QLabel();

    formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

    Ccoeff = new QLineEdit();

    formLayout->setWidget(4, QFormLayout::FieldRole, Ccoeff);

    label_4 = new QLabel();

    formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

    Dcoeff = new QLineEdit();

    formLayout->setWidget(5, QFormLayout::FieldRole, Dcoeff);

    registerNumber = new QLineEdit();

    formLayout->setWidget(0, QFormLayout::FieldRole, registerNumber);

    label_5 = new QLabel();

    formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

    registerType = new QLabel();

    formLayout->setWidget(1, QFormLayout::LabelRole, registerType);

    registerTypeCombobox = new QComboBox();

    formLayout->setWidget(1, QFormLayout::FieldRole, registerTypeCombobox);


    verticalLayout->addLayout(formLayout);

    functionLabel->setText("A*sin(B*x+C)+D");
    label->setText("A");
    label_2->setText("B");
    label_3->setText("C");
    label_4->setText("D");
    label_5->setText("\320\240\320\265\320\263\320\270\321\201\321\202\321\200");
    registerType->setText("\320\242\320\270\320\277");

    functionComboBox->addItem("Синусоида");
    functionComboBox->addItem("Меандр");

    registerTypeCombobox->addItem("Coils", QModbusDataUnit::Coils);
    registerTypeCombobox->addItem("Discrete Inputs", QModbusDataUnit::DiscreteInputs);
    registerTypeCombobox->addItem("Input Registers", QModbusDataUnit::InputRegisters);
    registerTypeCombobox->addItem("Holding Registers", QModbusDataUnit::HoldingRegisters);

    registerNumber->setValidator(new QIntValidator(1, 10000));

    Acoeff->setValidator(new QDoubleValidator(this));
    Bcoeff->setValidator(new QDoubleValidator(this));
    Ccoeff->setValidator(new QDoubleValidator(this));
    Dcoeff->setValidator(new QDoubleValidator(this));

    setLayout(verticalLayout);
    connect(functionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onSignalChanged(int)));
}

void SignalDialogWidget::onSignalChanged(int index){
    QString function = functionComboBox->currentText();
    if (function == "Синусоида") functionLabel->setText("A*sin(B*x+C)+D");
    else functionLabel->setText("sgn(A*sin(B*x+C)+D)");
}
