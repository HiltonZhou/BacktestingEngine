#include "RSI.h"

RSI::RSI()
{
    period = 14;
}


double RSI::calculateRSI(const std::vector<Candle>& candles, int currentIndex) const
{
    double gain = 0;
    double loss = 0;

    for(size_t i = currentIndex - period; i <= currentIndex; i++){
        double difference = candles[i].close - candles[i-1].close;

        if(difference > 0){
            gain++;
        }else if(difference < 0){
            loss++;
        }

    }

    double rs = gain/loss;

    return 100 - (100/(1+rs));
}