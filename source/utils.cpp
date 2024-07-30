#include <utils.h>

void Stopwatch::Start()
{
    start_time = std::chrono::steady_clock::now();
}


int64_t Stopwatch::Get(TIME_TYPE timeType)
{
    auto end_time = std::chrono::steady_clock::now();
    if (timeType == TIME_TYPE::NANO_SECONDS)
	{
    	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	    return elapsed_ns.count();
	}
	else
	{
    	auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	    return elapsed_ns.count();	
	}
}

void Stopwatch::PrintCurrent(Logger *logger, TIME_TYPE timeType)
{
    int64_t elapsed = Get(timeType);

    logger->Log("It took " + std::to_string(elapsed) + " " + time_type_names[(int)timeType]);
}