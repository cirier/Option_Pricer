#include <iostream>
#include "VanillaPutOption.h"

VanillaPutOption::VanillaPutOption(double expiry, double strike)
	: VanillaOption(expiry, strike) {}

double VanillaPutOption::payoff(double underlyingPrice) const {
	return std::max(_strike - underlyingPrice, 0.0);
}

VanillaOption::optionType VanillaPutOption::GetOptionType() const {
	return optionType::put;
}