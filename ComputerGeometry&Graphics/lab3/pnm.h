#pragma once

#include <string>
#include <vector>

#include "file_exceptions.h"

class PNM
{
public:
    PNM() noexcept;

    void read(const std::string&);
    void write(const std::string&);

    void setCorrection(float) noexcept;
    void fill() noexcept;
    void dither(unsigned, unsigned);

private:
    std::vector<unsigned char> _pgm;
    short                      _format;
    int                        _width;
    int                        _height;
    int                        _colors;
    float                      _correction;

    [[nodiscard]] constexpr double correct(double) noexcept;
    [[nodiscard]] constexpr double backCorrect(double) noexcept;

    void noDither(unsigned) noexcept;
    void orderedDither(unsigned) noexcept;
    void randomDither(unsigned) noexcept;
    void floydSteinbergDither(unsigned) noexcept;
    void jarvisJudiceNinkeDither(unsigned) noexcept;
    void sierra3Dither(unsigned) noexcept;
    void atkinsonDither(unsigned) noexcept;
    void halftoneDither(unsigned) noexcept;
};