#include "cmake-build-debug/ChebyshevMetric.h"
#include "cmake-build-debug/ManhattanMetric.h"
#include "cmake-build-debug/EuclideanMetric.h"
#include "cmake-build-debug/EnumerationAlgorithm.h"
#include "cmake-build-debug/DijkstraAlgorithm.h"
#include "cmake-build-debug/FastAlgorithm.h"

#include <iostream>

int main()
{
    std::cout << "Enter number of algorithm:\n" <<
              "1. Enumeration\n2. Fast\n3. Dijkstra\n";
    unsigned short input;
    std::cin >> input;
    AlgorithmsI* algorithm = nullptr;
    switch (input)
    {
        case 1:
            algorithm = new EnumerationAlgorithm();
            break;
        case 2:
            algorithm = new FastAlgorithm();
            break;
        case 3:
            algorithm = new DijkstraAlgorithm();
            break;
        default:
            std::cout << "Incorrect input\n";
            return 0;
    }
    std::cout << "Enter number of metric:\n" <<
              "1. Chebyshev\n2. Manhattan\n3. Euclidean\n";
    std::cin >> input;
    MetricsI* metric = nullptr;
    switch (input)
    {
        case 1:
            metric = new ChebyshevMetric();
            break;
        case 2:
            metric = new ManhattanMetric();
            break;
        case 3:
            metric = new EuclideanMetric();
            break;
        default:
            std::cout << "Incorrect input\n";
            return 0;
    }
    std::cout << "Enter amount of points and limit\n";
    int size, limit;
    std::cin >> size >> limit;
    std::cout << "Enter the points\n";
    std::vector<Point> points;
    for (int i = 0; i < size; ++i)
    {
        double first, second;
        std::cin >> first >> second;
        points.push_back(Point(first, second));
    }
    Routes answer = algorithm -> getRoutes(limit, points, metric);
    for (int i = 0; i < answer.size(); ++i)
    {
        std::cout << "Route " << i + 1 << ":\n";
        for (auto j : answer[i])
            std::cout << '{' << j.x << ',' << j.y << "}\n";
        std::cout << '\n';
    }
}