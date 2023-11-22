#include "Option.h"

Option::Option(double expiry, bool isAmerican = false) : _expiry(expiry), _isAmerican(isAmerican) {}

double Option::getExpiry() const {
    return _expiry;
}

bool Option::isAmericanOption() const {
    return _isAmerican;
}

bool Option::getExercise(int n, int i) {
    return false;
}
