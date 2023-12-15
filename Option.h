#pragma once
#include <vector>
#include <iostream>
#include <cmath>

class Option {
private:
    double _expiry;
    bool _isAmerican;

public:
    Option(double expiry, bool _isAmerican = false);
    virtual ~Option() {}
    virtual double getExpiry() const;
    virtual double payoff(double) const=0;
    virtual double payoffPath(std::vector<double> S) const;
    virtual bool isAmericanOption() const;
    virtual bool getExercise(int n, int i);
    virtual bool isAsianOption();
};


