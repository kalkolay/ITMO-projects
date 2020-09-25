#pragma once

#include <stdexcept>

namespace ini_parser::exceptions
{
    class DuplicateOptionException : public std::exception
    {
    public:
        explicit DuplicateOptionException(const char* msg) noexcept
            : message(msg)
        {}

        /**
         * @return a C-style character string describing the general cause of the current error.
         */
        [[nodiscard]] const char* what() const noexcept override
        {
            return message;
        }

    private:
        const char* message;
    };
}