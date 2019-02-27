cmake_minimum_required(VERSION 3.13)
project(hw10)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw10 main.cpp cmake-build-debug/DijkstraAlgorithm.cpp cmake-build-debug/DijkstraAlgorithm.h cmake-build-debug/ChebyshevMetric.cpp cmake-build-debug/ChebyshevMetric.h cmake-build-debug/EnumerationAlgorithm.cpp cmake-build-debug/EnumerationAlgorithm.h cmake-build-debug/EuclideanMetric.cpp cmake-build-debug/EuclideanMetric.h cmake-build-debug/FastAlgorithm.cpp cmake-build-debug/FastAlgorithm.h cmake-build-debug/ManhattanMetric.cpp cmake-build-debug/ManhattanMetric.h cmake-build-debug/MetricsI.h cmake-build-debug/AlgorithmsI.h cmake-build-debug/Point.h)