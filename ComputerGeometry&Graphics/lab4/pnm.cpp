#include "pnm.h"

#include <fstream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#define MAX_VALUE 255
#define area width * height

PNM::PNM() : height(0), width(0), image(nullptr), colorSpace(ColorSpace::RGB) {}

PNM::~PNM() { delete[] image; }

void PNM::readPpm(const std::string& filename)
{
    std::ifstream in;
    in.open(filename, std::ios_base::in | std::ios_base::binary);
    if ( !in.is_open() )
        throw std::runtime_error("PPM file error!");
    std::string header;
    in >> header;
    if (header != "P6")
        throw std::runtime_error("Current PPM file is not P6 format!");
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
        in.read(imageChar, 1);
        image[i].A = *imageChar;
        in.read(imageChar, 1);
        image[i].B = *imageChar;
        in.read(imageChar, 1);
        image[i].C = *imageChar;
    }
    if ( !in.good() )
        throw std::runtime_error("Reading error!");
    in.close();
}

void PNM::writePpm(const std::string& filename)
{
    std::ofstream output;
    output.open(filename, std::ios_base::out | std::ios_base::binary);
    if ( !output.is_open() )
        throw std::runtime_error("File writing error!");
    output << "P6" << '\n';
    output << width << ' ' << height << '\n' << MAX_VALUE << '\n';
    char* imageChar = reinterpret_cast<char*>(image);
    output.write(imageChar, area * 3);
    if ( output.fail() )
        throw std::runtime_error("File writing error!");
    output.close();
}

void PNM::readPgm(std::string filename)
{
    std::ifstream firstIn, secondIn, thirdIn;
    filename.insert(filename.size() - 4, "_1");
    firstIn.open(filename, std::ios_base::in | std::ios_base::binary);
    if ( !firstIn.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);
    filename.replace(filename.size() - 5, 1, "2");
    secondIn.open(filename, std::ios_base::in | std::ios_base::binary);
    if ( !secondIn.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);
    filename.replace(filename.size() - 5, 1, "3");
    thirdIn.open(filename, std::ios_base::in | std::ios_base::binary);
    if ( !thirdIn.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);

    std::string firstHeader, secondHeader, thirdHeader;
    firstIn >> firstHeader;
    secondIn >> secondHeader;
    thirdIn >> thirdHeader;
    if (firstHeader != secondHeader || secondHeader != thirdHeader || thirdHeader != "P5")
        throw std::runtime_error("One or more files aren't P5 format!");

    firstIn >> width >> height;
    int secondWidth, secondHeight, thirdWidth, thirdHeight;
    secondIn >> secondWidth >> secondHeight;
    if (secondWidth != width || secondHeight != height)
        throw std::runtime_error("Files have different formats!");
    thirdIn >> thirdWidth >> thirdHeight;
    if (thirdWidth != width || thirdHeight != height)
        throw std::runtime_error("Files have different formats!");

    int maxValue;
    firstIn >> maxValue;
    if (maxValue != MAX_VALUE)
        throw std::runtime_error("Invalid metadata!");
    secondIn >> maxValue;
    if (maxValue != MAX_VALUE)
        throw std::runtime_error("Invalid metadata!");
    thirdIn >> maxValue;
    if (maxValue != MAX_VALUE)
        throw std::runtime_error("Invalid metadata!");
    if ( !firstIn.good() || !secondIn.good() || !thirdIn.good() )
        throw std::runtime_error("Reading error!");
    char partPixel;
    char* imageChar = &partPixel;
    image = new Pixel[area];
    if (image == nullptr)
        throw std::runtime_error("Out of memory!");
    firstIn.read(imageChar, 1);
    secondIn.read(imageChar, 1);
    thirdIn.read(imageChar, 1);
    for (int i = 0; i < area; ++i)
    {
        firstIn.read(imageChar, 1);
        image[i].A = *imageChar;
        secondIn.read(imageChar, 1);
        image[i].B = *imageChar;
        thirdIn.read(imageChar, 1);
        image[i].C = *imageChar;
    }
    if ( !firstIn.good() || !secondIn.good() || !thirdIn.good() )
        throw std::runtime_error("Reading error!");
}

void PNM::writePgm(std::string filename)
{
    std::ofstream firstOut, secondOut, thirdOut;
    filename.insert(filename.size() - 4, "_1");
    firstOut.open(filename, std::ios_base::out | std::ios_base::binary);
    if ( !firstOut.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);
    filename.replace(filename.size() - 5, 1, "2");
    secondOut.open(filename, std::ios_base::out | std::ios_base::binary);
    if ( !secondOut.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);
    filename.replace(filename.size() - 5, 1, "3");
    thirdOut.open(filename, std::ios_base::out | std::ios_base::binary);
    if ( !thirdOut.is_open() )
        throw std::runtime_error("Problem opening file:" + filename);

    firstOut << "P5" << '\n';
    firstOut << width << ' ' << height << '\n' << MAX_VALUE << '\n';
    secondOut << "P5" << '\n';
    secondOut << width << ' ' << height << '\n' << MAX_VALUE << '\n';
    thirdOut << "P5" << '\n';
    thirdOut << width << ' ' << height << '\n' << MAX_VALUE << '\n';

    if ( !firstOut.good() || !secondOut.good() || !thirdOut.good() )
        throw std::runtime_error("File writing error!");
    for (int i = 0; i < area; ++i)
    {
        firstOut.write(reinterpret_cast<char*>(&image[i].A), 1);
        secondOut.write(reinterpret_cast<char*>(&image[i].B), 1);
        thirdOut.write(reinterpret_cast<char*>(&image[i].C), 1);
    }
    if ( !firstOut.good() || !secondOut.good() || !thirdOut.good() )
        throw std::runtime_error("File writing error!");
}

