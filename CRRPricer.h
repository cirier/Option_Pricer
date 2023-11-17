#ifndef CRRPRICER_H
#define CRRPRICER_H

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer {
private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    double _volatility;
    BinaryTree<double> _tree;
    BinaryTree<bool> _exercise_conditions;

public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);
    void compute();
    double get(int n, int i);
    double operator()();
    BinaryTree<bool> getExerciseConditions() const;
    void setDepth(int newDepth);
};

#endif
