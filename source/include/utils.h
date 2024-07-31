#pragma once
#include <chrono>
#include <logger.h>
#include <string>

#if defined(_WIN32)

#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

#endif

class Stopwatch
{
public:
    enum class TIME_TYPE {
        NANO_SECONDS,
        MILISECONDS,
    };
    const std::string time_type_names[2] = {
        "nanoseconds", "milliseconds"
    } ;
    Stopwatch() = default;
    void Start();
    int64_t Get(TIME_TYPE timeType = TIME_TYPE::MILISECONDS);
    void PrintCurrent(Logger* logger, TIME_TYPE timeType = TIME_TYPE::MILISECONDS);
private:
    std::chrono::_V2::steady_clock::time_point start_time;
};