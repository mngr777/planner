#ifndef ESTIMATOR_HPP_
#define ESTIMATOR_HPP_

#include "plan.hpp"
#include "sequence.hpp"
#include "tariff.hpp"

class Estimator {
public:
    Estimator(TariffList& tariff_list)
        : tariff_list_(tariff_list) {}

    Cost estimate(const Plan& plan, const Sequence& sequence) const;

private:
    TariffList& tariff_list_;
};

#endif
