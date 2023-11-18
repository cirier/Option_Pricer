#include <iostream>
#include "VanillaOption.h"

VanillaOption::VanillaOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {
    if (expiry < 0 || strike < 0) {
        throw std::invalid_argument("Error : Expiry and strike must be positive double ");
    }
}

VanillaOption::optionType VanillaOption::GetOptionType() const {
	return optionType::call;
}






