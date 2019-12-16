#include "plan.hpp"
#include <utility>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../types.hpp"

namespace io {

static const char PathItems[]     = "items";
static const char FieldDuration[] = "duration";
static const char FieldDistance[] = "distance";


Plan read_plan(std::istream& is) {
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;

    ptree pt;
    read_json(is, pt);

    Plan plan;
    auto items_pt = pt.get_child(PathItems);
    for (const auto& pair : items_pt) {
        auto duration = pair.second.get<Duration>(FieldDuration);
        auto distance = pair.second.get<Distance>(FieldDistance);
        plan.add(duration, distance);
    }
    return plan;
}

void write_plan(std::ostream& os, const Plan& plan) {
    using boost::property_tree::ptree;
    using boost::property_tree::write_json;

    ptree pt, pt_items;
    for (const Plan::Item& item : plan.items()) {
        ptree pt_item;
        pt_item.put<Duration>(FieldDuration, item.duration);
        pt_item.put<Distance>(FieldDistance, item.distance);
        pt_items.push_back(std::make_pair("", pt_item));
    }
    pt.add_child(PathItems, pt_items);

    write_json(os, pt);
}

} // namespace io
