#include <cstdlib>
#include <iostream>
#include <string>
#include "io/plan.hpp"
#include "io/tariff.hpp"
#include "plan.hpp"
#include "planner/all.hpp"
#include "sequence.hpp"
#include "tariff.hpp"
#include "utils.hpp"

static void usage(const std::string& name);

static Plan read_plan(const std::string& name);
static TariffList read_tariff_list(const std::string& name);

int main(int argc, char** argv) {
    if (argc < 3)
        usage(argv[0]);

    // Read tariff list
    TariffList tariff_list = read_tariff_list(argv[1]);

    // Read plan
    Plan plan = read_plan(argv[2]);
    std::cout << "Plan:" << std::endl
              << plan << std::endl;

    // Output
    std::ostream *output = &std::cout;
    std::fstream output_file;
    if (argc > 3) {
        output_file = open_file(argv[3], std::ios_base::out);
        output = &output_file;
    }

    // Create tariff sequence
    PlannerBF planner(tariff_list);
    Planner::Result result = planner.plan(plan);

    // Output result
    *output << "Tariff sequence:" << std::endl;
    print_sequence(*output, tariff_list, result.sequence);
    *output << "Total price: " << result.price << std::endl;
}


void usage(const std::string& name) {
    std::cout << "Usage:" << std::endl
              << " $ " << name
              << " <tariff-list-filename>"
              << " <plan-filename>"
              << std::endl;
    std::exit(EXIT_FAILURE);
}

Plan read_plan(const std::string& name) {
    std::fstream is = open_file(name);
    return io::read_plan(is);
}

TariffList read_tariff_list(const std::string& name) {
    std::fstream is = open_file(name);
    return io::read_tariff_list(is);
}
