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
    std::cout << "Starting Balance..." << initialBalance << std::endl;

    for(size_t i = 0; i < candles.size(); i++){
        Signal signal = strategy.generateSignal(candles,i);

        if( signal == Signal::BUY && !position){
            buy(candles[i]);
        }else if(signal == Signal::SELL && position){
            sell(candles[i]);
        }

        MaximumDrawdown(balance,quantity,candles,i);
        
    }

    //final run check if you still got btc
    if(position){
        sell(candles.back());
    }

    finalBalance = balance;
}

void Backtest::buy(const Candle& candle)
{   
    position = true;
    quantity = balance/candle.close;
    buyPrice = candle.close * (1 + slippage);

    double fee = executeCommision(balance);
    quantity = (balance - fee) / buyPrice;

    balance = 0;

    std::cout << "BUY: " << candle.date << " AT " << candle.close << std::endl;
}

void Backtest::sell(const Candle& candle)
{
    position = false;

    sellPrice = candle.close * (1 - slippage);

    double grossValue = quantity * sellPrice;
    double fee = executeCommision(grossValue);

    balance = grossValue - fee;
    quantity = 0;

    //calculate win or loss
    double profit = (sellPrice - buyPrice) * 100;

    if(profit > 0){
        wins++;
    }else if(profit < 0){
        losses++;
    }

    std::cout << "SELL: " << candle.date << " AT " << candle.close << std::endl;
}

void Backtest::Stats()
{   
    totalTrades = wins+losses;

    profit = finalBalance - initialBalance;
    
    std::cout << "Stats:" << std::endl;
    std::cout << "\nInitial Balance: $" << initialBalance << std::endl;
    std::cout << "Final Balance: $" << finalBalance << std::endl;
    std::cout << "Profit: $" << profit << std::endl;
    std::cout << "Return: "<< (profit/ initialBalance)*100 << "%" << std::endl;
    std::cout << "Winrate: " << 100.0 * wins/totalTrades << "%" << std::endl;
    std::cout << "total commision cost: $" << commisionBalance << std::endl;
    std::cout << "Maximum Drawdown: " << maximumDrawdown * 100.0 << "%"<< std::endl;
}

void Backtest::setCommision(double commision)
{
    this->commision = commision;
}

double Backtest::executeCommision(double tradeValue)
{
    double fee = tradeValue * commision;
    commisionBalance += fee;
    return fee;
}

double Backtest::MaximumDrawdown(double balance, double quantity, std::vector<Candle> candle, size_t index)
{
    currentPortfolioValue = balance + quantity * candles[index].close;

    if(currentPortfolioValue > highestPortfolioValue){
        highestPortfolioValue = currentPortfolioValue;
    }

    double drawdown = (highestPortfolioValue - currentPortfolioValue) / highestPortfolioValue;

    if(drawdown > maximumDrawdown){
        maximumDrawdown = drawdown;
    }
}


