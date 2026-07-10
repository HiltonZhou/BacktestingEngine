# BTC Backtesting Engine

A modular C++ backtesting engine for evaluating algorithmic trading strategies on historical Bitcoin price data.

The project is designed with extensibility in mind—new indicators and strategies can be added with minimal changes to the existing codebase.

---

## Features

### Indicators
- Simple Moving Average (SMA)
- Exponential Moving Average (EMA)
- Relative Strength Index (RSI)
- Moving Average Convergence Divergence (MACD)
- Stochastic Oscillator

### Strategies
- SMA Strategy
- EMA Strategy
- RSI Strategy
- MACD Strategy
- Stochastic Strategy
- EMA + RSI Strategy

### Performance Metrics
- Initial / Final Balance
- Total Profit
- Percentage Return
- Win Rate
- Commission Costs
- Maximum Drawdown (MDD)
- Sharpe Ratio

### Trading Features
- Buy/Sell signal generation
- Commission simulation
- Slippage simulation
- Portfolio value tracking

---

# Project Structure

```
BacktestingEngine/
│
├── include/
│   ├── Candle.h
│   ├── Data.h
│   ├── Strategy.h
│   └── Indicators/
│
├── src/
│   ├── Backtest.cpp
│   ├── Data.cpp
│   └── Indicators/
│
├── Data/
│   └── BTC-USD.csv
│
├── CMakeLists.txt
└── README.md
```

---

# Building

## First Time

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Rebuild After Changes

```bash
cd build
cmake --build .
```

---

# Running

```bash
./BacktestingEngine
```

---

# Creating Your Own Strategy

Every trading strategy inherits from the abstract `Strategy` interface.

```cpp
class MyStrategy : public Strategy
{
public:
    Signal generateSignal(const std::vector<Candle>& candles, int currentIndex) const override;
};
```

The strategy returns one of three signals:

```cpp
Signal::BUY
Signal::SELL
Signal::HOLD
```

The backtesting engine automatically executes trades based on these signals.

---

# Example Strategy

The EMA + RSI strategy combines trend following with momentum confirmation.

### Buy

- EMA(10) > EMA(30)
- RSI crosses above 50

This indicates a bullish trend with strengthening momentum.

### Sell

- EMA(10) < EMA(30)
- RSI crosses below 50

This indicates a bearish trend with weakening momentum.

---

# Running a Different Strategy

In `main.cpp`, simply create the strategy you want to test.

```cpp
EMA ema(20);

runTest(
    ema,
    BTC.getCandles(),
    1000,
    0.001
);
```

or

```cpp
RSI rsi;

runTest(
    rsi,
    BTC.getCandles(),
    1000,
    0.001
);
```

or your own strategy:

```cpp
EMARSIStrategy strategy;

runTest(
    strategy,
    BTC.getCandles(),
    1000,
    0.001
);
```

No changes to the backtesting engine are required.

---

# Future Improvements

- ATR
- Bollinger Bands
- ADX
- Position sizing
- Stop-loss / Take-profit
- Trailing stop
- Portfolio optimization
- Walk-forward analysis

