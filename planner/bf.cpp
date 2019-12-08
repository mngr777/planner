#include "bf.hpp"
#include <limits>

Planner::Result PlannerBF::plan(const Plan& plan) {
    PlanPointer pointer(plan);
    return bruteforce(pointer, Sequence(), 0.0);
}

PlannerBF::Result PlannerBF::bruteforce(
    PlanPointer pointer,
    Sequence sequence,
    Cost price)
{
    Result best_result(std::numeric_limits<Cost>::max(), {});

    for (TariffIdx tariff_idx = 0; tariff_idx < tariff_list_.size(); ++tariff_idx) {
        const Tariff& tariff = tariff_list_.get(tariff_idx);

        PlanPointer pointer_tmp = pointer;
        Cost price_tmp          = price;
        Sequence sequence_tmp   = sequence;
        sequence_tmp.push_back(tariff_idx);

        // Add price of selected tariff
        // NOTE: assuming that plans that can span over multiple items
        // (duration > 1m) do not have idle price
        price_tmp += (tariff.has_idle() && pointer_tmp.current().is_idle())
            ? tariff.price_idle
            : tariff.price;

        // Advance pointer
        // Add price for additional distance
        Distance additional_distance = pointer_tmp.advance(tariff.duration, tariff.distance);
        if (tariff.has_additional())
            price_tmp += (tariff.price_additional * additional_distance);

        // Result
        Result result = pointer_tmp.is_finished()
            ? Result(price_tmp, sequence_tmp)
            : bruteforce(pointer_tmp, sequence_tmp, price_tmp);

        // Check if result is better
        if (result.price < best_result.price)
            best_result = result;
    }

    return best_result;
}
