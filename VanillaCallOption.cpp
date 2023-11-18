#include <iostream>
#include "VanillaOption.h"
#include "VanillaCallOption.h"


VanillaCallOption::VanillaCallOption(double expiry, double strike ) : VanillaOption(expiry, strike) {}

double VanillaCallOption::payoff(double underlyingPrice) const {
	return std::max(underlyingPrice - _strike, 0.0);
}

VanillaOption::optionType VanillaCallOption::GetOptionType() const {
	return optionType::call;
}
