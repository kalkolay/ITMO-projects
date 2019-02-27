//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_MANHATTANMETRIC_H
#define HW10_MANHATTANMETRIC_H

#pragma once

#include "MetricsI.h"

class ManhattanMetric : public MetricsI
{
public:
    std::string getName() const override;
    double calcDistance(const Point& first, const Point& second) const override;
};

#endif //HW10_MANHATTANMETRIC_H
