#include "EuropeanPutOption.h"

EuropeanPutOption::EuropeanPutOption(double expiry, double strike)
    : EuropeanOption(expiry), _strike(strike) {}

double EuropeanPutOption::payoff(double spotPrice) const {
    if (spotPrice < _strike) {
        return _strike - spotPrice;
    }
    else {
        return 0.0;
    }
}
