#include "file_exceptions.h"

const char* FileIOException::what() const noexcept
{
    return "Error while trying to read file or write to file!";
}

const char* PerformException::what() const noexcept
{
    return "Failed to perform the command!";
}

const char* FileFormatException::what() const noexcept
{
    return "Unsupported PNM file format!";
}
