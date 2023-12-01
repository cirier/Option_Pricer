#ifndef AMERICANPUTOPTION_H
#define AMERICANPUTOPTION_H

#include "AmericanOption.h"
#include <algorithm>


class AmericanPutOption : public AmericanOption {
private:
    double _strike; // Strike price of the put option

public:
    AmericanPutOption(double expiry, double strike);
    double payoff(double stockPrice) const override;
    
};

#endif // AMERICANPUTOPTION_H
