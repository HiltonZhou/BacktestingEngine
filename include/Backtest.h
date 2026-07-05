#ifndef BACKTEST_H
#define BACKTEST_H

#include <vector>
#include "Strategy.h"

class Backtest{

    private:
        const Strategy& strategy;

        const std::vector<Candle>& candles;

        bool position = false;

        double initialBalance = 0;

        double balance = 0;

        double finalBalance = 0;

        double quantity = 0;

        


    public:
        Backtest(const Strategy& strategy, const std::vector<Candle>& candles);

        void run();

        void buy(const Candle& candle);

        void sell(const Candle& candle);

        void setBalance(const double cash);
        
};  

#endif