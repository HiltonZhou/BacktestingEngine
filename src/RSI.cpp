#include "Indicators/RSI.h"

RSI::RSI()
{
    period = 14;
}


double RSI::calculateRSI(const std::vector<Candle>& candles, int currentIndex) const
{
    double Avg_gain = 0;
    double Avg_loss = 0;

    for(size_t i = currentIndex - period + 1; i <= currentIndex; i++){ 
        double difference = candles[i].close - candles[i-1].close;

        if(difference > 0){
            Avg_gain += difference;
        }else if(difference < 0){
            Avg_loss += std::abs(difference);
        }
    }

    double rs = Avg_gain/Avg_loss;

    return 100 - (100/(1+rs));
}

Signal RSI::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{
    if(currentIndex < period){
        return Signal::HOLD;
    }

    double RSI_value = calculateRSI(candles, currentIndex);

    std::cout << candles[currentIndex].date
          << " RSI: " << RSI_value << '\n';

    if(RSI_value < 30){             //security could be oversold or undervalued potential rebound
        return Signal::BUY;

    }else if(RSI_value > 50){       // 50 better than 70 for btc security could be overbought or overvalued potential drop
        return Signal::SELL;
    }

    return Signal::HOLD;
}