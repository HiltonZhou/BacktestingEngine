//Moving average convergence/divergence

#pragma once
#include "Strategy.h"
#include "EMA.h"

class MACD: public Strategy{

    private:
        double calcMACD(const std::vector<Candle>& candles,int currentIndex) const;

    public:
        MACD();

        Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};