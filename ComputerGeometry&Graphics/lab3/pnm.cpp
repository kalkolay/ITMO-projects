#include <fstream>
#include <cmath>

#include "config.h"
#include "pnm.h"

PNM::PNM() noexcept = default;

void PNM::read(const std::string& fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    if ( !input.is_open() )
        throw FileIOException();

    char P;
    input >> P;
    if (P != 'P')
        throw FileFormatException();
    input >> _format;
    if (_format != PGM)
        throw FileFormatException();
    input >> _width >> _height;
    input >> _colors;
    if (_colors != MAX_COLORS)
        throw FileFormatException();
    input.get();

    _pgm.resize(area);
    input.read(reinterpret_cast<char*>(&_pgm[0]), area);
    if ( input.fail() )
        throw FileIOException();

    input.close();
}

void PNM::write(const std::string& fileName)
{
    std::ofstream output(fileName, std::ios::binary);
    if ( !output.is_open() )
        throw FileIOException();

    output << "P" << _format << '\n';
    output << _width << ' ' << _height << '\n';
    output << _colors << '\n';
    output.write(reinterpret_cast<char*>(&_pgm[0]), area);
    if ( output.fail() )
        throw FileIOException();

    output.close();
}

void PNM::setCorrection(float gamma) noexcept
{
    _correction = gamma;
}

constexpr double PNM::correct(double value) noexcept
{
    value /= MAX_COLORS;
    if (value > 1)
        value = 1;

    return (_correction == 0 ?
            UNLIKELY(value < 0.0031308) ? MAX_COLORS * value * 12.92
                              : MAX_COLORS * (211. * pow(value, 0.4166) - 11.) / 200.
            : MAX_COLORS * pow(value, _correction)
    );
}

constexpr double PNM::backCorrect(double value) noexcept
{
    value /= MAX_COLORS;

    return (_correction == 0 ?
            UNLIKELY(value < 0.04045) ? MAX_COLORS * value / 12.92
                            : MAX_COLORS * pow((200. * value + 11.) / 211., 2.4)
            : MAX_COLORS * pow(value, 1 / _correction)
    );
}

void PNM::fill() noexcept
{
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
            _pgm[i * _width + j] = correct(static_cast<double>(j) / _width * MAX_COLORS);
}

void PNM::dither(unsigned ditherType, unsigned colorDepth)
{
    switch (ditherType)
    {
        case NoDithering:
            noDither(colorDepth);
            break;
        case OrderedDithering:
            orderedDither(colorDepth);
            break;
        case RandomDithering:
            randomDither(colorDepth);
            break;
        case FloydSteinbergDithering:
            floydSteinbergDither(colorDepth);
            break;
        case JarvisJudiceNinkeDithering:
            jarvisJudiceNinkeDither(colorDepth);
            break;
        case Sierra3Dithering:
            sierra3Dither(colorDepth);
            break;
        case AtkinsonDithering:
            atkinsonDither(colorDepth);
            break;
        case HalftoneDithering:
            halftoneDither(colorDepth);
            break;
        default:
            throw DitheringException();
    }
}

void PNM::noDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer;
    for (auto i = 0; i < area; ++i)
    {
        buffer = backCorrect(_pgm[i]) / static_cast<double>(MAX_COLORS);
        buffer *= value - 1;
        buffer = round(buffer);
        _pgm[i] = round(correct(buffer * MAX_COLORS / static_cast<double>(value - 1)) );
    }
}

void PNM::orderedDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer;
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + MAX_COLORS / static_cast<double>(colorDepth)
                       * (ORDERED_MATRIX[i % 8][j % 8] - 0.5) ) / MAX_COLORS;
            if (buffer < 0)
                buffer = 0;
            buffer *= value - 1;
            buffer = round(buffer);
            _pgm[i * _width + j] = round(correct(buffer * MAX_COLORS / static_cast<double>(value - 1)) );
        }
}

void PNM::randomDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer;
    srand(666);
    for (auto i = 0; i < area; ++i)
    {
        buffer = (backCorrect(_pgm[i])
                  + MAX_COLORS / static_cast<double>(colorDepth)
                   * (static_cast<double>( rand() ) / 32767. - 0.75) ) / static_cast<double>(MAX_COLORS);
        if (buffer < 0)
            buffer = 0;
        buffer *= value;
        buffer = round(buffer);
        _pgm[i] = round(correct(buffer * MAX_COLORS / static_cast<double>(value - 1)) );
    }
}

