// Relative strenght index

#pragma once

#include "Strategy.h"

class RSI : public Strategy
{
    private:
        int period;

    public:
        RSI();

        Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;

        double calculateRSI(const std::vector<Candle>& candles, int currentIndex) const;
};