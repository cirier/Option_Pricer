#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

double AmericanPutOption::payoff(double spotPrice) const {
    if (spotPrice < _strike) {
        return _strike - spotPrice;
    }
    else {
        return 0.0;
    }
}
