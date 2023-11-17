#ifndef EUROPEANPUTOPTION_H
#define EUROPEANPUTOPTION_H

#include "EuropeanOption.h"

class EuropeanPutOption : public EuropeanOption {
private:
    double _strike;

public:
    EuropeanPutOption(double expiry, double strike);
    double payoff(double spotPrice) const override;
};

#endif // EUROPEANPUTOPTION_H
