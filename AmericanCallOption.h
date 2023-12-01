#ifndef AMERICANCALLOPTION_H
#define AMERICANCALLOPTION_H

#include "AmericanOption.h"
#include <algorithm>


class AmericanCallOption : public AmericanOption {
private:
    double _strike; // Strike price of the call option

public:
    AmericanCallOption(double expiry, double strike);
    double payoff(double stockPrice) const override;
};

#endif // AMERICANCALLOPTION_H
