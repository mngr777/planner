#ifndef IO_PLAN_HPP_
#define IO_PLAN_HPP_

#include <istream>
#include <ostream>
#include "../plan.hpp"

namespace io {

Plan read_plan(std::istream& is);

void write_plan(std::ostream& os, const Plan& plan);

}

#endif
