#include <iostream>
#include "BlackScholesPricer.h"
#include "VanillaOption.h"

BlackScholesPricer::BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility)
    : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility){}


double d1(const double& S, double& K, double& r, double& v, double& T) {
    return (log(S / K) + (r + v * v / 2) * T) / (v * sqrt(T));
}
double d2(const double& S, double& K, double& r, double& v, double& T) {
    return d1(S, K, r, v, T) - v * sqrt(T);
}

double BlackScholesPricer::operator()() const {
    double T = _option->getExpiry();
    double K = _option->_strike;
    double S = _asset_price;
    double r = _interest_rate;
    double v = _volatility;

    if (_option->GetOptionType() == VanillaOption::optionType::call) {
        return S * 0.5 * std::erfc(-d1(S, K, r, v, T) / sqrt(2.0)) - K * exp(-r * T) * 0.5 * std::erfc(-d2(S, K, r, v, T) / sqrt(2.0));
    }
    else {
        return -S * 0.5 * std::erfc(d1(S, K, r, v, T) / sqrt(2.0)) + K * exp(-r * T) * 0.5 * std::erfc(d2(S, K, r, v, T) / sqrt(2.0));
    }
}

double BlackScholesPricer::delta() const {
	double T = _option->getExpiry();
	double K = _option->_strike;
	double S = _asset_price;
	double r = _interest_rate;
	double v = _volatility;
    if (_option->GetOptionType() == VanillaOption::optionType::call) {
		return 0.5 * std::erfc(-d1(S, K, r, v, T) / sqrt(2.0));
	}
    else {
		return 0.5 * std::erfc(d1(S, K, r, v, T) / sqrt(2.0)) - 1;
	}
}