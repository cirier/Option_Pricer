#include "CRRPricer.h"
#include <cmath>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate),
    _tree(depth), _exercise_conditions(depth) {
    for (int i = 0; i <= depth; ++i) {
        for (int j = 0; j <= i; ++j) {
            _exercise_conditions.setNode(i, j, option->getExercise(depth, i));
        }
    }
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
    : _option(option), _depth(depth), _asset_price(asset_price), _volatility(volatility),
    _tree(depth), _exercise_conditions(depth) {
    // Calculate U, D, and R based on the provided parameters and Section 6.
    double dt = _option->getExpiry() / static_cast<double>(_depth);
    double a = exp(r * dt);
    _up = exp(_volatility * sqrt(dt));
    _down = 1.0 / _up;
    _interest_rate = (a - _down) / (_up - _down);
}

void CRRPricer::compute() {
    for (int n = _depth; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            if (n == _depth) {
                double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);
                double option_value = _option->payoff(stock_price);
                _tree.setNode(n, i, option_value);

                if (_option->isAmericanOption()) {
                    _exercise_conditions.setNode(n, i, option_value >= stock_price);
                }
            }
            else {
                double option_value_up = _tree.getNode(n + 1, i + 1);
                double option_value_down = _tree.getNode(n + 1, i);
                double q = (_interest_rate - _down) / (_up - _down);
                double option_value = ((q * option_value_up) + ((1 - q) * option_value_down)) / (1 + _interest_rate);
                _tree.setNode(n, i, option_value);

                if (_option->isAmericanOption()) {
                    double stock_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, n - i);
                    double exercise_value = _option->payoff(stock_price);
                    _exercise_conditions.setNode(n, i, exercise_value >= option_value);
                }
            }
        }
    }
}

double CRRPricer::get(int n, int i) {
    if (n < 0 || i < 0 || n > _depth || i > n) {
        throw std::invalid_argument("Invalid indices.");
    }
    return _tree.getNode(n, i);
}

double CRRPricer::operator()() {
    if (_tree.getNode(0, 0) == 0) {
        compute();
    }
    return _tree.getNode(0, 0);
}

BinaryTree<bool> CRRPricer::getExerciseConditions() const {
    return _exercise_conditions;
}

void CRRPricer::setDepth(int newDepth) {
    if (newDepth < 0) {
        throw std::invalid_argument("Depth cannot be negative.");
    }
    _depth = newDepth;
    _tree = BinaryTree<double>(_depth);  // Réinitialise l'objet BinaryTree avec la nouvelle profondeur
    _exercise_conditions = BinaryTree<bool>(_depth);  // Réinitialise l'objet BinaryTree des conditions d'exercice
}
