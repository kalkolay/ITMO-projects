//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_FASTALGORITHM_H
#define HW10_FASTALGORITHM_H

#pragma once

#include "AlgorithmsI.h"

class FastAlgorithm : public AlgorithmsI
{
public:
    std::string getName() const override;
    Routes getRoutes(int limit,
                     const std::vector <Point>& points, MetricsI* metric) const override;
};

#endif //HW10_FASTALGORITHM_H
