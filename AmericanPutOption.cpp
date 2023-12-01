#include "AmericanPutOption.h"
#include <algorithm>

// Constructor implementation (if not defined inline)
AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

// Payoff function implementation
double AmericanPutOption::payoff(double stockPrice) const {
    return std::max(_strike - stockPrice, 0.0); // Payoff for a put option
}