void PNM::setColorSpace(ColorSpace other) noexcept { colorSpace = other; }

void PNM::convertColorSpace(ColorSpace convert) noexcept
{
    if (colorSpace == convert)
        return;
    convertRgb();
    if (convert == RGB)
        return;
    double Max, Min, H, S = 0, L, C, V, M;
    double Y, Cb, Cr, Co, Cg, Kr, Kg, Kb, R, G, B;
    switch (convert)
    {
        case HSL:
        case HSV:
            for (int i = 0; i < area; ++i)
            {
                R = image[i].A / 255.0;
                G = image[i].B / 255.0;
                B = image[i].C / 255.0;
                Max = std::max(R, std::max(G, B));
                Min = std::min(R, std::min(G, B));
                V = Max;
                C = Max - Min;
                L = V - C / 2.0;
                if (C == 0)
                    H = 0;
                else
                {
                    if (V == R)
                        H = (60.0) * ((G - B) / C);
                    else if (V == G)
                        H = (60.0) * (2 + (B - R) / C);
                    else if (V == B)
                        H = (60.0) * (4 + (R - G) / C);
                    else
                        H = 0;
                }
                if (convert == HSV)
                {
                    S = (V == 0) ? 0 : C / V;
                    image[i].C = static_cast<unsigned char>(V * 255.0);
                }
                if (convert == HSL)
                {
                    S = (L == 0 || L == 1) ? 0 : ((V - L) / std::min(L, 1 - L));
                    image[i].C = static_cast<unsigned char>(L * 255.0);
                }
                image[i].B = static_cast<unsigned char>(S * 255.0);
                image[i].A = static_cast<unsigned char>((H / 360.0) * 255.0);

            }
            colorSpace = convert;
            break;
        case YCbCr_601:
        case YCbCr_709:
            if (convert == YCbCr_601)
            {
                Kr = 0.299;
                Kg = 0.587;
                Kb = 0.114;
                colorSpace = YCbCr_601;
            }
            else
            {
                Kr = 0.0722;
                Kg = 0.2126;
                Kb = 0.7152;
                colorSpace = YCbCr_709;
            }
            for (int i = 0; i < area; ++i)
            {
                R = image[i].A / 255.0;
                G = image[i].B / 255.0;
                B = image[i].C / 255.0;
                Y = Kr * R + Kg * G + Kb * B;
                Cb = 0.5 * ((B - Y) / (1.0 - Kb));
                Cr = 0.5 * ((R - Y) / (1.0 - Kr));
                image[i].A = static_cast<unsigned char>(Y * 255.0);
                image[i].B = static_cast<unsigned char>((Cb + 0.5) * 255.0);
                image[i].C = static_cast<unsigned char>((Cr + 0.5) * 255.0);
            }
            break;
        case YCoCg:
            for (int i = 0; i < area; ++i)
            {
                R = image[i].A / 255.0;
                G = image[i].B / 255.0;
                B = image[i].C / 255.0;
                Y = R / 4 + G / 2 + B / 4;
                Co = R / 2 - B / 2;
                Cg = -R / 4 + G / 2 - B / 4;
                image[i].A = static_cast<unsigned char>(Y * 255.0);
                image[i].B = static_cast<unsigned char>((Co + 0.5) * 255.0);
                image[i].C = static_cast<unsigned char>((Cg + 0.5) * 255.0);
            }
            colorSpace = YCoCg;
            break;
        case CMY:
            for (int i = 0; i < area; ++i)
            {
                R = image[i].A / 255.0;
                G = image[i].B / 255.0;
                B = image[i].C / 255.0;
                C = 1 - R;
                M = 1 - G;
                Y = 1 - B;
                image[i].A = static_cast<unsigned char>(C * 255.0);
                image[i].B = static_cast<unsigned char>(M * 255.0);
                image[i].C = static_cast<unsigned char>(Y * 255.0);
            }
            colorSpace = CMY;
            break;
        default:
            break;
    }
}

