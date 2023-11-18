
#pragma once
#include <iostream>
#include "Option.h"

class VanillaOption : public Option {
private:
    double _strike;

public:
    enum class optionType { call, put };
    VanillaOption(double expiry, double strike);

    virtual optionType GetOptionType() const;

    friend class VanillaCallOption;
    friend class VanillaPutOption;
    friend class BlackScholesPricer;
};