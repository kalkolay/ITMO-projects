#pragma once

#include "entities/LandTransport.h"
#include "entities/AirTransport.h"

#include "utils/Utilities.h"

namespace race_engine
{
    using namespace entities;
    using namespace utils;

    enum RaceType
    {
        LandTransportOnly,
        AirTransportOnly,
        LandAndAirTransport
    };

    class Race
    {
    public:
        explicit Race(unsigned type);

        void RegisterTransport(const LandTransport& landTransport);
        void RegisterTransport(const AirTransport&   airTransport);

        std::variant<LandTransport, AirTransport> StartRace(double distance);

    private:
        unsigned                   m_raceType;
        std::vector<LandTransport> m_landTransport;
        std::vector<AirTransport>  m_airTransport;
    };
}