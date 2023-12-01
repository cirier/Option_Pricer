#include "CRRPricer.h"
#include <vector>
#include <iostream>

// --- CRR Pricer

/*
* depth : N
* asset_price : S0
* up, down, interest_rate : U, D, R
*/

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(_depth) {
    
    /*if (option.isAsianOption() == true) {
        throw std::invalid_argument("Invalid parameters. Conditions: S0 > 0, U > D > -1 must be satisfied.");
    }*/

    // Check for conditions: S0 > 0, U > D > -1
    if (asset_price <= 0 || up <= down || down < -1) {
        throw std::invalid_argument("Invalid parameters. Conditions: S0 > 0, U > D > -1 must be satisfied.");
    }

    // Check for arbitrage

    /* If the Cox-Ross-Rubinstein model is used in a context where there is arbitrage,
    then the prices calculated by the model will not reflect the reality of the market.

    The CRR model relies on the assumption that there are no arbitrage opportunities in the market.
    In other words, it assumes that asset prices are determined in such a way that it is impossible
    to make risk-free profits by exploiting price variations.
    */
    if (_down >= _interest_rate || _interest_rate >= _up) {
        throw std::invalid_argument("Arbitrage detected. Conditions: D < R < U are not met.");
    }
}
BinaryTree<double> CRRPricer::getTree() const {
    return _tree;
}

void CRRPricer::compute() {
    for (int n = _depth;n >= 0;--n) {
        for (int i = 0;i <= n;++i) {
            if (n == _depth) {

                //Calculate the option value using CRR formula for expiry dates N
                double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);
                double option_value = _option->payoff(stock_price);
                _tree.setNode(n, i, option_value);

            }
            else {

                // Calculate the option value using CRR formula for non-expiry dates
                double option_value_up = _tree.getNode(n + 1, i + 1);
                double option_value_down = _tree.getNode(n + 1, i);

                double q = (_interest_rate - _down) / (_up - _down);

                double option_value = ((q * option_value_up) + ((1 - q) * option_value_down)) / (1 + _interest_rate);

                _tree.setNode(n, i, option_value);
            }
        }

    }
}

double CRRPricer::get(int n, int i) {
    // Check if the indices are valid
    if (n < 0 || i < 0 || n > _depth || i > n) {
        throw std::invalid_argument("Invalid indices.");
    }
    // Return the value at node (n, i)
    return _tree.getNode(n, i);
}

// Implements the factoriel method for the closed-formula
double CRRPricer::factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

// Function that returns the price of the option [H(0,0)]
double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        double q = (_interest_rate - _down) / (_up - _down);
        double h = 0.0;

        for (int i = 0;i <= _depth;i++) {
            double binomialCoefficient = factorial(_depth) / (factorial(i) * factorial(_depth - i));
            double term = binomialCoefficient * pow(q, i) * pow(1 - q, _depth - i);
            double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i);
            double optionPayoff = _option->payoff(stock_price);

            h += term * optionPayoff;
        }
        h = (1 / pow(1 + _interest_rate, _depth))*h;
        return h;
    }
    else {
        compute();
        return get(0, 0);
    }
}
