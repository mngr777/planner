#include "tariff.hpp"
#include <string>
#include <utility>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../types.hpp"

namespace io {

const char PathTariffs[]          = "tariffs";
const char FieldName[]            = "name";
const char FieldPrice[]           = "price";
const char FieldPriceIdle[]       = "price_idle";
const char FieldPriceAdditional[] = "price_additional";
const char FieldDuration[]        = "duration";
const char FieldDistance[]        = "distance";

const char DefaultName[] = "<noname>";


TariffList read_tariff_list(std::istream& is) {
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;

    ptree pt;
    read_json(is, pt);

    TariffList tariff_list;
    auto pt_tariff_list = pt.get_child(PathTariffs);
    for (auto pair : pt_tariff_list) {
        auto pt_tariff = pair.second;

        auto name             = pt_tariff.get<std::string>(FieldName, DefaultName);
        auto price            = pt_tariff.get<Cost>(FieldPrice);
        auto price_idle       = pt_tariff.get<Cost>(FieldPriceIdle, 0.0);
        auto price_additional = pt_tariff.get<Cost>(FieldPriceAdditional, 0.0);
        auto duration         = pt_tariff.get<Duration>(FieldDuration);
        auto distance         = pt_tariff.get<Distance>(FieldDistance, 0.0);

        tariff_list.add(
            name,
            price, price_idle, price_additional,
            duration, distance);
    }
    return tariff_list;
}

void write_tariff_list(std::ostream& os, const TariffList& tariff_list) {
    using boost::property_tree::ptree;
    using boost::property_tree::write_json;

    ptree pt, pt_tariff_list;
    for (const Tariff& tariff : tariff_list.list()) {
        ptree pt_tariff;
        pt_tariff.put<std::string>(FieldName, tariff.name);
        pt_tariff.put<Cost>(FieldPrice, tariff.price);
        pt_tariff.put<Cost>(FieldPriceIdle, tariff.price_idle);
        pt_tariff.put<Cost>(FieldPriceAdditional, tariff.price_additional);
        pt_tariff.put<Duration>(FieldDuration, tariff.duration);
        pt_tariff.put<Distance>(FieldDistance, tariff.distance);

        pt_tariff_list.push_back(std::make_pair("", pt_tariff));
    }
    pt.add_child(PathTariffs, pt_tariff_list);

    write_json(os, pt);
}

} // namespace io
