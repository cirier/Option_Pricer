#ifndef AMERICANCALLOPTION_H
#define AMERICANCALLOPTION_H

#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption {
private:
    double _strike;

public:
    AmericanCallOption(double expiry, double strike);
    double payoff(double spotPrice) const override;
};

#endif 
