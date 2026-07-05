#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include "Candle.h"


class MarketData{

    private:
        std::string symbol; //type of exchange
        std::string timeframe;
        std::vector<Candle> candles;

    public:
        MarketData(std::string symbol, std::string timeframe);

        bool readData(const std::string& filename);

        const std::vector<Candle>& getCandles() const;

        std::string getSymbol() const;
        std::string getTimeframe() const;

        int size() const;
};  

#endif
 