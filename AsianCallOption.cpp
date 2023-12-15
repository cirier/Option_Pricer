#include "AsianCallOption.h"
#include "AsianOption.h"
#include <iostream>
#include <cmath>
#include <vector>


AsianCallOption :: AsianCallOption(double expiry, std::vector<double>_tk, double strike) 
    : AsianOption(expiry, _tk){}

double AsianCallOption::payoff(double Savg) {
    return std::max(Savg - _strike, 0.0);
}
    
AsianCallOption ::optionType AsianCallOption :: GetOptionType() const {
    return optionType::call;
}
