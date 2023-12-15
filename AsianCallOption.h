#pragma once
#include "AsianOption.h"



class AsianCallOption : AsianOption {
private:
    double _strike;
public:
    AsianCallOption(double expiry, std::vector<double>_tk, double strike);

    double payoff(double S);
    optionType GetOptionType() const override;
};

