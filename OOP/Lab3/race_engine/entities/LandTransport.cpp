#include "LandTransport.h"

#include <utility>
#include <cmath>

namespace race_engine::entities
{
    LandTransport::LandTransport(std::string     name,
                                 speed_t         speed,
                                 rest_interval_t restInterval,
                                 rest_duration_t restDuration)
        : m_name        ( std::move(name) ),
          m_speed       (speed),
          m_restInterval(restInterval),
          m_restDuration( std::move(restDuration) )
    {}

    std::string LandTransport::GetName()
    {
        return m_name;
    }

    double LandTransport::Update(double distance)
    {
        double totalTime = 0;
        size_t iteration = 0;
        while (distance > 0)
        {
            distance  -= static_cast<double>(m_speed) * m_restInterval;
            totalTime += m_restInterval + m_restDuration(iteration);
            ++iteration;
        }
        totalTime -= std::abs(distance) / m_speed - m_restDuration(--iteration);
        return totalTime;
    }
}