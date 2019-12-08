#include "planner.hpp"

bool Validator::validate(const Plan& plan, const Sequence& sequence) {
    const Plan::ItemList& items = plan.items();
    auto it = items.begin();
    auto end = items.end();
    unsigned seq_idx = 0;
    unsigned item_offset = 0, seq_offset = 0;

    while (it != end && seq_idx < sequence.size()) {

    }
}
