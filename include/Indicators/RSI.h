// Relative strenght index

#pragma once

#include "Strategy.h"

class RSI : public Strategy
{
    private:
        int period;
        
        double calculateRSI(const std::vector<Candle>& candles, int currentIndex) const;

    public:
        RSI();

        Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};