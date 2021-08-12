#ifndef CHANGEREGISTERTHREADDATA_H
#define CHANGEREGISTERTHREADDATA_H

#include <QtCharts>
#include "signalcoefficientdata.h"

struct PrevValues {
    qreal prevMinX = -0.1;
    qreal prevMaxX = 5.1;
    qreal prevMaxY = 1.1;
    qreal prevMinY = -1.1;
    qreal delta = 0.1;
};

class ChangeRegisterThreadData
{
public:
    ChangeRegisterThreadData(QLineSeries * series,
                             SignalCoefficientData * data, QValueAxis *axisX, QValueAxis *axisY);
    ~ChangeRegisterThreadData();
    QLineSeries * getSeries();
    SignalCoefficientData * getData();
    QValueAxis * getAxisX();
    QValueAxis * getAxisY();
    PrevValues * getPrevValues();
private:
    QLineSeries * series;
    SignalCoefficientData * data;
    QValueAxis * axisX;
    QValueAxis * axisY;
    PrevValues * prevValues = new PrevValues();
};


#endif // CHANGEREGISTERTHREADDATA_H
