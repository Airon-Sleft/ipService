#pragma once
#include <string>
#include <logger.h>
#include <downloader.h>
#include <unpacker.h>

class GeoDBChecker {
public:
    GeoDBChecker(const Logger* logger);
    bool Start(u_int16_t timeOutInMiliseconds = 0);
private:
    // const std::string _urlPath = "https://www.ip2location.com/download/?token=1OmoltRoZRfZO6DLt6QqFNTkD7uOceswVygASjNTW2bm5kvLQfJXL3wvbGqchheq&file=DB9LITECSV";
    const std::string _urlPath = "https://curl.se/windows/dl-8.9.0_1/curl-8.9.0_1-win64-mingw.zip";
    const std::string _fileDirectory = "files/";
    const std::string _fileNameInArchive = "BUILD-HASHES.txt";
    const std::string _fileFullPath = _fileDirectory + _fileNameInArchive;
    const u_int32_t _dayToUpdateDBFile = 31;
    const Logger* _logger;
    const Downloader _downloader;
    Unpacker _unpacker;
    bool DoesHaveDBFile() const;
    bool IsDBFileActual() const;
    bool DownloadDBFile(u_int32_t timeOutInMiliseconds); // download, unpack and delete downloaded archive
};