#include <iostream>
#include <vector>

#include "Data.h"
#include "Indicators/SMA.h"
#include "Indicators/EMA.h"
#include "Backtest.h"


void runTest(Strategy &strat, const std::vector<Candle>& candles, const double balance, const double commision)
{
    Backtest bt(strat, candles);

    bt.setBalance(balance);
    
    bt.setCommision(commision);

    bt.run();

    bt.Stats();
}


int main()
{
    MarketData BTC("BTC-USD","1d");

    bool load = BTC.readData("../data/BTC-USD.csv");

    if(!load){
        std::cerr << "file path is wrong" << std::endl;
    }

    const auto& candles = BTC.getCandles();

    // -------------------------------------------------
    const double balance = 1000.00;

    const int period = 200;

    const double commision = 0.001;

    // -------------------------------------------------
    SMA SMA_strategy(period);

    runTest(SMA_strategy,candles,balance,commision);

    EMA EMA_strategy(period);

    runTest(EMA_strategy,candles,balance,commision);

    return 0;
}
