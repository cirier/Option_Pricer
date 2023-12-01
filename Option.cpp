#include "Option.h"

Option::Option(double expiry) : _expiry(expiry), _isAmerican(false) {}

double Option::getExpiry() const {
    return _expiry;
}

bool Option::isAmericanOption() const {
    return _isAmerican;
}

bool Option::getExercise(int n, int i) {
    return false;
}

bool Option::isAsianOption() {
    return false;
}
