#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

double AmericanCallOption::payoff(double spotPrice) const {
    if (spotPrice > _strike) {
        return spotPrice - _strike;
    }
    else {
        return 0.0;
    }
}
