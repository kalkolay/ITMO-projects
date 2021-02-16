#pragma once

#include <stdexcept>

namespace reports::exceptions
{
    class UnresolvedTaskException : public std::exception
    {
    public:
        explicit UnresolvedTaskException(const char* msg) noexcept
                : message(msg)
        {}

        [[nodiscard]] const char* what() const noexcept override
        {
            return message;
        }

    private:
        const char* message;
    };
}