//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_ENUMERATIONALGORITHM_H
#define HW10_ENUMERATIONALGORITHM_H

#pragma once

#include "AlgorithmsI.h"

class EnumerationAlgorithm : public AlgorithmsI
{
public:
    std::string getName() const override;
    Routes getRoutes(int limit,
                     const std::vector <Point>& points, MetricsI* metric) const override;
};

#endif //HW10_ENUMERATIONALGORITHM_H