void PNM::convertRgb() noexcept
{
    double H, S, L, C, H_D, X, m, R, G, B, Y, Cb, Cr, Co, Cg, M, Kr, Kg, Kb;
    if (colorSpace == RGB)
        return;
    switch (colorSpace)
    {
        case HSL:
        case HSV:
            for (int i = 0; i < area; ++i)
            {
                H = (image[i].A / 255.0) * 360.0;
                S = image[i].B / 255.0;
                L = image[i].C / 255.0;
                H_D = H / 60;
                if (colorSpace == HSL)
                {
                    C = (1 - abs(2 * L - 1)) * S;
                    X = C * (1 - abs(fmod(H_D, 2) - 1));
                    m = L - C / 2.0;
                }
                else
                {
                    C = S * L;
                    X = C * (1.0 - abs(fmod(H_D, 2) - 1.0));
                    m = L - C;
                }

                m *= 255.0;
                if (H_D >= 0 && H_D <= 1)
                {
                    image[i].A = static_cast<unsigned char>(C * 255.0 + m);
                    image[i].B = static_cast<unsigned char>(X * 255.0 + m);
                    image[i].C = static_cast<unsigned char>(m);
                }
                if (H_D > 1 && H_D <= 2)
                {
                    image[i].A = static_cast<unsigned char>(X * 255.0 + m);
                    image[i].B = static_cast<unsigned char>(C * 255.0 + m);
                    image[i].C = static_cast<unsigned char>(m);
                }
                if (H_D > 2 && H_D <= 3)
                {
                    image[i].A = static_cast<unsigned char>(m);
                    image[i].B = static_cast<unsigned char>(C * 255.0 + m);
                    image[i].C = static_cast<unsigned char>(X * 255.0 + m);
                }
                if (H_D > 3 && H_D <= 4)
                {
                    image[i].A = static_cast<unsigned char>(m);
                    image[i].B = static_cast<unsigned char>(X * 255.0 + m);
                    image[i].C = static_cast<unsigned char>(C * 255.0 + m);
                }
                if (H_D > 4 && H_D <= 5)
                {
                    image[i].A = static_cast<unsigned char>(X * 255.0 + m);
                    image[i].B = static_cast<unsigned char>(m);
                    image[i].C = static_cast<unsigned char>(C * 255.0 + m);
                }
                if (H_D > 5 && H_D <= 6)
                {
                    image[i].A = static_cast<unsigned char>(C * 255.0 + m);
                    image[i].B = static_cast<unsigned char>(m);
                    image[i].C = static_cast<unsigned char>(X * 255.0 + m);
                }

            }
            break;
        case YCbCr_601:
        case YCbCr_709:
            if (colorSpace == YCbCr_601)
            {
                Kr = 0.299;
                Kg = 0.587;
                Kb = 0.114;
            }
            else
            {
                Kr = 0.0722;
                Kg = 0.2126;
                Kb = 0.7152;
            }
            for (int i = 0; i < area; ++i)
            {
                Y = image[i].A / 255.0;
                Cb = (image[i].B / 255.0) - 0.5;
                Cr = (image[i].C / 255.0) - 0.5;
                R = (Y + Cr * (2.0 - 2.0 * Kr));
                G = (Y - (Kb / Kg) * (2.0 - 2.0 * Kb) * Cb - (Kr / Kg) * (2.0 - 2.0 * Kr) * Cr);
                B = (Y + (2.0 - 2.0 * Kb) * Cb);
                if (R < 0)
                    R = 0;
                if (G < 0)
                    G = 0;
                if (B < 0)
                    B = 0;
                if (R > 1)
                    R = 1;
                if (G > 1)
                    G = 1;
                if (B > 1)
                    B = 1;
                image[i].A = static_cast<unsigned char>(R * 255.0);
                image[i].B = static_cast<unsigned char>(G * 255.0);
                image[i].C = static_cast<unsigned char>(B * 255.0);
            }
            break;
        case YCoCg:
            for (int i = 0; i < area; ++i)
            {
                Y = image[i].A / 255.0;
                Co = (image[i].B / 255.0) - 0.5;
                Cg = (image[i].C / 255.0) - 0.5;
                R = Y + Co - Cg;
                G = Y + Cg;
                B = Y - Co - Cg;
                if (R < 0)
                    R = 0;
                if (G < 0)
                    G = 0;
                if (B < 0)
                    B = 0;
                if (R > 1)
                    R = 1;
                if (G > 1)
                    G = 1;
                if (B > 1)
                    B = 1;
                image[i].A = static_cast<unsigned char>(R * 255.0);
                image[i].B = static_cast<unsigned char>(G * 255.0);
                image[i].C = static_cast<unsigned char>(B * 255.0);
            }
            break;
        case CMY:
            for (int i = 0; i < area; ++i)
            {
                C = image[i].A / 255.0;
                M = image[i].B / 255.0;
                Y = image[i].C / 255.0;
                R = 1 - C;
                G = 1 - M;
                B = 1 - Y;
                image[i].A = static_cast<unsigned char>(R * 255.0);
                image[i].B = static_cast<unsigned char>(G * 255.0);
                image[i].C = static_cast<unsigned char>(B * 255.0);
            }
            break;
        default:
            break;
    }
    colorSpace = RGB;
}