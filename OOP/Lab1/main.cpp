#include <iostream>

#include "ini_parser/INIParser.h"

using namespace ini_parser;

int main()
{
    INIParser parser = INIParser::Parse("test.ini");

    std::cout << parser.TryGetIntegerOption("ADC_DEV", "SampleRate") << std::endl;
    std::cout << parser.TryGetDoubleOption("ADC_DEV", "bufferLenSeconds") << std::endl;
    std::cout << parser.TryGetStringOption("ADC_DEV", "Driver") << std::endl;

    return 0;
}
