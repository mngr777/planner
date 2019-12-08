#ifndef SEQUENCE_HPP_
#define SEQUENCE_HPP_

#include <ostream>
#include <vector>
#include "tariff.hpp"

using Sequence = std::vector<TariffIdx>;

void print_sequence(
    std::ostream& os,
    const TariffList& tariff_list,
    const Sequence& sequence);

#endif
