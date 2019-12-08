#ifndef PLANNER_HPP_
#define PLANNER_HPP_

#include "plan.hpp"
#include "tariff.hpp"

using Sequence = std::vector<TariffIdx>;

class Estimator {
public:
    Estimator(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    Cost estimate(Plan& plan, const Sequence& sequence);

private:
    TariffList& tariff_list_;
};

#endif
