#include "MACD.h"
#include "EMA.h"
#include <iostream>

MACD::MACD()
{

}

double MACD::calcMACD()
{   
    EMA period_12(12);
    EMA period_26(26);

    double macdLine =  period_12 - period_26;
}