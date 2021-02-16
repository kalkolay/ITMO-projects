#pragma once

#include <exception>

namespace race_engine::exceptions
{
    class RaceTypeException : public std::exception
    {
    public:
        explicit RaceTypeException(const char* msg) noexcept
                : m_message(msg)
        {}

        /**
         * @return a C-style character string describing the general cause of the current error.
         */
        [[nodiscard]] const char* what() const noexcept override
        {
            return m_message;
        }

    private:
        const char* m_message;
    };
}