#pragma once

#include <stdexcept>

namespace ini_parser::exceptions
{
    class InvalidTypeException : public std::exception
    {
    public:
        explicit InvalidTypeException(const char* msg) noexcept
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