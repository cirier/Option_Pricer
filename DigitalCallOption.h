#pragma once
#include <iostream>
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption {
public:
    DigitalCallOption(double expiry, double strike);

    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;
};