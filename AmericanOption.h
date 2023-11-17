#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H

#include "Option.h"

class AmericanOption : public Option {
public:
    AmericanOption(double expiry);
    bool getExercise(int n, int i) override;
};

#endif
