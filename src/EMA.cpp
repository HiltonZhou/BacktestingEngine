#include "Indicators/EMA.h"

EMA::EMA(int period)
{   
    this->period = period;

    alpha = 2.0 / (period + 1);
}

double EMA::calculateSMA(const std::vector<Candle>& candles,int currentIndex) const
{
    double sum = 0;

    for(int i = currentIndex - period; i < currentIndex; i++){
        sum += candles[i].close;
    }

    return sum/period;
}

double EMA::calculateEMA(const std::vector<Candle>& candles, int currentIndex) const
{   
    //base case
    if(currentIndex == period)
    {
        return calculateSMA(candles, period);
    }

    //recursive
    return alpha * candles[currentIndex].close + (1 - alpha) * calculateEMA(candles, currentIndex - 1);
}

Signal EMA::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{       
    if(currentIndex < period){
        return Signal::HOLD;
    }

    double MA = calculateEMA(candles, currentIndex);

    double currentClosePrice = candles[currentIndex].close;

    if(currentClosePrice > MA){return Signal::BUY;}
    
    if(currentClosePrice < MA){return Signal::SELL;}

    return Signal::HOLD;
}

