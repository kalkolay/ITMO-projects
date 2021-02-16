#include <iostream>

#include "ini_parser/INIParser.h"
#include "ini_parser/exceptions/Exceptions.h"

using namespace ini_parser;
using namespace exceptions;

/// Пока без юнит-тестов, впредь буду аккуратнее
int main()
{
    INIParser parser;

    try
    {
        parser = INIParser::Parse("test.ini");
    }
    catch (INIFormatException& e)
    {
        std::cerr << e.what();
    }
    catch (INIReaderException& e)
    {
        std::cerr << e.what();
    }
    catch (DuplicateSectionException& e)
    {
        std::cerr << e.what();
    }
    catch (DuplicateOptionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidSectionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidOptionException& e)
    {
        std::cerr << e.what();
    }

    try
    {
        std::cout << parser.TryGetIntegerOption("ADC_DEV", "SampleRate") << std::endl;
        std::cout << parser.TryGetIntegerOption("ADC_DEV", "Driver") << std::endl;
    }
    catch (InvalidSectionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidOptionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidTypeException& e)
    {
        std::cerr << e.what();
    }

    try
    {
        std::cout << parser.TryGetDoubleOption("ADC_DEV", "bufferLenSeconds") << std::endl;
        std::cout << parser.TryGetDoubleOption("ADC_DEV", "Driver") << std::endl;
    }
    catch (InvalidSectionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidOptionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidTypeException& e)
    {
        std::cerr << e.what();
    }

    try
    {
        std::cout << parser.TryGetStringOption("ADC_DEV", "Driver") << std::endl;
    }
    catch (InvalidSectionException& e)
    {
        std::cerr << e.what();
    }
    catch (InvalidOptionException& e)
    {
        std::cerr << e.what();
    }

    return 0;
}
