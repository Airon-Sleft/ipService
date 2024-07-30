#pragma once
#include <string>

class Logger
{
public:
    virtual void Log(const std::string& info) const = 0;
};