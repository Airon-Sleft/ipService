#pragma once
#include <chrono>
#include <logger.h>
#include <string>

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