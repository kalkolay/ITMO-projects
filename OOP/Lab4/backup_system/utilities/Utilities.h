#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

namespace backup::utils
{
    template <typename TP>
    std::time_t to_time_t(TP tp)
    {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                            + system_clock::now());
        return system_clock::to_time_t(sctp);
    }

    template <typename T>
    std::string time_to_string(T time)
    {
        std::time_t tt       = to_time_t(time);
        std::tm*    gmt      = std::gmtime(&tt);
        std::stringstream buffer;
        buffer << std::put_time(gmt, "%A, %d %B %Y %H:%M");
        return buffer.str();
    }

    template <typename T>
    std::vector<T> find_intersection(std::vector<T> v1, std::vector<T> v2)
    {
        std::sort( v1.begin(), v1.end() );
        std::sort( v2.begin(), v2.end() );

        std::vector<T> v_intersection;

        std::set_intersection( v1.begin(), v1.end(),
                               v2.begin(), v2.end(),
                               std::back_inserter(v_intersection) );
        return v_intersection;
    };
}