#include <iostream>
#include "AsianOption.h"
#include <vector>

AsianOption::AsianOption(double expiry, std::vector<double>tk) : Option(expiry), _tk(tk){
    tk = _tk;}

double AsianOption:: payoffPath(std::vector<double> St) {
    double mean = 0;

    for (int i = 0; i < St.size(); i++) {
        mean += St[i];
    }
    mean = mean / St.size();
    return payoff(mean);
}
double AsianOption::payoff(double S)
{
    return 0.0;
}
bool AsianOption:: isAsianOption() {
    return true;
}
std::vector<double> AsianOption:: getTimeSteps() const {
    return _tk;
}

