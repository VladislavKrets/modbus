#include "chartdata.h"

ChartData::ChartData(QChartView * qChartView, SignalCoefficientData * signalCoefficientData, ChangeRegister * changeRegister)
{
    this->qChartView = qChartView;
    this->signalCoefficientData = signalCoefficientData;
    this->changeRegister = changeRegister;
}

ChartData::~ChartData(){
    delete qChartView;
    delete signalCoefficientData;
    delete changeRegister;
}

QChartView * ChartData::getQChartView(){
    return qChartView;
}

SignalCoefficientData * ChartData::getSignalCoefficientData(){
    return signalCoefficientData;
}

ChangeRegister * ChartData::getChangeRegister(){
    return changeRegister;
}

void ChartData::setChangeRegister(ChangeRegister *changeRegister){
    this->changeRegister = changeRegister;
}

void ChartData::setSignalCoefficientData(SignalCoefficientData *signalCoefficientData){
    this->signalCoefficientData = signalCoefficientData;
}
