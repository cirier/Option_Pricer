#pragma once
#include "AsianOption.h"



class AsianCallOption : public AsianOption {
private:
    double _strike;
public:
    
    AsianCallOption(std::vector<double>_tk, double strike);

    double payoff(double S);
    optionType GetOptionType() const override;
};
