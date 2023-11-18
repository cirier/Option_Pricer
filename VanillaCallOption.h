#include <iostream>
#include "VanillaOption.h"
#pragma once

class VanillaCallOption : public VanillaOption {
public:
    VanillaCallOption(double expiry, double strike);
    
    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;
};