#include <iostream>
#include "DigitalOption.h"
#include "DigitalPutOption.h"

DigitalPutOption::DigitalPutOption(double expiry, double strike)
    : DigitalOption(expiry, strike) {}


double DigitalPutOption::payoff(double underlyingPrice) const {
    if (underlyingPrice <= _strike) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

DigitalPutOption::optionType DigitalPutOption::GetOptionType() const {
    return optionType::put;
}
