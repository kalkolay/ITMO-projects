#include "Race.h"

#include "exceptions/TransportTypeException.h"
#include "exceptions/RaceTypeException.h"

namespace race_engine
{
    Race::Race(unsigned type)
        : m_raceType(type)
    {}

    void Race::RegisterTransport(const LandTransport& transport)
    {
        switch (m_raceType)
        {
            case LandTransportOnly:
            case LandAndAirTransport:
                m_landTransport.push_back(transport);
                break;
            case AirTransportOnly:
                throw exceptions::TransportTypeException("Incompatible transport type.");
            default:
                throw exceptions::RaceTypeException("Incompatible race type.");
        }
    }

    void Race::RegisterTransport(const AirTransport& transport)
    {
        switch (m_raceType)
        {
            case AirTransportOnly:
            case LandAndAirTransport:
                m_airTransport.push_back(transport);
                break;
            case LandTransportOnly:
                throw exceptions::TransportTypeException("Incompatible transport type.");
            default:
                throw exceptions::RaceTypeException("Incompatible race type.");
        }
    }

    std::variant<LandTransport, AirTransport> Race::StartRace(double distance)
    {
        std::variant<LandTransport, AirTransport> ans;
        LandTransport land;
        AirTransport  air;
        switch (m_raceType)
        {
            case LandTransportOnly:
                ans = FindFastestTransport<LandTransport>(m_landTransport, distance);
                break;
            case AirTransportOnly:
                ans = FindFastestTransport<AirTransport>(m_airTransport, distance);
                break;
            case LandAndAirTransport:
                land = FindFastestTransport<LandTransport>(m_landTransport, distance);
                air  = FindFastestTransport<AirTransport> (m_airTransport,  distance);
                land.Update(distance) < air.Update(distance) ? ans = land : ans = air;
                break;
            default:
                throw exceptions::RaceTypeException("Incompatible race type.");
        }
        return ans;
    }
}