#include <iostream>
#include "Data.h"
#include "SMA.h"
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

    SMA strategy(200);

    Backtest bt(strategy, candles);

    const double balance = 1000.00;

    bt.setBalance(balance);
    
    bt.setCommision(0.001);

    bt.run();

    bt.Stats();

    return 0;
}
