#pragma once
#include "Option.h"

enum class DigitalOptionType { call, put };

class DigitalOption : public Option {
protected:
    double _strike;

public:

    enum class optionType { call, put };

    DigitalOption(double expiry, double strike);

    double getStrike() const;

    virtual optionType GetOptionType() const = 0;

    virtual double payoff(double underlyingPrice) const = 0;

    friend class DigitalCallOption;
    friend class DigitalPutOption;
};
