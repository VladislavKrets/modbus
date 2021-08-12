#include "changeregisterthreaddata.h"

ChangeRegisterThreadData::ChangeRegisterThreadData(QLineSeries * series,
                                                   SignalCoefficientData * data, QValueAxis *axisX, QValueAxis *axisY)
{
    this->series = series;
    this->data = data;
    this->axisX = axisX;
    this->axisY = axisY;
}

ChangeRegisterThreadData::~ChangeRegisterThreadData(){
    delete prevValues;
    delete data;
    delete series;
    delete axisX;
    delete axisY;
}

QLineSeries * ChangeRegisterThreadData::getSeries(){
    return series;
}

SignalCoefficientData * ChangeRegisterThreadData::getData(){
    return data;
}

QValueAxis * ChangeRegisterThreadData::getAxisX(){
    return axisX;
}

QValueAxis * ChangeRegisterThreadData::getAxisY(){
    return axisY;
}

PrevValues * ChangeRegisterThreadData::getPrevValues(){
    return prevValues;
}
