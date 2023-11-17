#include "EuropeanCallOption.h"

EuropeanCallOption::EuropeanCallOption(double expiry, double strike)
    : EuropeanOption(expiry), _strike(strike) {}

double EuropeanCallOption::payoff(double spotPrice) const {
    if (spotPrice > _strike) {
        return spotPrice - _strike;
    }
    else {
        return 0.0;
    }
}
