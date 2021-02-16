#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace race_engine::entities
{
    using speed_t           = uint64_t;
    using rest_interval_t   = uint32_t;
    using rest_duration_t   = std::function<double(size_t)>;
    using distance_reduce_t = std::function<double(double)>;

    class ITransport
    {
    public:
        virtual ~ITransport() = default;

        virtual std::string GetName() = 0;

        virtual double Update(double distance) = 0;
    };
}