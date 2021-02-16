#pragma once

#include "ITransport.h"

namespace race_engine::entities
{
    class AirTransport : public ITransport
    {
    public:
        AirTransport() = default;
        AirTransport(std::string       name,
                     speed_t           speed,
                     distance_reduce_t distanceReducer);

        std::string GetName() override;

        double Update(double distance) override;

    private:
        std::string       m_name;
        speed_t           m_speed;
        distance_reduce_t m_distanceReducer;
    };
}