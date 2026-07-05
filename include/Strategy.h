#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <vector>
#include "Signal.h"
#include "Candle.h"

class Strategy{
    public:
        virtual ~Strategy() = default;
        
        virtual Signal generateSignal(const std::vector<Candle>& candles, int currentIndex) const = 0;
};

#endif