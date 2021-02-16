#pragma once

#include <stdexcept>

namespace reports::exceptions
{
    class UnfamiliarTaskException : public std::exception
    {
    public:
        explicit UnfamiliarTaskException(const char* msg) noexcept
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