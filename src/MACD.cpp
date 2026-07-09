#include "MACD.h"

MACD::MACD()
{

}

double MACD::calcMACD(const std::vector<Candle>& candles,int currentIndex) const
{      
    EMA x(12);
    EMA y(26);

    double period_12 = x.calculateEMA(candles, currentIndex);

}