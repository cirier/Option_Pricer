#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include <vector>
class CRRPricer {
private:
	Option* _option;
	int _depth;
	double _asset_price;
	double _up;
	double _down;
	double _interest_rate;
	BinaryTree<double>_tree;
	BinaryTree<bool> _exerciseTree; // Store exercise conditions for American options


public:
	// Constructor 
	CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);

	// Overloaded constructor to initialize using Black-Scholes parameters
	CRRPricer(Option* option, int depth, double asset_price, double r, double volatility);


	BinaryTree<double> getTree() const;

	// Implements the CRR procedure
	void compute();

	// Implements the getter method
	double get(int n, int i);

	// Implements the factoriel method for the closed-formula
	double factorial(int n);
	// Implements the operator() method
	double operator()(bool closed_form = false);

	bool getExercise(int n, int i);

	double intrinsicValue(double stock_price);

	//double continuationValue(double stock_price, double intrinsic, int n, int i, double q, double R, const BinaryTree<double>& optionTree);

	double stockPrice(double i, double n);

};