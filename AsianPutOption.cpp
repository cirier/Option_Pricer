#include "AsianPutOption.h"


AsianPutOption::AsianPutOption (double expiry, std::vector<double>_tk, double strike) : AsianOption(expiry, _tk){

};
double AsianPutOption::payoff(double Savg) {
    return std::max(_strike-Savg, 0.0);
    }

AsianPutOption::optionType AsianPutOption::GetOptionType() const {
    return optionType::put;
}
