#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption {
private:
    double _strike;
public:
    AsianPutOption(std::vector<double>_tk, double strike);
    double payoff(double S);
    optionType GetOptionType() const override;
};