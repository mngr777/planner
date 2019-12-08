#ifndef PLANNER_HPP_
#define PLANNER_HPP_

#include <ostream>
#include "plan.hpp"
#include "sequence.hpp"
#include "tariff.hpp"

class Planner {
public:
    struct Result {
        Result(Cost price, Sequence sequence)
            : price(price),
              sequence(sequence) {}

        Cost price;
        Sequence sequence;
    };

    virtual ~Planner() {}

    virtual Result plan(const Plan& plan) = 0;
};

#endif
