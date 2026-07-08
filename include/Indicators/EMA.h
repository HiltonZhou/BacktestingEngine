// Exponential Moving Avearage 
#pragma once

#include "Strategy.h"

class EMA : public Strategy
{
    private:
        int period;

        double alpha; // smoothing factor

        int track = 0;

        double calculateSMA(const std::vector<Candle>& candles,int currentIndex) const;

        double calculateEMA(const std::vector<Candle>& candles,int currentIndex) const;

    public:
        EMA(int period);

};