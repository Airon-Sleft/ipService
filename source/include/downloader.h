#pragma once
#include <string>
#include <curl/curl.h>
#include <vector>
#include <zip.h>
#include <logger.h>
#include <utils.h>

class Downloader
{
public:
    Downloader(const Logger* log);
    ~Downloader();
    bool Load(const std::string_view& urlPath, const std::string_view& saveFilePath, const u_int32_t timeOutInMiliseconds = 0) const;
private:
    CURL *curl;
    const Logger* logger;
};