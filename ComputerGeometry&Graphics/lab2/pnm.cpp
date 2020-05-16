#include "pnm.h"

#include <fstream>

#include <cmath>
#include <functional>
#include <algorithm>

#define area width * height

using Point = std::pair<float, float>;

const short PGM = 5, COLORS = 255;

PNM::PNM() = default;

void PNM::read(const std::string& fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    if ( !input.is_open() )
        throw FileIOException();

    char P;
    input >> P;
    if (P != 'P')
        throw FileFormatException();
    input >> format;
    if (format != PGM)
        throw FileFormatException();
    input >> width >> height;
    input >> colors;
    if (colors != COLORS)
        throw FileFormatException();
    input.get();

    pgm.resize(area);
    input.read(reinterpret_cast<char*>(&pgm[0]), area);
    if ( input.fail() )
        throw FileIOException();

    input.close();
}

void PNM::write(const std::string& fileName)
{
    std::ofstream output(fileName, std::ios::binary);
    if ( !output.is_open() )
        throw FileIOException();

    output << "P" << format << '\n';
    output << width << ' ' << height << '\n';
    output << colors << '\n';
    output.write(reinterpret_cast<char*>(&pgm[0]), area);
    if ( output.fail() )
        throw FileIOException();

    output.close();
}

void PNM::drawPoint(int x, int y, double transparency, unsigned char brightness, float gamma)
{
    transparency = std::max(std::min(transparency, 1.0), 0.0);
    if (y < 0 || y >= height || x < 0 || x >= width)
        return;
    pgm[width * y + x] = 255 * pow((transparency * pgm[width * y + x] + brightness * (1 - transparency)) / 255.0,
                                   (1.0 / gamma - 1.0) * (1.0 - transparency) + 1.0);
}

void PNM::drawPoint(int x, int y, double transparency, unsigned char brightness)
{
    transparency = std::max(std::min(transparency, 1.0), 0.0);
    if (y < 0 || y >= height || x < 0 || x >= width)
        return;
    double  lineColorLinear = brightness / 255.0,
            picColorSRGB = pgm[width * y + x] / 255.0,
            picColorLinear = picColorSRGB <= 0.04045 ? picColorSRGB / 12.92 : pow((picColorSRGB + 0.055) / 1.055, 2.4),
            c_Linear = (1 - transparency) * lineColorLinear + transparency * picColorLinear,
            c_sRGB = c_Linear <= 0.0031308 ? 12.92 * c_Linear : 1.055 * pow(c_Linear, 1 / 2.4) - 0.055;
    pgm[width * y + x] = 255 * c_sRGB;
}

void PNM::drawLine(float xBegin, float yBegin, float xEnd, float yEnd,
        unsigned char brightness, float thickness, float gamma)
{
    if (thickness <= 0)
        return;

    bool isSteep = abs(yEnd - yBegin) > abs(xEnd - xBegin);

    auto intPart = [](double x) -> int
    {
        return static_cast<int>(x);
    };
    auto distance = [](Point a, Point b) -> double
    {
        return sqrt( pow(a.first - b.first, 2) + pow(a.second - b.second, 2) );
    };
    auto plot = [&](int x, int y, double intensity) -> void
    {
        gamma == 0 ?
            isSteep ?
                drawPoint(y, x, 1.0 - intensity, brightness) :
                drawPoint(x, y, 1.0 - intensity, brightness)
        :
            isSteep ?
                drawPoint(y, x, 1.0 - intensity, brightness, gamma) :
                drawPoint(x, y, 1.0 - intensity, brightness, gamma);
    };

    if (isSteep)
    {
        std::swap(xBegin, yBegin);
        std::swap(xEnd, yEnd);
    }
    if (xBegin > xEnd)
    {
        std::swap(xBegin, xEnd);
        std::swap(yBegin, yEnd);
    }

    double dx = xEnd - xBegin, dy = yEnd - yBegin;
    double gradient = dy / dx;

    double y = yBegin + gradient * (round(xBegin) - xBegin);

    for (int x = (int)round(xBegin); x <= (int)round(xEnd); ++x)
    {
        for (int plotY = intPart(y - (thickness - 1) / 2);
             plotY <= intPart(y - (thickness - 1) / 2 + thickness); ++plotY)
        {
            plot( x, plotY,
                    std::min(1.0, (thickness + 1.0) / 2.0 - fabs(y - plotY)) );
        }
        y += gradient;
    }

    Point plotStart = std::make_pair( round(xBegin), round(yBegin) );
    for (int plotX = int(round(xBegin) - thickness / 2); plotX < (int)round(xBegin); ++plotX)
    {
        y = yBegin + gradient * ( (float)plotX - xBegin );
        for (int plotY = int(y - (thickness - 1) / 2.0);
             plotY <= int(y - (thickness - 1) / 2.0 + thickness); ++plotY)
        {
            plot(plotX, plotY,
                    std::min(1.0, (thickness + 0.5) / 2.0 -
                    distance( { (float) plotX, (float) plotY }, plotStart) )
            );
        }
    }

    Point plotEnd = { round(xEnd), round(yEnd) };
    for (int plotX = (int)round(xEnd) + 1; plotX <= int(round(xEnd) + thickness / 2); plotX++)
    {
        y = yBegin + gradient * ( (float)plotX - xBegin );
        for (int plotY = int(y - (thickness - 1) / 2.0);
             plotY <= int(y - (thickness - 1) / 2.0 + thickness); ++plotY)
        {
            plot(plotX, plotY,
                    std::min(1.0, (thickness + 0.5) / 2.0 -
                    distance( { (float) plotX, (float) plotY }, plotEnd ) )
            );
        }
    }
}
