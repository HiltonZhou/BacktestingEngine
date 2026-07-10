// Stochastic Oscillator

#pragma once

#include "Strategy.h"

class Stoch: public Strategy{

    private:

        int period = 14;

    public: 

        Stoch();

        double calc_percent_K(const std::vector<Candle>& candles,int currentIndex) const;

        Signal generateSignal(const std::vector<Candle>& candles, int currentIndex) const override;
};