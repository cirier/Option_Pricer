
#pragma once
#include <iostream>
#include "Option.h"

class VanillaOption : public Option {
private:
    double _strike;

public:
    enum class optionType { call, put };
    VanillaOption(double expiry, double strike);
    
    double getStrike() const;

    virtual optionType GetOptionType() const=0;

    friend class VanillaCallOption;
    friend class VanillaPutOption;
    friend class BlackScholesPricer;
};