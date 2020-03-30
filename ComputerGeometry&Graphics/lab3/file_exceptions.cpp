#include "file_exceptions.h"

const char* FileIOException::what() const noexcept
{
    return "Error while trying to read file or write to file!";
}

const char* FileFormatException::what() const noexcept
{
    return "Unsupported PNM file format (only PGM is accepted).";
}

const char* DitheringException::what() const noexcept
{
    return "Failed to perform dithering!";
}