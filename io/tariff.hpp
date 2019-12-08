#ifndef IO_TARIFF_HPP_
#define IO_TARIFF_HPP_

#include <istream>
#include <ostream>
#include "../tariff.hpp"

namespace io {

TariffList read_tariff_list(std::istream& is);

void write_tariff_list(std::ostream& os, const TariffList& tariff_list);

}

#endif
