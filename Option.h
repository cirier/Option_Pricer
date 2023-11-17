#ifndef OPTION_H
#define OPTION_H

#include <iostream>
#include <cmath>

class Option {
private:
    double _expiry;
    bool _isAmerican;

public:
    Option(double expiry, bool isAmerican = false);
    double getExpiry() const;
    virtual double payoff(double) const = 0;
    bool isAmericanOption() const;
    virtual bool getExercise(int n, int i);
};

#endif // OPTION_H
