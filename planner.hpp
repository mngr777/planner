#ifndef PLANNER_HPP_
#define PLANNER_HPP_

#include <ostream>
#include "plan.hpp"
#include "tariff.hpp"

using Sequence = std::vector<TariffIdx>;

void print_sequence(
    std::ostream& os,
    const TariffList& tariff_list,
    const Sequence& sequence);


class Estimator {
public:
    Estimator(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    Cost estimate(const Plan& plan, const Sequence& sequence) const;

private:
    TariffList& tariff_list_;
};

#endif
