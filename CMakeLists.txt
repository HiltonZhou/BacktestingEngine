cmake_minimum_required(VERSION 3.16)

project(BacktestingEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    BacktestingEngine
    main.cpp
    src/Data.cpp
    src/Backtest.cpp
    src/SMA.cpp
    src/EMA.cpp
    src/RSI.cpp
    src/MACD.cpp
    src/Stoch.cpp
)