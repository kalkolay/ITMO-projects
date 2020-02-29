#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "file_exceptions.h"

struct RGB
{
    unsigned char R, G, B;
};

enum Command
{
    inverse = 0,
    horizontalMirror,
    verticalMirror,
    rotate90,
    rotate270
};

enum Format
{
    PGM = 5,
    PPM
};

class PNM
{
public:
    PNM() = default;

    void displayImgData();

    void read(const std::string&);
    void read(std::ifstream&);

    void write(const std::string&);
    void write(std::ofstream&);

    void perform(unsigned);

private:
    std::vector<unsigned char> pgm;
    std::vector<RGB> ppm;
    short format;
    int width, height, colors;

    void writePGM(std::ofstream&);
    void readPGM(std::ifstream&);
    void inversePGM();
    void horizontalMirrorPGM();
    void verticalMirrorPGM();
    void rotate90PGM();
    void rotate270PGM();

    void writePPM(std::ofstream&);
    void readPPM(std::ifstream&);
    void inversePPM();
    void horizontalMirrorPPM();
    void verticalMirrorPPM();
    void rotate90PPM();
    void rotate270PPM();
};
