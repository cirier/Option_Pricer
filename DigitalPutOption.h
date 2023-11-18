#pragma once
#include <iostream>
#include "DigitalOption.h"

class DigitalPutOption : public DigitalOption {
public:
    DigitalPutOption(double expiry, double strike);

    double payoff(double underlyingPrice) const override;

    optionType GetOptionType() const override;
};