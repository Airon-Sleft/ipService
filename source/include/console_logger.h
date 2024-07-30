#pragma once
#include <logger.h>
#include <iostream>

class ConsoleLogger : public Logger
{
public:
    void Log(const std::string& info) const override;
};