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
    std::cout << plan << std::endl;

    PlannerBF planner(tariff_list);
    Sequence sequence = planner.plan(plan);

    print_sequence(std::cout, tariff_list, sequence);
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
