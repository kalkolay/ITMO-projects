#pragma once

#include <string>

struct Pixel { unsigned char A, B, C; };

enum ColorSpace
{
    RGB,
    HSL,
    HSV,
    YCbCr_601,
    YCbCr_709,
    YCoCg,
    CMY
};

class PNM
{
public:
    PNM();
    ~PNM();

    void readPpm(const std::string&);
    void writePpm(const std::string&);
    void readPgm(std::string);
    void writePgm(std::string);

    void setColorSpace(ColorSpace) noexcept;
    void convertColorSpace(ColorSpace) noexcept;

private:
    int        width;
    int        height;
    Pixel*     image;
    ColorSpace colorSpace;

    void convertRgb() noexcept;
};