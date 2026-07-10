#include "Indicators/SMA.h"

SMA::SMA(int period)
{
    this->period = period;
}

Signal SMA::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{   
    if(currentIndex < period){
        return Signal::HOLD;
    }
    
    double MA = calculateSMA(candles, currentIndex);

    double currentClosePrice = candles[currentIndex].close;

    if(currentClosePrice > MA){return Signal::BUY;}
    
    if(currentClosePrice < MA){return Signal::SELL;}

    return Signal::HOLD;
}

double SMA::calculateSMA(const std::vector<Candle>& candles,int currentIndex) const
{
    double sum = 0.0;
    for(int i = currentIndex - period + 1; i <= currentIndex; i++){
        sum += candles[i].close;
    }

    return sum/period;
}

double SMA::calculateSMA(const std::vector<double>& values,int currentIndex) const
{
    double sum = 0.0;

    for(int i = currentIndex - period + 1; i <= currentIndex; i++)
    {
        sum += values[i];
    }

    return sum / period;
}