//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_METRICSI_H
#define HW10_METRICSI_H

#pragma once

#include "Point.h"
#include <string>

class MetricsI
{
public:
    virtual std::string getName() const = 0;
    virtual double calcDistance(const Point& first, const Point& second) const = 0;
};

#endif //HW10_METRICSI_H
