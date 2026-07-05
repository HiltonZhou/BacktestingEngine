#include "Backtest.h"
#include <iostream>
#include <cmath>

Backtest::Backtest(const Strategy& strategy, const std::vector<Candle>& candles): strategy(strategy), candles(candles)
{

}

void Backtest::setBalance(double cashAmt)
{
    this->balance = cashAmt;
    this->initialBalance = cashAmt;
}

void Backtest::run()
{
    std::cout << "Running Backtest..." << std::endl;
    std::cout << "Starting Balance..." << std::endl;

    for(size_t i = 0; i < candles.size(); i++){
        Signal signal = strategy.generateSignal(candles,i);

        if( signal == Signal::BUY && !position){
            buy(candles[i]);
        }else if(signal == Signal::SELL && position){
            sell(candles[i]);
        }
    }

    //final run check if you still got btc
    if(position){
        sell(candles.back());
    }

    finalBalance = balance;
}

void Backtest::buy(const Candle& candles)
{
    position = true;
    quantity = balance/candles.close;
    balance = 0;

    std::cout << "BUY: " << candles.date << " AT " << candles.close << std::endl;
}

void Backtest::sell(const Candle& candles)
{
    position = false;
    balance = quantity * candles.close;
    quantity = 0;

    std::cout << "SELL: " << candles.date << " AT " << candles.close << std::endl;
}

void Backtest::Stats()
{
    std::cout << "\nInitial Balance: $" << initialBalance << std::endl;
    std::cout << "Final Balance: $" << finalBalance << std::endl;
    std::cout << "Profit: $" << finalBalance - initialBalance << std::endl;
    std::cout << "Return: "<< ((finalBalance - initialBalance)/ initialBalance)*100 << "%" << std::endl;
}
