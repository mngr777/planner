#include "tariff.hpp"

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
