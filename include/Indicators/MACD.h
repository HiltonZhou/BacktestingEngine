//Moving average convergence/divergence

#pragma once
#include "Strategy.h"
#include "EMA.h"

class MACD: public EMA{

    private:
    public:
        MACD();

        double calcMACD(const std::vector<Candle>& candles,int currentIndex) const;
};