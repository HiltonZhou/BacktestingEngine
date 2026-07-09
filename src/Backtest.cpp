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
    this->highestPortfolioValue = cashAmt;
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

        currentPortfolioValue = balance + quantity * candles[i].close;
        
        portfolioValue.push_back(currentPortfolioValue);

        MaximumDrawdown(currentPortfolioValue);
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

    //std::cout << "BUY: " << candle.date << " AT " << candle.close << std::endl;
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

    //std::cout << "SELL: " << candle.date << " AT " << candle.close << std::endl;
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
    std::cout << "Sharpe Ratio: " << SharpeRatio() << std::endl;
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

void Backtest::MaximumDrawdown(double currentPortfolioValue)
{

    if(currentPortfolioValue > highestPortfolioValue){
        highestPortfolioValue = currentPortfolioValue;
    }

    double drawdown = (highestPortfolioValue - currentPortfolioValue) / highestPortfolioValue;

    if(drawdown > maximumDrawdown){
        maximumDrawdown = drawdown;
    }
}

double Backtest::calcAvgReturns()
{   

    for(size_t i = 1; i < portfolioValue.size(); i++){

        double r = (portfolioValue[i] - portfolioValue[i-1])/portfolioValue[i-1];

        returns.push_back(r);
    }
    
    double sums = 0.0;

    for(size_t i = 0; i < returns.size(); i++){
        sums += returns[i];
    }

    return sums/returns.size();
}

double Backtest::calcVolatility()
{   
    double mean = calcAvgReturns();
    double variance = 0.0;
    int n = returns.size();

    for(size_t i = 0; i < n; i++){
        variance += ((returns[i] - mean) * (returns[i] - mean)); //(returns[i] - mean)^2
    }

    variance = variance/(n-1);

    return std::sqrt(variance);
}

double Backtest::SharpeRatio()
{
    return (calcAvgReturns() - riskFreeRate)/calcVolatility();
}




