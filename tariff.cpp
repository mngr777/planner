#include "tariff.hpp"
#include <stdexcept>

Tariff::Tariff(
    std::string name,
    Cost price,
    Cost price_idle,
    Cost price_additional,
    Duration duration,
    Distance distance)
    : name(std::move(name)),
      price(price),
      price_idle(price_idle),
      price_additional(price_additional),
      duration(duration),
      distance(distance)
{
    if (duration == 0)
        throw std::invalid_argument("Tariff duration cannot be zero");
}


std::ostream& operator<<(std::ostream& os, const Tariff& tariff) {
    using std::endl;
    os << tariff.name << endl 
       << "Price: " << tariff.price << endl;
    if (tariff.price_idle > 0)
        os << "Price idle: " << tariff.price_idle << endl;
    if (tariff.price_additional > 0)
        os << "Price additional: " << tariff.price_additional << "/km over limit" << endl;
    os << "Duration: " << tariff.duration << endl;
    if (tariff.distance > 0)
        os << "Distance limit: " << tariff.distance << endl;

    os << "per minute: " << (tariff.price / tariff.duration) << endl;
    if (tariff.distance > 0)
        os << "per km*: " << (tariff.price / tariff.distance) << endl;
    if (tariff.price_idle > 0)
        os << "per minute idle: " << (tariff.price_idle / tariff.duration) << endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const TariffList& tariff_list) {
    for (const Tariff& tariff : tariff_list.list())
        os << tariff << std::endl;
    return os;
}
