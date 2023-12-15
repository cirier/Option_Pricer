#include <iostream>
#include <vector>
#include "Option.h"
#include "MT.h"

class BlackScholesMCPricer
{
    private:
        Option* option;
        double initial_price;
        double interest_rate;
        double volatility;
        int nbPaths_generated;
        std::vector<std::vector<double>> allPaths;
    
    public:
        BlackScholesMCPricer (Option* option, double initial_price, double interest_rate, double volatility);
        int getNbPaths() const;
        std::vector<double> generate(int nbPaths);
        double operator()() const;
        std::vector<double> confidenceInterval();
};