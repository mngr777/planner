#ifndef PLAN_HPP_
#define PLAN_HPP_

#include <ostream>
#include <utility>
#include <vector>
#include "types.hpp"

class Plan {
public:
    // Plan item
    class Item {
    public:
        Item(Duration duration, Distance distance)
            : duration(duration),
              distance(distance) {}

        bool is_idle() const { return distance == 0.0; }

        const Duration duration;
        const Distance distance;
    };
    using ItemList = std::vector<Item>;

    Plan() :
        duration_(0),
        distance_(0) {}

    // Adding plan item
    void add(Item item);
    void add(Duration duration, Distance distance);


    const ItemList& items() const { return items_; }

    Duration duration() const { return duration_; }
    Distance distance() const { return distance_; }

private:
    ItemList items_;
    Duration duration_;
    Distance distance_;
};


class PlanPointer {
public:
    PlanPointer(const Plan& plan)
        : plan_(plan),
          current_idx_(0),
          current_offset_(0) {}

    const Plan::Item& current() const;

    // Advance, return distance over limit
    Distance advance(Duration duration, Distance distance);

    bool is_finished() const;

    void reset();

private:
    const Plan plan_;
    unsigned current_idx_;
    Duration current_offset_;
};


std::ostream& operator<<(std::ostream& os, const Plan& plan);
std::ostream& operator<<(std::ostream& os, const Plan::Item& item);

#endif
