#pragma once

#define OPTION_H
#include <iostream>
#include <cmath>

class Option {
private:
    double _expiry;
    bool _isAmerican;

public:
    Option(double expiry);
    virtual ~Option() {} // Define virtual destructor
    double getExpiry() const;
    virtual double payoff(double) const = 0; // Pure virtual function
    virtual bool isAmericanOption() const; // Declare as virtual without a body
    virtual bool getExercise(int n, int i);
    virtual bool isAsianOption();
};



