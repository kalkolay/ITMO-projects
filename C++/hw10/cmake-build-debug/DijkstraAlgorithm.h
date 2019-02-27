//
// Created by kalkolay on 2/25/19.
//

#ifndef HW10_DIJKSTRAALGORITHM_H
#define HW10_DIJKSTRAALGORITHM_H

#pragma once

#include "AlgorithmsI.h"

class DijkstraAlgorithm : public AlgorithmsI
{
	public:
		std::string getName() const override;
		Routes getRoutes(int limit,
		const std::vector <Point>& points, MetricsI* metric) const override;
};

#endif //HW10_DIJKSTRAALGORITHM_H
