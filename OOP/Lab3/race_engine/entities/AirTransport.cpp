#include "AirTransport.h"

#include <utility>

namespace race_engine::entities
{
    AirTransport::AirTransport(std::string       name,
                               speed_t           speed,
                               distance_reduce_t distanceReducer)
        : m_name           ( std::move(name) ),
          m_speed          (speed),
          m_distanceReducer( std::move(distanceReducer) )
    {}

    std::string AirTransport::GetName()
    {
        return m_name;
    }

    double AirTransport::Update(double distance)
    {
        double currentDistance = distance * (1. - m_distanceReducer(distance) / 100.);
        double totalTime = currentDistance / m_speed;
        return totalTime;
    }
}