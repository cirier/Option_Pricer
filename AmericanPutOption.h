#ifndef AMERICANPUTOPTION_H
#define AMERICANPUTOPTION_H

#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption {
private:
    double _strike;

public:
    AmericanPutOption(double expiry, double strike);
    double payoff(double spotPrice) const override;
};

#endif // AMERICANPUTOPTION_H
