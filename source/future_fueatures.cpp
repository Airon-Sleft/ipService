#include <filesystem>
#include <chrono>
#include <future>
#include <thread>

int DayFromLastModify()
{
    using namespace std;
    filesystem::file_time_type ftime = filesystem::last_write_time("ipBase.csv");
    const auto toNow = filesystem::file_time_type::clock::now() - ftime;
    const auto elapsedHours = chrono::duration_cast<chrono::hours>(toNow).count();
    return elapsedHours/24;
}

void AsyncLoad()
{
    using namespace std;
    auto future = std::async(std::launch::async, [](const string& fileName) {

    }, "classfile.zip");
	while (future.wait_for(chrono::nanoseconds(1)) != future_status::ready)
	{
		//something usefull...
	}
    // future is ready
}