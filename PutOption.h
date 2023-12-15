#pragma once
#include <iostream>
#include "VanillaOption.h"

class PutOption : public VanillaOption {
public:
    PutOption(double expiry, double strike);

    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;

};