#pragma once

#include "Strategy.h"

class MovingAverageStrategy : public Strategy
{
private:
    int amtCandle; //amount to look back on

    double calculateMovingAverage(const std::vector<Candle>& candles,int currentIndex) const;

public:
    MovingAverageStrategy(int amtCandle); 

    Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};