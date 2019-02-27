//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_ALGORITHMSI_H
#define HW10_ALGORITHMSI_H

#pragma once

#include "MetricsI.h"

#include <vector>

#define Routes std::vector<std::vector<Point>>

class AlgorithmsI
{
public:
    virtual std::string getName() const = 0;
    virtual Routes getRoutes(int limit,
                             const std::vector <Point>& points, MetricsI* metric) const = 0;
};

#endif //HW10_ALGORITHMSI_H
