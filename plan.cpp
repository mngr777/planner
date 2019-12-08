#include "plan.hpp"
#include <numeric>
#include <stdexcept>

void Plan::add(Plan::Item item) {
    items_.emplace_back(std::move(item));
    duration_ += item.duration;
    distance_ += item.distance;
}

void Plan::add(Duration duration, Distance distance) {
    add(Item(duration, distance));
}


const Plan::Item& Plan::current() const {
    return items_.at(current_idx_);
}

Distance Plan::advance(Duration duration, Distance distance) {
    while (!is_finished() && duration > 0) {
        const Item& item = current();
        if (!item.is_idle())
            distance -= item.distance; // take item distance from distance limit

        if (current_offset_ + duration < item.duration) {
            // increase offset
            current_offset_ += duration;
            duration = 0;
        } else {
            // move to next item
            ++current_idx_;
            duration -= (item.duration - current_offset_);
            current_offset_ = 0;
        }
    }
    return (distance < 0.0) ? -distance : 0;
}

bool Plan::is_finished() const {
    return current_idx_ == items_.size();
}

void Plan::reset() {
    current_idx_ = 0;
    current_offset_ = 0;
}


// Default output

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
