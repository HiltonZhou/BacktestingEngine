#include <iostream>
#include "Data.h"
#include "MovingAverageStrategy.h"
#include "Backtest.h"

int main()
{
    MarketData BTC("BTC-USD","1d");

    bool load = BTC.readData("../data/BTC-USD.csv");

    if(!load){
        std::cerr << "file path is wrong" << std::endl;
    }

    const auto& candles = BTC.getCandles();

    // -------------------------------------------------

    MovingAverageStrategy strategy(200);

    Backtest bt(strategy, candles);

    const double balance = 10000;

    bt.setBalance(balance);

    bt.run();

    bt.Stats();

    return 0;
}