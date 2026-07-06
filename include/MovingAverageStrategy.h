#pragma once

#include "Strategy.h"

class MovingAverageStrategy : public Strategy
{
private:
    int period; //period to look back on

    double calculateMovingAverage(const std::vector<Candle>& candles,int currentIndex) const;

public:
    MovingAverageStrategy(int period); 

    Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};