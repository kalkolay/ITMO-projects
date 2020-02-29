#include "pnm.h"

#define area width * height

void PNM::displayImgData()
{
    std::cout << "Format: P" << format << " - ";
    std::cout << (format == PGM ? "portable graymap\n" : "portable pixmap\n");
    std::cout << "Size: " << width << "x" << height << std::endl;
    std::cout << colors << " colors" << std::endl;
}

void PNM::read(const std::string& fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    if ( !input.is_open() )
        throw FileIOException();
    read(input);
    input.close();
}

void PNM::read(std::ifstream& input)  // "[^\.]+[^\>]*\.(pgm|ppm){1}$"
{
    input.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    char P;
    input >> P;
    if (P != 'P')
        throw FileFormatException();
    input >> format;
    if (format != PGM && format != PPM)
        throw FileFormatException();
    input >> width >> height;
    input >> colors;
    if (colors != 255)
        throw FileFormatException();
    input.get();
    format == PGM ? readPGM(input) : readPPM(input);
}

void PNM::write(const std::string& fileName)
{
    std::ofstream output(fileName, std::ios::binary);
    if ( !output.is_open() )
        throw FileIOException();
    write(output);
    output.close();
}

void PNM::write(std::ofstream& output)
{
    output.exceptions( std::ofstream::failbit | std::ofstream::badbit );
    output << "P" << format << '\n';
    output << width << ' ' << height << '\n';
    output << colors << '\n';
    format == PGM ? writePGM(output) : writePPM(output);
}

void PNM::perform(unsigned cmd)
{
    switch(cmd)
    {
        case inverse:
            format == PGM ? inversePGM() : inversePPM();
            break;
        case horizontalMirror:
            format == PGM ? horizontalMirrorPGM() : horizontalMirrorPPM();
            break;
        case verticalMirror:
            format == PGM ? verticalMirrorPGM() : verticalMirrorPPM();
            break;
        case rotate90:
            format == PGM ? rotate90PGM() : rotate90PPM();
            std::swap(width, height);
            break;
        case rotate270:
            format == PGM ? rotate270PGM() : rotate270PPM();
            std::swap(width, height);
            break;
        default:
            throw PerformException();
    }
}

void PNM::writePGM(std::ofstream& output)
{
    output.write(reinterpret_cast<char*>(&pgm[0]), area);
}

void PNM::readPGM(std::ifstream& input)
{
    ppm.clear();
    pgm.resize(area);
    input.read(reinterpret_cast<char*>(&pgm[0]), area);
}

void PNM::inversePGM()
{
    for (size_t i = 0; i < area; ++i)
        pgm[i] = colors - pgm[i];
}

void PNM::horizontalMirrorPGM()
{
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width / 2; ++j)
            std::swap(pgm[i * width + j],
                  pgm[i * width + width - j - 1]);
}

void PNM::verticalMirrorPGM()
{
    for (size_t i = 0; i < width; ++i)
        for (size_t j = 0; j < height / 2; ++j)
            std::swap(pgm[j * width + i],
                  pgm[(height - 1) * width - j * width + i]);
}

void PNM::rotate90PGM()
{
    std::vector<unsigned char> turnedDataP5(width * height);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            turnedDataP5[(height - i - 1) + j * height] = pgm[i * width + j];
    pgm.clear();
    pgm = turnedDataP5;
}

void PNM::rotate270PGM()
{
    std::vector<unsigned char> turnedDataP5(width * height);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            turnedDataP5[height * (width - j - 1) + i] = pgm[i * width + j];
    pgm.clear();
    pgm = turnedDataP5;
}

void PNM::writePPM(std::ofstream& output)
{
    auto* buffer = new(std::nothrow) unsigned char[3 * area];
    for (size_t i = 0; i < area; ++i)
    {
        buffer[3 * i] = ppm[i].R;
        buffer[3 * i + 1] = ppm[i].G;
        buffer[3 * i + 2] = ppm[i].B;
    }
    output.write(reinterpret_cast<char*>(buffer), 3 * area);
    delete[] buffer;
}

void PNM::readPPM(std::ifstream& input)
{
    pgm.clear();
    ppm.resize(area);
    auto* buffer = new(std::nothrow) unsigned char[3 * area];
    input.read(reinterpret_cast<char*>(buffer), 3 * area);
    for (size_t i = 0; i < area; ++i)
    {
        ppm[i].R = buffer[3 * i];
        ppm[i].G = buffer[3 * i + 1];
        ppm[i].B = buffer[3 * i + 2];
    }
    delete[] buffer;
}

void PNM::inversePPM()
{
    for (size_t i = 0; i < area; ++i)
    {
        ppm[i].R = colors - ppm[i].R;
        ppm[i].G = colors - ppm[i].G;
        ppm[i].B = colors - ppm[i].B;
    }
}

void PNM::horizontalMirrorPPM()
{
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width / 2; ++j)
            std::swap(ppm[i * width + j],
                  ppm[i * width + width - j - 1]);
}

void PNM::verticalMirrorPPM()
{
    for (size_t i = 0; i < width; ++i)
        for (size_t j = 0; j < height / 2; ++j)
            std::swap(ppm[j * width + i],
                  ppm[(height - 1) * width - j * width + i]);
}

void PNM::rotate90PPM()
{
    std::vector<RGB> turnedDataP6(area);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            turnedDataP6[(height - i - 1) + j * height] = ppm[i * width + j];
    ppm.clear();
    ppm = turnedDataP6;
}

void PNM::rotate270PPM()
{
    std::vector<RGB> turnedDataP6(area);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            turnedDataP6[height * (width - j - 1) + i] = ppm[i * width + j];
    ppm.clear();
    ppm = turnedDataP6;
}
