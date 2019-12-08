#include "estimator.hpp"
#include <stdexcept>

Cost Estimator::estimate(const Plan& plan, const Sequence& sequence) const {
    Cost total = 0;

    PlanPointer pointer(plan);
    for (TariffIdx tariff_idx : sequence) {
        if (pointer.is_finished())
            throw std::invalid_argument("plan is already finished");

        // NOTE: assuming that plans that can span over multiple items
        // (duration > 1m) do not have idle price
        const Tariff& tariff = tariff_list_.get(tariff_idx);
        total += (tariff.has_idle() && pointer.current().is_idle())
            ? tariff.price_idle
            : tariff.price;

        Distance additional_distance = pointer.advance(tariff.duration, tariff.distance);
        if (tariff.has_additional())
            total += (tariff.price_additional * additional_distance);
    }

    if (!pointer.is_finished())
        throw std::invalid_argument("cannot finish plan");

    return total;
}
