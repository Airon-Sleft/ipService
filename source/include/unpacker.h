#pragma once
#include <zip.h>
#include <string>
#include <logger.h>

class Unpacker {
public:
    Unpacker(const Logger* logger);
    ~Unpacker();
    bool Do(const std::string& zipFilePath, const std::string& fileNameForUnpack);
    void PrintAll(const std::string& zipFilePath);
private:
    void CloseAll();
    bool Open(const std::string& zipFilePath);
    std::string GetFileName(const std::string& fullFilePath);
    bool WriteToFile(const std::string& fileName, const char* content, size_t sizeBuffer);
    const Logger* logger;
    zip* zipAchive = nullptr;
    zip_stat_t zipStat;
    zip_file* zipFile = nullptr;
};