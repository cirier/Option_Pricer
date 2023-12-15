#pragma once
#include <iostream>
#include <vector>
#include "Option.h"

enum class DigitalOptionType { call, put };

class AsianOption : public Option {
private:
    std::vector<double>_tk;


public:

    enum class optionType { call, put };
    virtual optionType GetOptionType() const = 0;
    AsianOption(double expiry, std::vector<double>tk);
    double payoffPath(std::vector<double> S);
    double payoff(double S) override;
    bool isAsianOption() override;
    std::vector<double> getTimeSteps()const;

    friend class AsianCallOption;
    friend class AsianPutOption;
};