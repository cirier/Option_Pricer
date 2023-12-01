#pragma once
#include "BinaryTree.h"
#include "Option.h"
class CRRPricer {
private:
	Option* _option;
	int _depth;
	double _asset_price;
	double _up;
	double _down;
	double _interest_rate;
	BinaryTree<double>_tree;

public:
	// Constructor 
	CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);

	BinaryTree<double> getTree() const;

	// Implements the CRR procedure
	void compute();

	// Implements the getter method
	double get(int n, int i);

	// Implements the factoriel method for the closed-formula
	double factorial(int n);

	// Implements the operator() method
	double operator()(bool closed_form = false);
	
};

