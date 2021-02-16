#pragma once

#include <stdexcept>

namespace reports::exceptions
{
    class UnfamiliarReportException : public std::exception
    {
    public:
        explicit UnfamiliarReportException(const char* msg) noexcept
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