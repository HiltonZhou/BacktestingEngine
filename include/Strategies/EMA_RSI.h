// Strategie involving EMA and RSI indicators

#include "Strategy.h"
#include "Indicators/EMA.h"
#include "Indicators/RSI.h"

class EMA_RSI: public Strategy
{
    private:
    
    public :
        EMA_RSI();

        Signal generateSignal(const std::vector<Candle>& candles,int currentIndex) const override;
};