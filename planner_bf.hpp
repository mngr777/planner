#ifndef PLANNER_BF_HPP_
#define PLANNER_BF_HPP_

#include <vector>
#include "plan.hpp"
#include "planner.hpp"
#include "tariff.hpp"

class PlannerBF {
public:
    PlannerBF(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    Sequence plan(const Plan& plan);

private:
    struct Result {
        Result(Cost price, Sequence sequence)
            : price(price),
              sequence(sequence) {}

        Cost price;
        Sequence sequence;
    };

    Result bruteforce(
        PlanPointer pointer,
        Sequence sequence,
        Cost price);

    TariffList& tariff_list_;
};

#endif
