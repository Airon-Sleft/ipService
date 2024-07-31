#include <iostream>
#include <geoBase.h>
#include <string>
#include <chrono>
#include <fstream>
#include <curl/curl.h>
#include <filesystem>
#include <downloader.h>
#include <thread>
#include <future>
#include <unpacker.h>
#include <utils.h>

#include <console_logger.h>

static Logger* mainLogger;

int main(int argc, char *argv[])
{
	using namespace std;
	ConsoleLogger logger;
	mainLogger = &logger;
	GeoBase geoBase;
	Stopwatch sp;
	sp.Start();
	geoBase.LoadBase("ipBase.csv"s);
	sp.PrintCurrent(mainLogger);

	string ipToFind;
	if (argc > 1 ) ipToFind = argv[1];
	else ipToFind = "178.66.177.98"s;
	sp.Start();
	const string country = geoBase.GetCountry(ipToFind);
	sp.PrintCurrent(mainLogger, Stopwatch::TIME_TYPE::NANO_SECONDS);
	cout << "Country:" << country << endl;	

	// const char* path = "https://www.ip2location.com/download/?token=1OmoltRoZRfZO6DLt6QqFNTkD7uOceswVygASjNTW2bm5kvLQfJXL3wvbGqchheq&file=DB9LITECSV";
	const char* path = "https://curl.se/windows/dl-8.9.0_1/curl-8.9.0_1-win64-mingw.zip";
	Downloader downloader{mainLogger};
	downloader.Load(path, "curl.zip");
	Unpacker unpacker(mainLogger);
	unpacker.PrintAll("curl.zip");
	unpacker.Do("curl.zip", "BUILD-HASHES.txt");
	return 0;
}
