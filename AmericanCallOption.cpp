#include "AmericanCallOption.h"
#include <algorithm>
// Constructor implementation (if not defined inline)
AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

// Payoff function implementation
double AmericanCallOption::payoff(double stockPrice) const {
    return std::max(stockPrice - _strike, 0.0); // Payoff for a call option
}
