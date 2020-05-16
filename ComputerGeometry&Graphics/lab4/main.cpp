#pragma GCC target("avx2")

#include <iostream>

#include "pnm.h"

int main(int argc, char** argv)
{
    PNM img;
    ColorSpace conversion = RGB;
    bool manyInput = false, manyOutput = false;
    std::string inName, outName, buffer;

    if (argc != 11)
    {
        std::cerr << "Wrong amount of arguments!";
        return 1;
    }

    for (int position = 1; position < argc; ++position)
    {
        buffer = argv[position];
        if (buffer == "-f")
        {
            position++;
            buffer = argv[position];
            if (buffer == "RGB")
            {
                img.setColorSpace(RGB);
                continue;
            }
            if (buffer =="HSL")
            {
                img.setColorSpace(HSL);
                continue;
            }
            if (buffer == "HSV")
            {
                img.setColorSpace(HSV);
                continue;
            }
            if (buffer == "YCbCr.601")
            {
                img.setColorSpace(YCbCr_601);
                continue;
            }
            if (buffer == "YCbCr.709")
            {
                img.setColorSpace(YCbCr_709);
                continue;
            }
            if (buffer == "YCoCg")
            {
                img.setColorSpace(YCoCg);
                continue;
            }
            if (buffer == "CMY")
            {
                img.setColorSpace(CMY);
                continue;
            }
            std::cerr << "Unknown color space \""<< buffer << "\". Terminating";
            return 1;
        }
        if (buffer == "-t")
        {
            position++;
            buffer = argv[position];
            if (buffer == "RGB")
            {
                conversion = RGB;
                continue;
            }
            if (buffer == "HSL")
            {
                conversion = HSL;
                continue;
            }
            if (buffer == "HSV")
            {
                conversion = HSV;
                continue;
            }
            if (buffer == "YCbCr.601")
            {
                conversion = YCbCr_601;
                continue;
            }
            if (buffer == "YCbCr.709")
            {
                conversion = YCbCr_709;
                continue;
            }
            if (buffer == "YCoCg")
            {
                conversion = YCoCg;
                continue;
            }
            if (buffer == "CMY")
            {
                conversion = CMY;
                continue;
            }
            std::cerr << "Unknown color space \""<< buffer << "\". Terminating";
            return 1;
        }
        if (buffer == "-i")
        {
            position++;
            buffer = argv[position];
            if (buffer == "1")
                manyInput = false;
            else if (buffer == "3")
                manyInput = true;
            else
            {
                std::cerr << "Incorrect inputs count!";
                return 1;
            }
            position++;
            buffer = argv[position];
            inName = buffer;
            continue;
        }
        if (buffer == "-o")
        {
            position++;
            buffer = argv[position];
            if (buffer == "1")
                manyOutput = false;
            else if (buffer == "3")
                manyOutput = true;
            else
            {
                std::cerr << "Incorrect outputs count!";
                return 1;
            }
            position++;
            buffer = argv[position];
            outName = buffer;
            continue;
        }
    }

    try
    {
        if (manyInput)
            img.readPgm(inName);
        else
            img.readPpm(inName);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    img.convertColorSpace(conversion);

    try
    {
        if (manyOutput)
            img.writePgm(outName);
        else
            img.writePpm(outName);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
