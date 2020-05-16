#include "pnm.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

#define MAX_VALUE 255
#define area width * height

PNM::PNM() : height(0), width(0), image(nullptr), colorSpace(RGB), color(false) {}

PNM::~PNM() { delete[] image; }

void PNM::read(const std::string& filename)
{
    std::ifstream in;
    in.open(filename, std::ios_base::in | std::ios_base::binary);
    if ( !in.is_open() )
        throw std::runtime_error("File error!");
    std::string header;
    in >> header;
    if (header == "P5")
        color = false;
    else if (header == "P6")
        color = true;
    else
        throw std::runtime_error("File has wrong format!");
    in >> width >> height;
    int maxValue;
    in >> maxValue;
    if ( !in.good() )
        throw std::runtime_error("Invalid metadata!");
    if (maxValue != MAX_VALUE)
        throw std::runtime_error("Unacceptable format!");
    char partPixel;
    char* imageChar = &partPixel;
    image = new Pixel[area];
    if (image == nullptr)
        throw std::runtime_error("Out of memory!");
    in.read(imageChar, 1);
    for (int i = 0; i < area; ++i)
    {
        if (color)
        {
            in.read(imageChar, 1);
            image[i].A = *imageChar;
            in.read(imageChar, 1);
            image[i].B = *imageChar;
            in.read(imageChar, 1);
            image[i].C = *imageChar;
        }
        else
        {
            in.read(imageChar, 1);
            image[i].A = *imageChar;
            image[i].B = *imageChar;
            image[i].C = *imageChar;
        }
    }
    if ( !in.good() )
        throw std::runtime_error("Reading error!");
    in.close();
}

void PNM::write(const std::string& filename)
{
    std::ofstream output;
    output.open(filename, std::ios_base::out | std::ios_base::binary);
    if ( !output.is_open() )
        throw std::runtime_error("File writing error");
    if (color)
        output << "P6" << '\n';
    else
        output << "P5" << '\n';
    output << width << ' ' << height << '\n' << MAX_VALUE << '\n';
    char* imageChar = reinterpret_cast<char*>(image);
    if (color)
        output.write(imageChar, area * 3);
    else
        for (int i = 0; i < area; ++i)
            output.write(&imageChar[i * 3], 1);
    if ( output.fail() )
        throw std::runtime_error("File writing error");
    output.close();
}

void PNM::setColorSpace(ColorSpace other) noexcept { colorSpace = other; }

void PNM::changeBrightness(double difference, double multiple) noexcept
{
    if (color)
    {
        if (colorSpace == RGB)
        {
            for (int i = 0; i < area; ++i)
            {
                int result = static_cast<int>( ((double)image[i].A - difference) * multiple );
                if (result > 255)
                    result = 255;
                if (result < 0)
                    result = 0;
                image[i].A = result;
                result = static_cast<int>( ((double)image[i].B - difference) * multiple );
                if (result > 255)
                    result = 255;
                if (result < 0)
                    result = 0;
                image[i].B = result;
                result = static_cast<int>( ((double)image[i].C - difference) * multiple );
                if (result > 255)
                    result = 255;
                if (result < 0)
                    result = 0;
                image[i].C = result;
            }
        }
        else
        {
            for (int i = 0; i < area; ++i)
            {
                int result = static_cast<int>( ((double)image[i].A - difference) * multiple );
                if (result > 255)
                    result = 255;
                if (result < 0)
                    result = 0;
                image[i].A = result;
            }
        }
    }
    else
    {
        for (int i = 0; i < area; ++i)
        {
            int result = static_cast<int>( ((double)image[i].A - difference) * multiple );
            if (result > 255)
                result = 255;
            if (result < 0)
                result = 0;
            image[i].A = result;
            image[i].B = result;
            image[i].C = result;
        }
    }
}

void PNM::setAutoBrightness(bool type) noexcept
{
    std::vector<int> BD;
    BD = getBrightestAndDarkest(type);
    double difference = BD[1], multiple = 255.0 / ((double)BD[0] - BD[1]);
    std::cout << "Difference: " << difference << ".\nMultiple: " << multiple << ".\n";
    changeBrightness(difference, multiple);
}

std::vector<int> PNM::getBrightestAndDarkest(bool avoid) noexcept
{
    int pixels[256] = {}, brightest = 0, darkest = 0;
    for (int i = 0; i < area; ++i)
    {
        if (color && colorSpace != YCbCr601)
        {
            pixels[image[i].A]++;
            pixels[image[i].B]++;
            pixels[image[i].C]++;
        }
        else
            pixels[image[i].A]++;
    }
    if (avoid)
    {
        int numberToDel = 0, deleted = 0, positionD = 0, positionB = 255;
        if (color && colorSpace != YCbCr601)
            numberToDel = static_cast<int>( (double)area * 3 * 0.0039 );
        else
            numberToDel = static_cast<int>( (double)area * 0.0039 );
        while (deleted < numberToDel)
        {
            if (deleted % 2 == 0)
            {
                while (pixels[positionD] == 0)
                    positionD++;
                pixels[positionD]--;
                deleted++;
            }
            else
            {
                while (pixels[positionB] == 0)
                    positionB--;
                pixels[positionB]--;
                deleted++;
            }
        }
    }
    for (int i = 0; i < 256; ++i)
    {
        if (pixels[i] > 0)
        {
            darkest = i;
            break;
        }
    }
    for (int i = 255; i >= 0; --i)
    {
        if (pixels[i] > 0)
        {
            brightest = i;
            break;
        }
    }
    return {brightest, darkest};
}

