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
#include <geo_db_checker.h>

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

	GeoDBChecker geoDBChecker(mainLogger);
	bool result = geoDBChecker.Start();
	if (!result)	mainLogger->Log("NO STARTed");
	else mainLogger->Log("Initialization is okay");
	return 0;
}
