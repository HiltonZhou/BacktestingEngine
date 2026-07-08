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
    
    double MA = calculateMovingAverage(candles, currentIndex);

    double currentClosePrice = candles[currentIndex].close;

    if(currentClosePrice > MA){return Signal::BUY;}
    
    if(currentClosePrice < MA){return Signal::SELL;}

    return Signal::HOLD;
}

double SMA::calculateMovingAverage(const std::vector<Candle>& candles,int currentIndex) const
{
    double sum = 0;
    for(int i = currentIndex - period; i < currentIndex; i++){
        sum += candles[i].close;
    }

    return sum/period;
}