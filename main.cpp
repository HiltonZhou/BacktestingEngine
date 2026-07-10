#include <iostream>
#include <vector>

#include "Data.h"
#include "Backtest.h"

//Indicators
#include "Indicators/SMA.h"
#include "Indicators/EMA.h"
#include "Indicators/RSI.h"
#include "Indicators/MACD.h"
#include "Indicators/Stoch.h"

//Strategies
#include "Strategies/EMA_RSI.h"

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

    EMA_RSI ema_rsi;

    runTest(ema_rsi,candles,balance,commision);

    return 0;
}
