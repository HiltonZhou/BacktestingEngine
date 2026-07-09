#ifndef BACKTEST_H
#define BACKTEST_H

#include <vector>
#include "Strategy.h"

class Backtest{

    private:
        const Strategy& strategy;

        const std::vector<Candle>& candles;

        bool position = false;

        double initialBalance = 0.0;

        double balance = 0.0;

        double finalBalance = 0.0;

        double quantity = 0.0;

        int totalTrades = 0;

        double buyPrice = 0.0;

        double sellPrice = 0.0;

        int wins = 0;

        int losses = 0;

        double commision = 0.0;

        double commisionBalance = 0.0;

        double slippage = 0.005; //slippage amount per trade 0.05%

        double profit = 0.0;

        double currentPortfolioValue = 0.0;

        double highestPortfolioValue = 0.0;

        double maximumDrawdown = 0.0;

        double riskFreeRate = 0.0455/365.0; // candle are in days (365 trading days) 4.55% is 10 year treasuary rate

        std::vector<double> portfolioValue;

        std::vector<double> returns;
        

    public:
        Backtest(const Strategy& strategy, const std::vector<Candle>& candles);

        void run();

        void buy(const Candle& candle);

        void sell(const Candle& candle);

        void setBalance(const double cash);

        void Stats(); 

        void setCommision(double commision);  

        double executeCommision(double tradeValue); 

        void MaximumDrawdown(double cpv);

        double calcAvgReturns();

        double calcVolatility();

        double SharpeRatio();
};  

#endif