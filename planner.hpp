#ifndef PLANNER_HPP_
#define PLANNER_HPP_

#include <ostream>
#include "plan.hpp"
#include "sequence.hpp"
#include "tariff.hpp"

class Planner {
public:
    virtual ~Planner() {}

    virtual Sequence plan(const Plan& plan) = 0;
};

#endif
