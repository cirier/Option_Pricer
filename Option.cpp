#include "Option.h"

Option::Option(double expiry, bool isAmerican) : _expiry(expiry), _isAmerican(isAmerican) {}

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

double Option::payoffPath(std::vector<double> S) const {
	return payoff(S.back());
}

double Option::payoff(double S) const {
	return 0;
}

