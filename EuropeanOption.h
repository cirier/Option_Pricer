#ifndef EUROPEANOPTION_H
#define EUROPEANOPTION_H

#include "Option.h"

class EuropeanOption : public Option {
public:
    EuropeanOption(double expiry);
};

#endif // EUROPEANOPTION_H
