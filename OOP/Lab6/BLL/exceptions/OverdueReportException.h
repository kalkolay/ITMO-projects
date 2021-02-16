#pragma once

#include <stdexcept>

namespace reports::exceptions
{
    class OverdueReportException : public std::exception
    {
    public:
        explicit OverdueReportException(const char* msg) noexcept
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