#pragma GCC target("avx2")

#include <iostream>

#include "pnm.h"

#define isGammaDefined (argc == 10)

int main(int argc, char** argv)
{
    if (argc != 9 && argc != 10)
    {
        std::cerr << "Incorrect number of command line arguments!\nArguments format: "
                     "./lab2 <input path> <output path> <brightness> <thickness> "
                     "<x begin> <y begin> <x end> <y end> <gamma (optional)>";
        std::cerr << std::endl;
        return 0;
    }

    std::string inputPath = argv[1], outputPath = argv[2];
    unsigned char brightness = std::stoi(argv[3]);
    float thickness = std::stof(argv[4]);
    float xBegin = std::stof(argv[5]), yBegin = std::stof(argv[6]);
    float xEnd = std::stof(argv[7]), yEnd = std::stof(argv[8]);
    float gamma = 2.2;
    if (isGammaDefined)
        gamma = std::stof(argv[9]);

    PNM img;

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

    try
    {
        isGammaDefined ?
            img.drawLine(xBegin, yBegin, xEnd, yEnd, brightness, thickness, gamma) :
            img.drawLine(xBegin, yBegin, xEnd, yEnd, brightness, thickness);
    }
    catch (std::exception& e)
    {
        std::cerr << "Failed to draw a line: " << e.what() << std::endl;
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
