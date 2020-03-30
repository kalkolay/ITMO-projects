#pragma GCC target("avx2")

#include <iostream>

#include "pnm.h"

int main(int argc, char** argv)
{
    if (argc != 7)
    {
        std::cerr << "Incorrect number of command line arguments!\nArguments format: "
                     "./lab3 <input path> <output path> <gradient> <dithering> <color depth> <gamma>";
        std::cerr << std::endl;
        return 0;
    }

    std::string inputPath = argv[1], outputPath = argv[2];
    bool gradient = std::stoi(argv[3]);

    unsigned dithering;
    try
    {
        dithering = static_cast<unsigned>( std::stoi(argv[4], nullptr) );
        if (dithering < 0 || dithering > 7)
            throw std::invalid_argument("Invalid dithering type!\n");
    }
    catch(std::invalid_argument& e)
    {
        std::cerr << "Invalid dithering type " << argv[4] << "!\n";
        return 1;
    }

    unsigned colorDepth = std::stoi(argv[5]);
    float gamma = std::stof(argv[6]);

    PNM img;
    img.setCorrection(gamma);

    try
    {
        img.read(inputPath);
    }
    catch (FileIOException&)
    {
        std::cerr << "Error while trying to read file " << inputPath << '.' << std::endl;
        return 1;
    }
    catch (FileFormatException& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (gradient)
        img.fill();

    try
    {
        img.dither(dithering, colorDepth);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    try
    {
        img.write(outputPath);
    }
    catch (FileIOException&)
    {
        std::cerr << "Error while trying to write data to file " << outputPath << '.' << std::endl;
        return 1;
    }

    return 0;
}