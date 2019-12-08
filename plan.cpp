#include "plan.hpp"
#include <numeric>

Duration Plan::duration() const {
    Duration result = 0;
    for (const Item& item : items_)
        result += item.duration;
    return result;
}

Distance Plan::distance() const {
    Distance result = 0;
    for (const Item& item : items_)
        result += item.distance;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Plan& plan) {
    using std::endl;

    const Plan::ItemList& items = plan.items();
    for (unsigned i = 0; i < items.size(); ++i)
        os << (i + 1) << ": " << items[i] << endl;
    os << "Duration: " << plan.duration() << endl;
    os << "Distance: " << plan.distance() << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Plan::Item& item) {
    os << item.duration << "min, "
       << item.distance << " km";
    if (item.is_idle())
        os << " (idle)";
    return os;
}
