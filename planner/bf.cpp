#include "bf.hpp"
#include <cassert>
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

        const Plan::Item& current_item = pointer_tmp.current();

        // Use tariff until next plan item (count times)
        unsigned count = 1;
        {
            Duration current_offset = pointer_tmp.current_offset();
            Duration left = current_item.duration - current_offset;
            // ceil(left/tariff.duration)
            count = (left / tariff.duration)
                + (left % tariff.duration ? 1 : 0);
            for (unsigned i = 0; i < count; ++i)
                sequence_tmp.push_back(tariff_idx);
        }
        assert(count >= 1);

        // Add price of selected tariff
        // NOTE: assuming that plans that can span over multiple items
        // (duration > 1m) do not have idle price
        {
            Cost tariff_price = (tariff.has_idle() && pointer_tmp.current().is_idle())
                ? tariff.price_idle
                : tariff.price;
            price_tmp += tariff_price * count;
        }

        // Advance pointer
        // Add price for additional distance
        Distance additional_distance = pointer_tmp.advance(
            tariff.duration * count,
            tariff.distance * count);
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
