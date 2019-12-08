#include "sequence.hpp"

namespace {

void print_sequence_item(
    std::ostream& os,
    const TariffList& tariff_list,
    TariffIdx tariff_idx,
    unsigned counter,
    unsigned group_num)
{
    // Print plan name with multiplier, e.g. '2 x "plan name"'
    os << (group_num + 1) << ": ";
    if (counter > 1) os << counter << " x ";
    os << '"' << tariff_list.get(tariff_idx).name << '"' << std::endl;
}

} // anonymous namespace

void print_sequence(
    std::ostream& os,
    const TariffList& tariff_list,
    const Sequence& sequence)
{
    // Print each group of repeating items

    TariffIdx prev_tariff_idx = NoTariffIdx;
    unsigned counter = 0, group_num = 0;
    for (const TariffIdx tariff_idx : sequence) {
        if (tariff_idx != prev_tariff_idx && counter > 0) {
            print_sequence_item(os, tariff_list, prev_tariff_idx, counter, group_num++);
            counter = 0;
        }
        prev_tariff_idx = tariff_idx;
        ++counter;
    }
    if (counter > 0)
        print_sequence_item(os, tariff_list, prev_tariff_idx, counter, group_num++);
}
