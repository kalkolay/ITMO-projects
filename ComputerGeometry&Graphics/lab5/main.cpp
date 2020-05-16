#pragma GCC target("avx2")

#include <iostream>
#include <cstdlib>

#include "pnm.h"

int main(int argc, char** argv)
{
    std::string inName, outName;
    Conversion conversion;
    double difference = 0, multiple = 0;
    char* end;

    if (argc < 4)
    {
        std::cerr << "Wrong amount of arguments!";
        return 1;
    }

    inName = argv[1];
    outName = argv[2];
    if (std::strtol(argv[3], &end, 10) < 0 || std::strtol(argv[3], &end, 10) > 6)
    {
        std::cerr << "Incorrect conversion!";
        return 1;
    }

    conversion = static_cast<Conversion>( std::strtol(argv[3], &end, 10) );
    if (conversion == RGB_SET || conversion == YCBCR_SET)
    {
        if (argc != 6)
        {
            std::cerr << "Not enough parameters for conversion!";
            return 1;
        }
        difference = static_cast<double>( std::strtol(argv[4], &end, 10) );
        multiple = static_cast<double>( std::strtol(argv[5], &end, 10) );
    }

    PNM img;
    if (conversion == YCBCR_SET || conversion == YCBCR_AUTO || conversion == YCBCR_AUTO_SIMPLE)
        img.setColorSpace(YCbCr601);
    try
    {
        img.read(inName);
        if (conversion == RGB_SET || conversion == YCBCR_SET)
            img.changeBrightness(difference, multiple);
        else
            img.setAutoBrightness(conversion == RGB_AUTO || conversion == YCBCR_AUTO);
        img.write(outName);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