void PNM::floydSteinbergDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(area, 0);
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + errors[i * _width + j]) / static_cast<double>(MAX_COLORS);
            buffer *= (value - 1);
            buffer = round(buffer);
            buffer *= MAX_COLORS / static_cast<double>(value - 1);
            currentError = _pgm[i * _width + j] + errors[i * _width + j] - buffer;
            _pgm[i * _width + j] = buffer;
            if (j + 1 < _width)
                errors[i * _width + j + 1] += currentError * (7. / 16.);
            if (i + 1 < _height)
            {
                if (j + 1 < _width)
                    errors[(i + 1) * _width + j + 1] += currentError * (1. / 16.);
                errors[(i + 1) * _width + j] += currentError * (5. / 16.);
                if (i > 1 && j > 1)
                    errors[(i - 1) * _width + j - 1] += currentError * (3. / 16.);
            }
        }
}

void PNM::jarvisJudiceNinkeDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(area, 0);
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + errors[i * _width + j]) / static_cast<double>(MAX_COLORS);
            buffer *= (value - 1);
            buffer = round(buffer);
            buffer *= MAX_COLORS / static_cast<double>(value - 1);
            currentError = _pgm[i * _width + j] + errors[i * _width + j] - buffer;
            _pgm[i * _width + j] = buffer;
            for (auto k = 0; k <= 2; ++k)
                for (auto l = -2; l <= 2; ++l)
                    if (i + k < _height)
                    {
                        if ( UNLIKELY(k == 0 && l > 0) )
                        {
                            if (j + l < _width)
                                errors[(i + k) * _width + j + l] += currentError * JJN_MATRIX[k][2 + l] / 48.;
                        }
                        else
                        {
                            if (j + l < _width && j + l > 0)
                                errors[(i + k) * _width + j + l] += currentError * JJN_MATRIX[k][2 + l] / 48.;
                        }
                    }
        }
}

void PNM::sierra3Dither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(area, 0);
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + errors[i * _width + j]) / static_cast<double>(MAX_COLORS);
            buffer *= (value - 1);
            buffer = round(buffer);
            buffer *= MAX_COLORS / static_cast<double>(value - 1);
            currentError = _pgm[i * _width + j] + errors[i * _width + j] - buffer;
            _pgm[i * _width + j] = buffer;
            for (auto k = 0; k <= 2; ++k)
                for (auto l = -2; l <= 2; ++l)
                    if (i + k < _height)
                    {
                        if ( UNLIKELY(k == 0 && l > 0) )
                        {
                            if (j + l < _width)
                                errors[(i + k) * _width + j + l] += currentError * SIERRA3_MATRIX[k][2 + l] / 32.;
                        }
                        else
                        {
                            if (j + l < _width && j + l > 0)
                                errors[(i + k) * _width + j + l] += currentError * SIERRA3_MATRIX[k][2 + l] / 32.;
                        }
                    }
        }
}

void PNM::atkinsonDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer, currentError;;
    std::vector<double> errors;
    errors.resize(area, 0);
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + errors[i * _width + j]) / static_cast<double>(MAX_COLORS);
            buffer *= (value - 1);
            buffer = round(buffer);
            buffer *= MAX_COLORS / static_cast<double>(value - 1);
            currentError = _pgm[i * _width + j] + errors[i * _width + j] - buffer;
            _pgm[i * _width + j] = buffer;
            for (auto k = 0; k <= 2; ++k)
                for (auto l = -2; l <= 2; ++l)
                    if (i + k < _height)
                    {
                        if ( UNLIKELY(k == 0 && l > 0) )
                        {
                            if (j + l < _width)
                                errors[(i + k) * _width + j + l] += currentError * ATKINSON_MATRIX[k][2 + l] / 8.;
                        }
                        else
                        {
                            if (j + l < _width && j + l > 0)
                                errors[(i + k) * _width + j + l] += currentError * ATKINSON_MATRIX[k][2 + l] / 8.;
                        }
                    }
        }
}

void PNM::halftoneDither(unsigned colorDepth) noexcept
{
    int value = pow(2, colorDepth);
    double buffer;
    for (auto i = 0; i < _height; ++i)
        for (auto j = 0; j < _width; ++j)
        {
            buffer = (backCorrect(_pgm[i * _width + j])
                      + MAX_COLORS / static_cast<double>(colorDepth)
                      * (HALFTONE_MATRIX[i % 4][j % 4] - 0.75) ) / MAX_COLORS;
            if (buffer < 0)
                buffer = 0;
            buffer *= value;
            buffer = round(buffer);
            _pgm[i * _width + j] = round(correct(buffer * MAX_COLORS / static_cast<double>(value - 1)) );
        }
}