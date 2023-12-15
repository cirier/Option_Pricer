#include <iostream>
#include "VanillaOption.h"
#pragma once

class CallOption : public VanillaOption {
public:
    CallOption(double expiry, double strike);
    
    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;

};

