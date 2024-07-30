#include <console_logger.h>

void ConsoleLogger::Log(const std::string &info) const
{
    std::cout << info << std::endl;
}