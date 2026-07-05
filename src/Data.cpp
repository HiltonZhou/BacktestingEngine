#include "Data.h"

#include <fstream>
#include <sstream>
#include <iostream>

//constructor
MarketData::MarketData(std::string symbol, std::string timeframe){
    this->symbol = symbol;
    this->timeframe = timeframe;
}


bool MarketData::readData(const std::string& filename){
    std::fstream file(filename);

    if(!file.is_open()){
        return false;
    }

    std::string line;

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        Candle c;

        std::getline(ss, c.date, ',');

        std::getline(ss, value, ',');
        c.open = std::stod(value);

        std::getline(ss, value, ',');
        c.high = std::stod(value);

        std::getline(ss, value, ',');
        c.low = std::stod(value);

        std::getline(ss, value, ',');
        c.close = std::stod(value);

        std::getline(ss, value, ',');
        c.volume = std::stod(value);

        candles.push_back(c);
    }

    return true;
}

const std::vector<Candle>& MarketData::getCandles() const {return candles;}

std::string MarketData::getSymbol() const {return symbol;}

std::string MarketData::getTimeframe() const {return timeframe;}

int MarketData::size() const {return candles.size();}










