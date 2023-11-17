#ifndef EUROPEANCALLOPTION_H
#define EUROPEANCALLOPTION_H

#include "EuropeanOption.h"

class EuropeanCallOption : public EuropeanOption {
private:
    double _strike;

public:
    EuropeanCallOption(double expiry, double strike);
    double payoff(double spotPrice) const override;
};

#endif 
