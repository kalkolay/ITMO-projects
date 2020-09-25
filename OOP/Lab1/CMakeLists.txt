cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1
               main.cpp
               ini_parser/INIParser.cpp
               ini_parser/INIParser.h
               ini_parser/utils/Utilities.cpp
               ini_parser/utils/Utilities.h
               ini_parser/exceptions/DuplicateSectionException.h
               ini_parser/exceptions/DuplicateOptionException.h
               ini_parser/exceptions/InvalidSectionException.h
               ini_parser/exceptions/InvalidOptionException.h
               ini_parser/exceptions/InvalidTypeException.h
               ini_parser/exceptions/INIReaderException.h
               ini_parser/exceptions/INIFormatException.h
               ini_parser/exceptions/Exceptions.h)
