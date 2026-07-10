#include "Indicators/Stoch.h"
#include "Indicators/SMA.h"
#include <cmath>
#include <algorithm>
#include <iostream>


Stoch::Stoch(){

}

double Stoch::calc_percent_K(const std::vector<Candle>& candles,int currentIndex) const
{
    double C = candles[currentIndex].close; //recent close price
    
    double H14 = candles[currentIndex - period + 1].high;
    double L14 = candles[currentIndex - period + 1].low;

    for(size_t i = currentIndex - period + 1; i < currentIndex; i++)
    {
        H14 = std::max(H14, candles[i].high);
        L14 = std::min(L14, candles[i].low);
    }

     
    return  ((C-L14)/(H14-L14)) * 100.0;
}

Signal Stoch::generateSignal(const std::vector<Candle>& candles,int currentIndex) const
{
    if(currentIndex < period - 1){
        return Signal::HOLD;
    }

    std::vector<double> k_val;

    for(size_t i = period - 1; i <= currentIndex; i++){
        k_val.push_back(calc_percent_K(candles,i));
    }

    double percent_K =  calc_percent_K(candles, currentIndex);

    SMA sma(3);  //period of 3 for %D line
    
    double percent_D = sma.calculateSMA(k_val, k_val.size() - 1);
    
    if(percent_K < 20 && percent_K > percent_D){
        return Signal::BUY;
    }else if(percent_K > 80 && percent_K < percent_D){
        return Signal::SELL;
    }

    return Signal::HOLD;
}


