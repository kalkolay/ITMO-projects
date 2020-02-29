#pragma GCC target("avx2")

#include "pnm.h"

#include <regex>
#include <chrono>

using ms = std::chrono::milliseconds;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Incorrect number of command line arguments!\nArguments format: "
                     "./pnm <input path> <output path> <command>\n";
        std::cerr << "Commands:\n\t0 - inversion\n\t1 - horizontally mirror\n"
                     "\t2 - vertically mirror\n\t3 - rotate 90 degrees clockwise"
                     "\n\t4 - rotate 90 degrees counterclockwise\n";
        return 0;
    }

    std::string inputPath = argv[1], outputPath = argv[2];
    
    unsigned command;
    try
    {
        command = static_cast<unsigned>( std::stoi(argv[3], nullptr) );
        if (command < 0 || command > 4)
            throw std::invalid_argument("Invalid command number!\n");
    }
    catch(std::invalid_argument& e)
    {
        std::cerr << "Invalid command " << argv[3] << "!\n";
        return -2;
    }

    PNM img;
    try
    {
        auto start = std::chrono::steady_clock::now();
        img.read(inputPath);
        auto end = std::chrono::steady_clock::now();
        auto timeElapsed = end - start;
        std::cout << "Image read in " << std::chrono::duration_cast<ms>(timeElapsed).count() << "ms\n";
    }
    catch(FileFormatException& e)
    {
        std::cerr << "Unsupported PNM file format!\n";
        return -1;
    }
    catch(std::exception& e)
    {
        std::cerr << "Error while trying to read image " << inputPath << "!\n";
        return -1;
    }
    catch (std::ifstream::failure e)
    {
      std::cerr << "Exception opening/reading file\n";
    }
    img.displayImgData();

    std::cout << "Performing your command...\n";
    auto start = std::chrono::steady_clock::now();
    try
    {
        img.perform(command);
    }
    catch(PerformException& e)
    {
        std::cerr << "Failed to perform the command!" << std::endl;
        return -2;
    }
    auto end = std::chrono::steady_clock::now();
    auto timeElapsed = end - start;
    std::cout << "Done in " << std::chrono::duration_cast<ms>(timeElapsed).count() << "ms\n";

    std::cout << "Saving..." << std::endl;

    try
    {
        start = std::chrono::steady_clock::now();
        img.write(outputPath);
        end = std::chrono::steady_clock::now();
        timeElapsed = end - start;
        std::cout << "Image saved in " << std::chrono::duration_cast<ms>(timeElapsed).count() << "ms\n";
    }
    catch(FileIOException& e)
    {
        std::cerr << "Error while trying to write data to file " + outputPath << "!\n";
        return -1;
    }
    catch (std::ofstream::failure e)
    {
      std::cerr << "Exception opening/closing file\n";
    }

    std::cout << "Image saved to " << outputPath << std::endl;

    return 0;
}
