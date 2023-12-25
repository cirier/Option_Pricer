#include <iostream>
#include <cmath>
#include "BlackScholesMCPricer.h"
#include "Option.h"
#include "MT.h"

#include <random>

BlackScholesMCPricer::BlackScholesMCPricer (Option* option, double initial_price, double interest_rate, double volatility)
    :option(option), initial_price(initial_price), interest_rate(interest_rate), volatility(volatility) , nbPaths_generated(0), current_estimate(0.0), sum_payoffs(0.0), sum_squared_payoffs(0.0)
    {
        if (dynamic_cast<AsianCallOption*>(option))
        {
            callOption = dynamic_cast<AsianCallOption*>(option);
            putOption = nullptr;
        }
        else if (dynamic_cast<AsianPutOption*>(option))
        {
            putOption = dynamic_cast<AsianPutOption*>(option);
            callOption = nullptr;
        }
        else if (dynamic_cast<VanillaOption*>(option))
        {
            vanillaOption = dynamic_cast<VanillaOption*>(option);
            callOption = nullptr;
        }
        else if (dynamic_cast<DigitalOption*>(option))
        {
            digitalOption = dynamic_cast<DigitalOption*>(option);
            callOption = nullptr;
        }
    }
         
int BlackScholesMCPricer::getNbPaths() const
{
    return nbPaths_generated;
}



void BlackScholesMCPricer::generate(int nb_paths) {
    std::vector<double> S(nb_paths+nbPaths_generated);
    double St;
    double T = option->getExpiry();
    double dt = T / nb_paths; // t[i]-t[i-1]= (k*T/N - (k-1)*T/N)=T/N
    double k = interest_rate - ((volatility*volatility) / 2);
    S[0] = initial_price;
    sum_payoffs=0;
    sum_squared_payoffs = 0;
    for (int i = 1; i < nbPaths_generated+ nb_paths; i++)
    {
        double Z;
        Z = MT::rand_norm();
        //std::cout << "Z=" << Z << "\n";
        
         St = S[0] * exp(k * dt + volatility * sqrt(dt) * Z);
         St = St * exp(k * dt+ volatility * sqrt(dt) * Z);  //end of page 8 formula
         S.push_back(St);
         //std::cout << "S=" << S[i] << "\n\n";
         double path_payoff = 0;
        if (dynamic_cast<AsianCallOption*>(callOption))
        {
            double path_payoff = callOption->payoffPath(S);
        }
        else if (dynamic_cast<AsianPutOption*>(putOption))
        {
            double path_payoff = putOption->payoffPath(S);
        }
        if (dynamic_cast<DigitalOption*>(digitalOption))
        {
            double path_payoff = digitalOption->payoffPath(S);
        }
        else if (dynamic_cast<VanillaOption*>(vanillaOption))
        {
            double path_payoff = vanillaOption->payoffPath(S);
        }
        
        //std::cout << "payoff=" << path_payoff << "\n";
        sum_payoffs += path_payoff;
        //std::cout << "Sum payoff=" << sum_payoffs << "\n\n";
        sum_squared_payoffs += path_payoff * path_payoff;
    }
    nbPaths_generated += nb_paths;
    current_estimate = exp(-interest_rate * T) * (sum_payoffs / nbPaths_generated);
    //std::cout << "current_estimate=" << current_estimate << "\n\n\n";
     
}

double BlackScholesMCPricer::operator()() const{
    if (nbPaths_generated == 0) {
        throw std::runtime_error("No paths generated");
    }
    return current_estimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval(){
    double mean = sum_payoffs / nbPaths_generated;
    double variance = (sum_squared_payoffs / (nbPaths_generated-1)) - (mean * mean);
    double stddev = sqrt(variance);
    double margin_error = 1.96 * stddev / sqrt(nbPaths_generated); // 95% confidence interval
    return { mean - margin_error, mean + margin_error };
}