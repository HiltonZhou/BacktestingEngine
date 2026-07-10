#include "Strategies/EMA_RSI.h"

EMA_RSI::EMA_RSI(){}

Signal EMA_RSI::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{
    EMA ema1(30);
    EMA ema2(10);

    RSI rsi;

    double ema30 = ema1.calculateEMA(candles,currentIndex);
    double ema10 = ema2.calculateEMA(candles,currentIndex);

    double RSI = rsi.calculateRSI(candles, currentIndex);

    if(ema10 > ema30 && RSI > 50){
        return Signal::BUY;
    }else if(ema10 < ema30 && RSI < 50){
        return Signal::SELL;
    }

    return Signal::HOLD;
}