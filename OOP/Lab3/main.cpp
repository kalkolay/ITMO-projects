#include <iostream>

#include "race_engine/Race.h"

using namespace race_engine;

int main()
{
    LandTransport bactrianCamel( "двугорбый верблюд", 10, 30,
            [](size_t i) { return (!i ? 5. : 8.); } );
    LandTransport fastCamel( "верблюд-быстроход", 40, 10,
            [](size_t i) {
                switch(i)
                {
                    case 0:
                        return 5.;
                    case 1:
                        return 6.5;
                    default:
                        return 8.;
                }
    } );
    LandTransport centaur( "кентавр", 15, 8,
            [](size_t i) { return 2.; } );
    LandTransport allTerrainBoots( "ботинки-вездеходы", 6, 60,
            [](size_t i) { return (!i ? 10. : 5.); } );

    AirTransport magicCarpet( "ковёр-самолёт", 10,
            [](double distance) {
                if (distance < 1000)
                    return 0.;
                else if (distance < 5000)
                    return 3.;
                else if (distance < 10000)
                    return 10.;
                else
                    return 5.;
    } );
    AirTransport mortar( "ступа", 8,
            [](double distance) { return 6.; } );
    AirTransport broom( "метла", 20,
            [](double distance) { return distance /= 1000; } );

    Race race(LandAndAirTransport);
    race.RegisterTransport(bactrianCamel);
    race.RegisterTransport(fastCamel);
    race.RegisterTransport(centaur);
    race.RegisterTransport(allTerrainBoots);
    race.RegisterTransport(magicCarpet);
    race.RegisterTransport(mortar);
    race.RegisterTransport(broom);

    std::variant<LandTransport, AirTransport> winner = race.StartRace(100000);
    if ( std::holds_alternative<LandTransport>(winner) )
    {
        LandTransport ans = std::get<LandTransport>(winner);
        std::cout << "LandTransport won! Winner's name: " << ans.GetName() << std::endl;
    }
    else if ( std::holds_alternative<AirTransport>(winner) )
    {
        AirTransport ans = std::get<AirTransport>(winner);
        std::cout << "AirTransport won! Winner's name: " << ans.GetName() << std::endl;
    }

    return 0;
}
