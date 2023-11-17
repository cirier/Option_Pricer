#include "AmericanOption.h"

AmericanOption::AmericanOption(double expiry) : Option(expiry, true) {}

bool AmericanOption::getExercise(int n, int i) {
    return true;
}
