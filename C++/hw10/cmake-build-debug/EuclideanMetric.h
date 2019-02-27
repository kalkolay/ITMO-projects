//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_EUCLIDEANMETRIC_H
#define HW10_EUCLIDEANMETRIC_H

#pragma once

#include "MetricsI.h"

class EuclideanMetric : public MetricsI
{
public:
    std::string getName() const override;
    double calcDistance(const Point& first, const Point& second) const override;
};

#endif //HW10_EUCLIDEANMETRIC_H
