#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "EuropeanCallOption.h"
//#include "EuropeanPutOption.h" 
#include "BinaryTree.h"
#include "CRRPricer.h"

int main() {

    double S0(100.), K(101.), T(5.), r(0.01), sigma(0.1);
    EuropeanCallOption opt1(T, K);
    int N(5.);
    double U = 0.05;
    double D = -0.045;
    double R = 0.01;
    std::cout << "European options 1" << std::endl << std::endl;
    CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
    std::cout << "Calling CRR pricer with depth=" << N << std::endl;
    std::cout << std::endl;
    std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
    std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
    std::cout << std::endl;

    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new EuropeanCallOption(T, K));
    opt_ptrs.push_back(new AmericanCallOption(T, K));
    opt_ptrs.push_back(new AmericanPutOption(T, K));

    CRRPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new CRRPricer(opt_ptr, 5, S0, r, sigma);

        pricer->compute();

        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;

    }


}


