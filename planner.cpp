#include "planner.hpp"
#include <stdexcept>

Cost Estimator::estimate(Plan& plan, const Sequence& sequence) {
    Cost total = 0;
    plan.reset();
    for (TariffIdx tariff_idx : sequence) {
        if (plan.is_finished())
            throw std::invalid_argument("plan is already finished");

        // NOTE: assuming that plans that can span over multiple items
        // (duration > 1m) do not have idle price
        const Tariff& tariff = tariff_list_.get(tariff_idx);
        total += (tariff.has_idle() && plan.current().is_idle())
            ? tariff.price_idle
            : tariff.price;

        Distance additional_distance = plan.advance(tariff.duration, tariff.distance);
        if (tariff.has_additional())
            total += (tariff.price_additional * additional_distance);
    }

    if (!plan.is_finished())
        throw std::invalid_argument("cannot finish plan");

    return total;
}
