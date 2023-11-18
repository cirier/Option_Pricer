#include "DigitalOption.h"

DigitalOption::DigitalOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Error: Expiry and strike must be positive.");
    }
}

double DigitalOption::getStrike() const { return _strike; }