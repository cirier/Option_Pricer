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
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(_depth), _exerciseTree(_depth) {

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


// Overloaded constructor with Black-Scholes parameters
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
    : _option(option), _depth(depth), _asset_price(asset_price), _tree(depth), _exerciseTree(depth) {
    double h = option->getExpiry() / static_cast<double>(depth); // Time step
    _up = exp((r + volatility * volatility / 2) * h + volatility * sqrt(h)) - 1;
    _down = exp((r + volatility * volatility / 2) * h - volatility * sqrt(h)) - 1;
    _interest_rate = exp(r * h) - 1;


}

BinaryTree<double> CRRPricer::getTree() const {
    return _tree;
}

void CRRPricer::compute() {
    for (int n = _depth; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            if (n == _depth) {

                //Calculate the option value using CRR formula for expiry dates N
                double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);
                double option_value = _option->payoff(stock_price);
                _tree.setNode(n, i, option_value);
                _exerciseTree.setNode(n, i, true); // At expiration, the option can always be exercised

            }
            else {

                double option_value_up = _tree.getNode(n + 1, i + 1);
                double option_value_down = _tree.getNode(n + 1, i);
                double q = (_interest_rate - _down) / (_up - _down);
                double option_value = ((q * option_value_up) + ((1 - q) * option_value_down)) / (1 + _interest_rate);



                // Set the node value to the max of option value or intrinsic value for American options
                if (_option->isAmericanOption()) {
                    // Calculate the intrinsic value for American options
                    double stock_price = stockPrice(i, n);
                    double intrinsic_value = intrinsicValue(stock_price);
                    if (intrinsic_value >= option_value)
                    {
                        _tree.setNode(n, i, intrinsic_value);
                        _exerciseTree.setNode(n, i, true);
                    }
                    else
                    {
                        _tree.setNode(n, i, option_value);
                        _exerciseTree.setNode(n, i, false);
                    }

                }
                else {
                    _tree.setNode(n, i, option_value);
                }


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


// ATENTION VOIR AVEC PROF -> Quel est l'operateur ou changer le nom de la fonction ??
// Function that returns the price of the option [H(0,0)]
double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        double q = (_interest_rate - _down) / (_up - _down);
        double h = 0.0;

        for (int i = 0; i <= _depth; i++) {
            double binomialCoefficient = factorial(_depth) / (factorial(i) * factorial(_depth - i));
            double term = binomialCoefficient * pow(q, i) * pow(1 - q, _depth - i);
            double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i);
            double optionPayoff = _option->payoff(stock_price);

            h += term * optionPayoff;
        }
        h = (1 / pow(1 + _interest_rate, _depth)) * h;
        return h;
    }
    else {
        compute();
        return get(0, 0);
    }
}

// Method to get the exercise condition from the tree
bool CRRPricer::getExercise(int n, int i) {
    // Make sure to check the bounds before accessing the tree
    if (n < 0 || i < 0 || n > _depth || i > n) {
        throw std::invalid_argument("Invalid indices.");
    }
    return _exerciseTree.getNode(n, i);
}


#include <algorithm> // For max function

// Function to calculate the intrinsic value of the option.
// It will depend on the type of option (e.g., call or put) and other factors.
double CRRPricer::intrinsicValue(double stock_price)
{

    return _option->payoff(stock_price);
}

// Function to calculate the continuation value
/*double CRRPricer::continuationValue(double stock_price, double intrinsic, int n, int i, double q, double R, const BinaryTree<double>& optionTree) {
    // Assuming optionTree is a 2D vector that contains option values at each node.

    // Ensure we are not at the last step
    if (n >= _depth - 1) {
        throw std::invalid_argument("Cannot calculate continuation value at the final step");
    }

    // Calculate the expected option value for the next step
    //double continuationUp = optionTree[n + 1][i + 1];
    double continuationDown = optionTree[n + 1][i];
    double continuationValue = (q * continuationUp + (1 - q) * continuationDown) / (1 + R);


    // The continuation value is the maximum of the continuation value and the intrinsic value
    return std::max(continuationValue, intrinsic);
}
*/
double CRRPricer::stockPrice(double i, double n)
{
    return _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);
}