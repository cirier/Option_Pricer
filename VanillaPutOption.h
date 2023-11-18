#pragma once
#include <iostream>
#include "VanillaOption.h"

class VanillaPutOption : public VanillaOption {
public:
    VanillaPutOption(double expiry, double strike);

    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;
};