#include <iostream>
#include "PutOption.h"

PutOption::PutOption(double expiry, double strike)
	: VanillaOption(expiry, strike) {}

double PutOption::payoff(double underlyingPrice) const {
	return std::max(_strike - underlyingPrice, 0.0);
}

VanillaOption::optionType PutOption::GetOptionType() const {
	return optionType::put;
}

