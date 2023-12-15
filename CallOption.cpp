#include <iostream>
#include "VanillaOption.h"
#include "CallOption.h"


CallOption::CallOption(double expiry, double strike ) : VanillaOption(expiry, strike) {}

double CallOption::payoff(double underlyingPrice) const {
	return std::max(underlyingPrice - _strike, 0.0);
}

VanillaOption::optionType CallOption::GetOptionType() const {
	return optionType::call;
}

