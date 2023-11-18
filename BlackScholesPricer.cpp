#include <iostream>
#include "BlackScholesPricer.h"
#include "Option.h"
#include "DigitalOption.h"
#include "VanillaOption.h"
#include <cmath>



BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
    : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility){}


double d1(const double& S, double& K, double& r, double& v, double& T) {
    return (log(S / K) + (r + v * v / 2) * T) / (v * sqrt(T));
}
double d2(const double& S, double& K, double& r, double& v, double& T) {
    return d1(S, K, r, v, T) - v * sqrt(T);
}
double normcdf(double value) {
    return 0.5 * std::erfc(-value / std::sqrt(2));
}

const double PI = 3.1415926535897932384626433832795028841971;

double BlackScholesPricer::operator()() const {
    
    double T = _option->getExpiry();
    double S = _asset_price;
    double r = _interest_rate;
    double v = _volatility;
    double K = 0.0;
    


    if (VanillaOption* vanillaOption = dynamic_cast<VanillaOption*>(_option))
    {
        K = vanillaOption-> getStrike();
        if (vanillaOption->GetOptionType() == VanillaOption::optionType::call) {
            return S * 0.5 * std::erfc(-d1(S, K, r, v, T) / sqrt(2.0)) - K * exp(-r * T) * 0.5 * std::erfc(-d2(S, K, r, v, T) / sqrt(2.0));
        }
        else {
            return -S * 0.5 * std::erfc(d1(S, K, r, v, T) / sqrt(2.0)) + K * exp(-r * T) * 0.5 * std::erfc(d2(S, K, r, v, T) / sqrt(2.0));
        }
    }

    else if (DigitalOption* digitalOption = dynamic_cast<DigitalOption*>(_option))
    {
        K = digitalOption->getStrike();
        if (digitalOption->GetOptionType() == DigitalOption::optionType::call) {
            return exp(-r * T) * normcdf(d2(S, K, r, v, T));
        }
        else { 
            return exp(-r * T) * normcdf(-d2(S, K, r, v, T));
        }

    }

    
}

double BlackScholesPricer::delta() const {
    
    double T = _option->getExpiry();
    double K = 0.0;
    double S = _asset_price;
    double r = _interest_rate;
    double v = _volatility;

    if (auto* vanillaOption = dynamic_cast<VanillaOption*>(_option)) 
    {
        K = vanillaOption->getStrike();
        if (vanillaOption->GetOptionType() == VanillaOption::optionType::call) {
            return 0.5 * std::erfc(-d1(S, K, r, v, T) / sqrt(2.0));
        }
        else {
            return 0.5 * std::erfc(-d1(S, K, r, v, T) / sqrt(2.0)) - 1;
        }
    }

    else if (auto* digitalOption = dynamic_cast<DigitalOption*>(_option))
    {
        K = digitalOption->getStrike();
        double d2_val = d2(S, K, r, v, T);
        double norm_pdf = std::exp(-0.5 * d2_val * d2_val) / sqrt(2 * PI);

        if (digitalOption->GetOptionType() == DigitalOption::optionType::call) {
            return exp(-r * T) * norm_pdf / (S * v * sqrt(T));
        }
        else {
            return -exp(-r * T) * norm_pdf / (S * v * sqrt(T));
        }

    }



	
}