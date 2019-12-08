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
    plan.add(2 * 60, 15);
    plan.add(30, 25);
    plan.add(100, 10);

    cout << plan << endl;

    // Brute force planning
    PlannerBF planner_bf(tariff_list);
    Sequence sequence = planner_bf.plan(plan);
    print_sequence(std::cout, tariff_list, sequence);

    // Estimate
    Estimator estimator(tariff_list);
    Cost price = estimator.estimate(plan, sequence);
    cout << "Total price: " << price << endl;

    cout << estimator.estimate(plan, {3}) << std::endl;
}
