#ifndef PLANNER_BF_HPP_
#define PLANNER_BF_HPP_

#include <vector>
#include "plan.hpp"
#include "tariff.hpp"

class PlannerBF {
public:
    PlannerBF(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    void plan(const Plan& plan);

private:
    TariffList& tariff_list_;
};

#endif
