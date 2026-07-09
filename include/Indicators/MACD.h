//Moving average convergence/divergence

#pragma once
#include "Strategy.h"

class MACD: public Strategy{

    private:

    public:
        MACD();

        double calcMACD();

};