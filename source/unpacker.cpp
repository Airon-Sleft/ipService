#include <unpacker.h>
#include <cstring>
#include <algorithm>
#include <memory>
#include <fstream>

Unpacker::Unpacker(const Logger* log) : logger(log)
{
}

Unpacker::~Unpacker()
{
    CloseAll();
}

void Unpacker::CloseAll()
{
    if (zipFile != nullptr)
    {
        zip_fclose(zipFile);
        zipFile = nullptr;
    }
    if (zipAchive != nullptr)
    {
        zip_close(zipAchive);
        zipAchive = nullptr;
    }
}

bool Unpacker::Open(const std::string &zipFilePath)
{
    int error = 0;
    if ( (zipAchive = zip_open(zipFilePath.c_str(), ZIP_RDONLY, &error)) == NULL)
    {
        zip_error_t zError;
        zip_error_init_with_code(&zError, error);
        logger->Log(zip_error_strerror(&zError));
        return false;
    }
    zip_stat_init(&zipStat);
    return true;
}

std::string Unpacker::GetFileName(const std::string &fullFilePath)
{
    std::string result;
    for (auto start = fullFilePath.rbegin(); start != fullFilePath.rend(); start++)
    {
        if (*start == '/')
        {
            break;
        }
        else
        {
            result += *start;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool Unpacker::Do(const std::string &zipFilePath, const std::string &fileNameForUnpack)
{
    Open(zipFilePath);
    for (int i = 0; i < zip_get_num_entries(zipAchive, ZIP_FL_UNCHANGED); i++)
    {
        zip_stat_index(zipAchive, i, 0, &zipStat);
        const char* pos = strstr(zipStat.name, fileNameForUnpack.c_str());
        if (pos != NULL)
        {
            break; // found, exit from loop and zipStat has a values;
        }
        zip_stat_init(&zipStat);
    }
    if (zipStat.valid == 0)
    {
        std::string message("File " + fileNameForUnpack + " not found in Archive: " + zipFilePath );
        logger->Log(message);
        return false;
    }
    std::unique_ptr<char[]> content(new char[zipStat.size]);
    zipFile = zip_fopen(zipAchive, zipStat.name, ZIP_FL_UNCHANGED);
    if (!zipFile || zip_fread(zipFile, content.get(), zipStat.size) == -1)
    {
        logger->Log("Unexpected error when read file" + fileNameForUnpack + " in Archive: " + zipFilePath);
        return false;
    }
    CloseAll();
    if (!WriteToFile(fileNameForUnpack, content.get(), zipStat.size))
    {
        logger->Log("Error when write data to file " + fileNameForUnpack);
        return false;
    }
    return true;
}

void Unpacker::PrintAll(const Logger *logger, const std::string &zipFilePath)
{
    Open(zipFilePath);
    for (int i = 0; i < zip_get_num_entries(zipAchive, ZIP_FL_UNCHANGED); ++i)
    {
        zip_stat_index(zipAchive, i, 0, &zipStat);
        logger->Log(zipStat.name);
        zip_stat_init(&zipStat);
    }
    CloseAll();
}

bool Unpacker::WriteToFile(const std::string& filePath, const char* content, size_t sizeBuffer)
{
    std::ofstream file = std::ofstream(filePath);
    if(!file.is_open()) return false;
    file.write(content, sizeBuffer);
    file.close();
    return true;
}