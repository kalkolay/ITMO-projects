#pragma once

#include "ITransport.h"

namespace race_engine::entities
{
    class LandTransport : public ITransport
    {
    public:
        LandTransport() = default;
        LandTransport(std::string     name,
                      speed_t         speed,
                      rest_interval_t restInterval,
                      rest_duration_t restDuration);

        std::string GetName() override;

        double Update(double distance) override;

    private:
        std::string     m_name;
        speed_t         m_speed;
        rest_interval_t m_restInterval;
        rest_duration_t m_restDuration;
    };
}

