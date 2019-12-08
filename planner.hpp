#ifndef PLANNER_HPP_
#define PLANNER_HPP_

#include "plan.hpp"
#include "tariff.hpp"

using Sequence = std::vector<TariffIdx>;

class Validator {
public:
    Validator(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    bool validate(const Plan& plan, const Sequence& sequence);

private:
    TariffList& tariff_list_;
};

#endif
