//Moving average convergence/divergence

/*

Moving average convergence/divergence (MACD) is a indicator that helps investors 
identify price trends, measure trend momentum, and identify entry points for buying 
or selling a security

*/

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