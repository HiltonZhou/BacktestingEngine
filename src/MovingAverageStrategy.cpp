#include "MovingAverageStrategy.h"

MovingAverageStrategy::MovingAverageStrategy(int amtCandle)
{
    this->amtCandle = amtCandle;
}

Signal MovingAverageStrategy::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{   
    double MA = calculateMovingAverage(candles, currentIndex);

    double currentClosePrice = candles[currentIndex].close;

    if(currentIndex < amtCandle){
        return Signal::HOLD;
    }

    if(currentClosePrice > MA){return Signal::BUY;}
    
    if(currentClosePrice < MA){return Signal::SELL;}

    return Signal::HOLD;
}

double MovingAverageStrategy::calculateMovingAverage(const std::vector<Candle>& candles,int currentIndex) const
{
    double sum = 0;
    for(int i = currentIndex - amtCandle; i < currentIndex; i++){
        sum += candles[i].close;
    }

    return sum/amtCandle;
}