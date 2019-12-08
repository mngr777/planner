#ifndef TARIFF_HPP_
#define TARIFF_HPP_

#include <limits>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include "types.hpp"

class Tariff {
public:
    Tariff(
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
          distance(distance) {}

    bool has_idle() const { return price_idle > 0; }
    bool has_additional() const { return price_additional > 0; }

    const std::string name;
    const Cost price;
    const Cost price_idle;
    const Cost price_additional;
    const Duration duration;
    const Distance distance;
};


class TariffList {
public:
    using List = std::vector<Tariff>;
    using TariffIdx = List::size_type;

    void add(Tariff tariff) {
        list_.emplace_back(std::move(tariff));
    }

    void add(
        std::string name,
        Cost price, Cost price_idle, Cost price_additional,
        Duration duration,
        Distance distance)
    {
        list_.emplace_back(
            std::move(name),
            price, price_idle, price_additional,
            duration, distance);
    }

    const Tariff& get(TariffIdx idx) const {
        return list_.at(idx);
    }

    TariffIdx size() const {
        return list_.size();
    }

    const List& list() const { return list_; }

private:
    List list_;
};

using TariffIdx = TariffList::TariffIdx;
const TariffIdx NoTariffIdx = std::numeric_limits<TariffIdx>::max();

std::ostream& operator<<(std::ostream& os, const Tariff& tariff);
std::ostream& operator<<(std::ostream& os, const TariffList& tariff_list);

#endif
