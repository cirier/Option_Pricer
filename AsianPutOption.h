#pragma once
#include "AsianOption.h"

class AsianPutOption : AsianOption {
private:
    double _strike;
public:
    AsianPutOption(double expiry, std::vector<double>_tk, double strike);
    double payoff(double S);
    optionType GetOptionType() const override;
};