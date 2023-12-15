#include <iostream>
#include <cmath>
#include "BlackScholesMCPricer.h"
#include "Option.h"
#include "MT.h"

BlackScholesMCPricer::BlackScholesMCPricer (Option* option, double initial_price, double interest_rate, double volatility)
    :option(option), initial_price(initial_price), interest_rate(interest_rate), volatility(volatility) 
    {}
         
int BlackScholesMCPricer::getNbPaths() const
{
    return nbPaths_generated;
}

std::vector<double> BlackScholesMCPricer::generate(int nb_paths) {
    std::vector<double> S(nb_paths);
    std::vector<double> t(nb_paths);
    std::vector<double> Z(nb_paths);
    t[0]=0;
    Z[0]=0; //here this value doesn't really matter because it won't be used
    //we could have use (nb_paths-1) random Z numbers but we did not to be more coherent with the 'end of page 8' formula
    double T= option->getExpiry();
    S.push_back(initial_price);
    double k=interest_rate-(pow(volatility,2)/2);

    for(int i=1; i < nb_paths; i++)
    {
        t[i]=i*T/nb_paths;
        Z[i]=MT::rand_norm();
        S[i]=S[i-1]*exp(k*((t[i]-t[i-1])+volatility*sqrt(t[i]-t[i-1])*Z[i])); //end of page 8 formula
        
    }
    //we now have our Black-Scholes sample path stored in the vector S
    nbPaths_generated += 1;
    allPaths.push_back(S);
    return S;

}

double BlackScholesMCPricer::operator()() const{
    double H=0;
    double sum=0;
    for(int i=0; i< allPaths.size(); i++)
    {
        sum+=option->payoffPath(allPaths[i]);
    }
    H=exp(-interest_rate*option->getExpiry())*(1/nbPaths_generated)*sum;
    return H;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval(){
    std::vector<double> IC;
    double sum=0;
    double sum_sq=0; //sum squared
    for(int i=0; i<nbPaths_generated; i++){
        for(int j=0; j< allPaths[i].size(); j++)
        {
            sum+=option->payoff(allPaths[i][j]);
            sum_sq+=pow(option->payoff(allPaths[i][j]),2);
        }
    }
    double mean = sum/nbPaths_generated;
    double variance = (sum_sq / nbPaths_generated) - (mean * mean);
    double stddev = std::sqrt(variance);
    double error = 1.96 * stddev / std::sqrt(nbPaths_generated); // 95% confidence interval
    IC.push_back(mean - error);
    IC.push_back(mean + error);
    return IC;
}