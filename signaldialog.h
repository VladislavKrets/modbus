#ifndef SIGNALDIALOG_H
#define SIGNALDIALOG_H

#include <QDialog>
#include "signalcoefficientdata.h"
#include "chartdata.h"

namespace Ui {
class SignalDialog;
}

class SignalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignalDialog(QWidget *parent = nullptr, QList<ChartData *> * chartDataList = nullptr);
    ~SignalDialog();
signals:
    void getFilledData(SignalCoefficientData * signalCoefficientData);
public slots:
    void okAccept();
    void addSignal();
    void deleteSignal();
private:
    Ui::SignalDialog *ui;
    QList<ChartData *> * chartDataList;
};

#endif // SIGNALDIALOG_H
