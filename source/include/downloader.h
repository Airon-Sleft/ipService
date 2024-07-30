#pragma once
#include <string>
#include <curl/curl.h>
#include <vector>
#include <zip.h>
#include <logger.h>

class Downloader
{
public:
    Downloader(const Logger* log);
    ~Downloader();
    bool Load(const std::string_view& urlPath, const std::string_view& saveFilePath);
private:
    CURL *curl;
    const Logger* logger;
};