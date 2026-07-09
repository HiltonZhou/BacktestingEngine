#include "Indicators/MACD.h"

MACD::MACD()
{

}

double MACD::calcMACD(const std::vector<Candle>& candles,int currentIndex) const
{      
    EMA short_term(12);
    EMA long_term(26);

    double ema_12 = short_term.calculateEMA(candles, currentIndex);
    double ema_26 = long_term.calculateEMA(candles, currentIndex);

    return ema_12 - ema_26;
}

Signal MACD::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{
    double macd_line = calcMACD(candles,currentIndex);

    EMA SL(9); // usually a 9 period as signal line

    double signal_line = SL.calculateEMA(candles,currentIndex);

    if(macd_line > signal_line){
        return Signal::BUY;
    }else if(macd_line < signal_line){
        return Signal::SELL;
    }

    return Signal::HOLD;
}


