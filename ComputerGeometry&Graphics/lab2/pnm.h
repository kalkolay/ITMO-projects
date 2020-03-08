#pragma once

#include <string>
#include <vector>

#include "file_exceptions.h"

class PNM
{
public:
    PNM();

    void read(const std::string&);
    void write(const std::string&);

    void drawLine(float, float, float, float, unsigned char, float, float = 0);

private:
    std::vector<unsigned char> pgm;
    short format;
    int width, height, colors;

    void drawPoint(int, int, double, unsigned char);
    void drawPoint(int, int, double, unsigned char, float);
};