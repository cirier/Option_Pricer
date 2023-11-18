#include <iostream>
#include "DigitalOption.h"
#include "DigitalCallOption.h"

DigitalCallOption::DigitalCallOption(double expiry, double strike)
    : DigitalOption(expiry, strike) {}


double DigitalCallOption::payoff(double underlyingPrice) const {
    if (underlyingPrice >= _strike) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

DigitalCallOption::optionType DigitalCallOption::GetOptionType() const {
    return optionType::call;
}
