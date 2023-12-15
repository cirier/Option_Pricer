#include "AsianPutOption.h"


AsianPutOption::AsianPutOption (std::vector<double>_tk, double strike) : AsianOption(_tk,strike) {

};
double AsianPutOption::payoff(double Savg) {
    return std::max(_strike-Savg, 0.0);
    }

AsianPutOption::optionType AsianPutOption::GetOptionType() const {
    return optionType::put;
}
