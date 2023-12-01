#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H

#include "Option.h"

class AmericanOption : public Option {
public:
    AmericanOption(double expiry); // Declare constructor without a body
    bool isAmericanOption() const override; // Declare override without a body
};

#endif // AMERICANOPTION_H
