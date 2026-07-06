#pragma once

#include "Strategy.h"

class SMA : public Strategy
{
private:
    int period; //period to look back on

    double calculateMovingAverage(const std::vector<Candle>& candles,int currentIndex) const;

public:
    SMA(int period); 

    Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};