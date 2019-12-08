#ifndef PLAN_HPP_
#define PLAN_HPP_

#include <ostream>
#include <utility>
#include <vector>
#include "types.hpp"

class Plan {
public:
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

    void add(Item item) {
        items_.emplace_back(std::move(item));
    }

    void add(Duration duration, Distance distance) {
        items_.emplace_back(duration, distance);
    }

    const ItemList& items() const { return items_; }

    Duration duration() const;
    Distance distance() const;

private:
     ItemList items_;
};

std::ostream& operator<<(std::ostream& os, const Plan& plan);
std::ostream& operator<<(std::ostream& os, const Plan::Item& item);

#endif
