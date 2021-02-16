#pragma once

#include <vector>
#include <limits>
#include <type_traits>
#include <variant>

#include "../entities/LandTransport.h"
#include "../entities/AirTransport.h"

namespace utils
{
    using namespace race_engine::entities;

    template <typename T>
    static constexpr bool is_land_or_air_transport_v =
            std::is_same<T, LandTransport>::value || std::is_same<T, AirTransport>::value;

    template < typename T, class = std::enable_if_t< !is_land_or_air_transport_v<T> > >
    inline T FindFastestTransport(std::vector<T>& transports,
                                  double          distance) = delete;

    template <typename T>
    inline T FindFastestTransport(std::vector<T>& transports,
                                  double          distance)
    {
        T ans;
        double minTime = std::numeric_limits<double>::max();
        for (auto transport : transports)
        {
            if (transport.Update(distance) < minTime)
            {
                minTime = transport.Update(distance);
                ans = transport;
            }
        }
        return ans;
    }
}