// Simple Moving Average

#pragma once

#include "Strategy.h"

class SMA : public Strategy
{
private:
    int period; //period to look back on

    double calculateSMA(const std::vector<Candle>& candles,int currentIndex) const;

public:
    SMA(int period); 

    Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;

    double calculateSMA(const std::vector<double>& values,int currentIndex) const;
};  