#ifndef PLANNER_BF_HPP_
#define PLANNER_BF_HPP_

#include <vector>
#include "../plan.hpp"
#include "../planner.hpp"
#include "../tariff.hpp"

// Basic brute-force solution to (hopefully) improve upon
// and test againts
class PlannerBF : public Planner {
public:
    PlannerBF(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    Result plan(const Plan& plan) override;

private:
    Result bruteforce(
        PlanPointer pointer,
        Sequence sequence,
        Cost price);

    TariffList& tariff_list_;
};

#endif
