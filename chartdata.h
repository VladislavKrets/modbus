#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QChartView>
#include "signalcoefficientdata.h"
#include "changeregister.h"

class ChartData
{
public:
    ChartData(QChartView * qChartView, SignalCoefficientData * signalCoefficientData, ChangeRegister * changeRegister = nullptr);
    ~ChartData();
    QChartView * getQChartView();
    SignalCoefficientData * getSignalCoefficientData();
    ChangeRegister * getChangeRegister();
    void setChangeRegister(ChangeRegister * changeRegister);
    void setSignalCoefficientData(SignalCoefficientData * signalCoefficientData);
private:
    QChartView * qChartView;
    SignalCoefficientData * signalCoefficientData;
    ChangeRegister * changeRegister;
};

#endif // CHARTDATA_H
