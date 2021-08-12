#ifndef SIGNALDIALOGWIDGET_H
#define SIGNALDIALOGWIDGET_H

#include <QWidget>
#include <QtWidgets>

class SignalDialogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignalDialogWidget(QWidget *parent = nullptr);
    QVBoxLayout *verticalLayout;
    QLabel *functionLabel;
    QComboBox *functionComboBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *Acoeff;
    QLabel *label_2;
    QLineEdit *Bcoeff;
    QLabel *label_3;
    QLineEdit *Ccoeff;
    QLabel *label_4;
    QLineEdit *Dcoeff;
    QLineEdit *registerNumber;
    QLabel *label_5;
    QLabel *registerType;
    QComboBox *registerTypeCombobox;
public slots:
    void onSignalChanged(int index);
signals:

};

#endif // SIGNALDIALOGWIDGET_H
