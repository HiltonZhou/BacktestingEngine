// Relative strenght index

/*
    RSI is a momemtum indicator to measure speed and magnitude of a securit's recent price 
    changes to deect overbough or oversold conditions in the price of that security
*/

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