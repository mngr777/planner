#include "plan.hpp"
#include <numeric>
#include <stdexcept>

// Plan

void Plan::add(Plan::Item item) {
    duration_ += item.duration;
    distance_ += item.distance;
    items_.emplace_back(std::move(item));
}

void Plan::add(Duration duration, Distance distance) {
    add(Item(duration, distance));
}


// Plan pointer

const Plan::Item& PlanPointer::current() const {
    return plan_.items().at(current_idx_);
}

Distance PlanPointer::advance(Duration duration, Distance distance) {
    while (!is_finished() && duration > 0) {
        const Plan::Item& item = current();
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

bool PlanPointer::is_finished() const {
    return current_idx_ == plan_.items().size();
};

void PlanPointer::reset() {
    current_idx_ = 0;
    current_offset_ = 0;
}


// Default output

std::ostream& operator<<(std::ostream& os, const Plan& plan) {
    using std::endl;

    const Plan::ItemList& items = plan.items();
    for (unsigned i = 0; i < items.size(); ++i)
        os << (i + 1) << ": " << items[i] << endl;
    os << "Total duration: " << plan.duration() << endl;
    os << "Total distance: " << plan.distance() << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Plan::Item& item) {
    os << item.duration << "min, "
       << item.distance << " km";
    if (item.is_idle())
        os << " (idle)";
    return os;
}

std::ostream& operator<<(std::ostream& os, const PlanPointer& pointer) {
    return os << "("
       << (pointer.current_idx() + 1) << " "
       << pointer.current_offset()
       << ")";
}
