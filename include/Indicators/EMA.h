// Exponential Moving Avearage 

/*
    Unlike SMA and MA, this indicator gives more weight to recent data points. 
    This is to capatlize on the most current market trends and movement.
*/


#pragma once

#include "Strategy.h"

class EMA : public Strategy
{
    private:
        int period;

        double alpha; // smoothing factor

        double calculateSMA(const std::vector<Candle>& candles,int currentIndex) const;

        double calculateSMA(const std::vector<double>& values,int currentIndex) const;

    public:
        EMA(int period);

        Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;

        double calculateEMA(const std::vector<Candle>& candles,int currentIndex) const;

        double calculateEMA(const std::vector<double>& values,int currentIndex) const;

};