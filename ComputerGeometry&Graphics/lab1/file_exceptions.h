#pragma once

#include <exception>

struct FileIOException : public std::exception
{
    [[nodiscard]] const char* what() const noexcept override;
};

struct PerformException : public std::exception
{
    [[nodiscard]] const char* what() const noexcept override;
};

struct FileFormatException : public std::exception
{
    [[nodiscard]] const char* what() const noexcept override;
};
