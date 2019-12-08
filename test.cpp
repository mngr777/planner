#include <iostream>
#include <stdexcept>
#include "plan.hpp"
#include "planner.hpp"
#include "planner_bf.hpp"
#include "tariff.hpp"
#include "types.hpp"

int main() {
    using namespace std;

    /// Init tariff list
    TariffList tariff_list;
    tariff_list.add("Per Minute", 0.3, 0.07, 0, 1, 0);     // 0
    tariff_list.add("3 hours", 24, 0, 0.29, 3 * 60, 35);   // 1
    tariff_list.add("6 hours", 34, 0, 0.29, 6 * 60, 55);   // 2
    tariff_list.add("9 hours", 42, 0, 0.29, 9 * 60, 70);   // 3
    tariff_list.add("12 hours", 49, 0, 0.29, 12 * 60, 80); // 4
    tariff_list.add("1 day", 59, 0, 0.29, 24 * 60, 105);   // 5

    cout << tariff_list << endl;

    /// Init plan
    Plan plan;
    plan.add(15, 20);
    plan.add(4 * 60, 0);
    plan.add(30, 250);

    cout << plan << endl;

    /// Plan
    PlannerBF planner_bf(tariff_list);
    planner_bf.plan(plan);

    /// Sequence
    Sequence sequence;
    for (unsigned i = 0; i < plan.duration(); ++i)
        sequence.push_back(0);

    // Estimate
    Estimator estimator(tariff_list);
    try {
        Cost price = estimator.estimate(plan, sequence);
        cout << "Total: " << price << endl;
    } catch (std::invalid_argument& e) {
        cout << e.what() << endl;
    }
}
