#pragma once
#include <iostream>
#include "VanillaOption.h"

class BlackScholesPricer {
private:
    VanillaOption* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;


public:
    BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility);
    double operator()() const;
    double delta() const;

};

